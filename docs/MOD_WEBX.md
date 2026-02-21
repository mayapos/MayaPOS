# mod_webx — High-Performance Apache Module for Harbour

**Version 2.0** (Feb 2026)

Persistent Harbour VM inside Apache with built-in connection pooling, code caching, sessions, and rate limiting — features that PHP needs Redis, OPcache, and middleware to achieve.

---

## What is mod_webx?

mod_webx is an Apache module that embeds the Harbour programming language directly into the Apache web server. Unlike traditional CGI or even PHP's mod_php, mod_webx keeps the Harbour VM **persistent** across HTTP requests — the compiler, runtime, and your application state stay in memory.

This persistent architecture enables five built-in features that eliminate the need for external services:

| Feature | What PHP Needs | mod_webx |
|---------|---------------|----------|
| Compiled code cache | OPcache extension | Built-in |
| DB connection pool | `pconnect` or ProxySQL | Built-in |
| Application cache | Redis ($) or Memcached | Built-in |
| Session storage | File I/O or Redis | Built-in (in-memory) |
| Rate limiting | Redis + middleware | Built-in |

---

## Architecture

```
Apache child process (persistent — handles thousands of requests)
  |
  +-- Harbour VM (initialized once, stays loaded)
  |
  +-- hPersistent hash (survives across all requests)
  |     +-- Compiled bytecode cache
  |     +-- Database connections (pooled)
  |     +-- Application cache (with TTL)
  |     +-- User sessions (in-memory)
  |     +-- Rate limit counters
  |
  +-- Per-request: lightweight thread context (fast setup/teardown)
```

**Key difference from PHP**: In PHP, every request starts from scratch — load code, connect to database, initialize session, etc. In mod_webx, all of this persists between requests.

---

## Performance: mod_webx vs PHP

### Request Processing

| Step | PHP (first request) | PHP (cached) | mod_webx (first) | mod_webx (cached) |
|------|:---:|:---:|:---:|:---:|
| Code compilation | 10-40ms | 0ms (OPcache) | 20-80ms | **0ms** |
| DB connection | 5-10ms | 0ms (pconnect) | 5-10ms | **0ms** |
| Cache lookup | 0.1-1ms (Redis) | 0.1-1ms (Redis) | **~0ms** | **~0ms** |
| Session load | 0.5-2ms (file) | 0.5-2ms (file) | **~0ms** | **~0ms** |
| Code execution | Bytecode + JIT | Bytecode + JIT | **Native compiled** | **Native compiled** |

### Why mod_webx is Faster

1. **Compiled execution**: Harbour compiles .prg to C, which compiles to native machine code. PHP interprets bytecode (even with JIT, there's overhead).

2. **Zero-latency caching**: Application cache lives in the same process memory. PHP needs Redis (network hop + serialization). mod_webx reads a pointer — literally zero milliseconds.

3. **Persistent connections**: Database connections survive across requests without any configuration. No `pconnect` quirks, no connection pooling proxy.

4. **No cold starts**: The VM, all symbols, and pre-loaded code stay resident. There's no equivalent of PHP's RINIT/RSHUTDOWN cycle.

### Where PHP Wins

- **Ecosystem**: Composer, Laravel, thousands of packages
- **Developer pool**: Far more PHP developers available
- **Hosting**: Every shared host supports PHP; mod_webx requires VPS/dedicated
- **Tooling**: PHPStorm, Xdebug, PHPUnit — mature ecosystem

---

## Built-in Features

### 1. Compiled Code Cache

The biggest performance win. On first request, mod_webx compiles your .prg file to bytecode and caches it in memory. On subsequent requests, it checks the file's fingerprint (date + time + size) — if unchanged, it skips compilation entirely and runs the cached bytecode.

```prg
// This happens automatically — no configuration needed.
// Developer edits file -> next request recompiles -> cache updated.
// No manual cache clearing required.
```

**Impact**: Eliminates 20-80ms compilation overhead on every request after the first.

### 2. Database Connection Pool

Persistent database connections that survive across HTTP requests. No reconnection overhead.

```prg
// Get or create a persistent connection
oConn := WebX_DBPool_Get( "main", "localhost", "root", "", "mydb", 3306 )

// Use it normally
oConn:Execute( "SELECT * FROM users WHERE active = 1" )

// Connection stays alive for the next request
WebX_DBPool_Return( "main" )
```

Features:
- Automatic health checks (ping before reuse)
- Dead connection replacement (transparent reconnect)
- Named pools (separate connections for different purposes)
- Diagnostics API (hit counts, connection age, status)

### 3. In-Memory Cache with TTL

Zero-latency key/value store. Store anything — arrays, hashes, objects, strings.

```prg
// Cache expensive query results for 5 minutes
aProducts := WebX_Cache_Remember( "products", 300, {|| ;
   oConn:Execute("SELECT * FROM products"):GetRows() ;
} )

// The block only executes on cache miss.
// For 5 minutes, every request gets instant results.
```

Features:
- TTL expiration (lazy cleanup on access)
- Get-or-set pattern (WebX_Cache_Remember)
- Atomic counters (WebX_Cache_Increment)
- Hit/miss statistics

### 4. In-Memory Sessions

No disk I/O. No file locking. Sessions live in process memory.

```prg
WebX_Session_Start()

// After login
WebX_Session_Regenerate()                // prevent session fixation
WebX_Session_Set( "user_id", nUserId )
WebX_Session_Set( "role", "admin" )

// On protected pages
IF WebX_Session_Get( "user_id" ) == NIL
   // redirect to login
ENDIF

// Logout
WebX_Session_Destroy()
```

Features:
- Cookie-based (HttpOnly, SameSite)
- Session regeneration (anti-fixation)
- Configurable timeout
- IP tracking

### 5. Rate Limiter

Sliding window counters. No external dependencies.

```prg
// 100 requests per minute per IP
IF ! WebX_RateLimit_Check( AP_UserIP(), 100, 60 )
   AP_RPuts( "429 Too Many Requests" )
   RETURN
ENDIF

// Standard rate limit headers
WebX_RateLimit_Headers( AP_UserIP(), 100, 60 )
// -> X-RateLimit-Limit: 100
// -> X-RateLimit-Remaining: 73
// -> X-RateLimit-Reset: 60
```

---

## Comparison: mod_webx vs mod_harbour

mod_webx is based on mod_harbour but significantly enhanced:

| Feature | mod_harbour v1 (FiveTech) | mod_harbour v3 (Manu Exposito) | mod_webx |
|---------|:---:|:---:|:---:|
| VM persistence | No (init/quit per request) | Yes | Yes |
| DLL handling | Copy + load + free per request | Static | Static |
| Persistent storage | No | hPersistent hash | hPersistent + 5 subsystems |
| Code caching | No | No | Yes (auto file-change detection) |
| Connection pool | No | No | Yes (multi-driver, health check) |
| Session management | No | No | Yes (in-memory, cookie-based) |
| Rate limiting | No | No | Yes (sliding window) |
| Cache API | No | No | Yes (TTL, get-or-set, counters) |
| Thread safety | No | APR mutex | APR mutex + per-thread map |
| Auto-claim .prg/.hrb | No | No | Yes (no SetHandler needed) |

---

## Quick Start

### Apache Configuration

```apache
LoadModule webx_module modules/mod_webx.so
```

That's it. mod_webx auto-claims `.prg` and `.hrb` files without needing `SetHandler`.

### Hello World

Create `hello.prg` in your web root:

```prg
FUNCTION Main()
   ?? "<h1>Hello from mod_webx!</h1>"
   ?? "<p>Harbour VM is persistent. This code was compiled once.</p>"
   ?? "<p>Request handled in ~0ms (cached).</p>"
RETURN NIL
```

Visit `http://localhost/hello.prg` — done.

### Real Application

```prg
FUNCTION Main()
   LOCAL oConn, aUsers

   // Rate limit
   IF ! WebX_RateLimit_Check( AP_UserIP(), 100, 60 )
      ?? "429 Too Many Requests"
      RETURN NIL
   ENDIF

   // Session
   WebX_Session_Start()

   // Get pooled DB connection
   oConn := WebX_DBPool_Get( "main", "localhost", "root", "", "myapp" )

   // Cached query (5 min TTL)
   aUsers := WebX_Cache_Remember( "active_users", 300, {|| ;
      oConn:Execute("SELECT * FROM users WHERE active=1"):GetRows() ;
   } )

   // Render
   ?? "<h1>Active Users: " + AllTrim(Str(Len(aUsers))) + "</h1>"
   ?? "<p>Session: " + WebX_Session_Id() + "</p>"
   ?? "<p>Cache stats: " + hb_JsonEncode(WebX_Cache_Stats()) + "</p>"

   WebX_DBPool_Return( "main" )
RETURN NIL
```

---

## API Quick Reference

### Persistent Storage (Low-Level)
```
AP_SetPersistent( cNamespace, cKey, xValue )
AP_GetPersistent( cNamespace, cKey ) -> xValue
AP_DelPersistent( cNamespace, cKey ) -> lDeleted
AP_HasPersistent( cNamespace, cKey ) -> lExists
```

### Connection Pool
```
WebX_DBPool_Get( cName, cHost, cUser, cPass, cDB [, nPort] ) -> oConnection
WebX_DBPool_Return( cName )
WebX_DBPool_Destroy( cName )
WebX_DBPool_DestroyAll()
WebX_DBPool_Names() -> aNames
WebX_DBPool_Info( cName ) -> hInfo
```

### Cache
```
WebX_Cache_Set( cKey, xValue [, nTTL] )
WebX_Cache_Get( cKey [, xDefault] ) -> xValue
WebX_Cache_Has( cKey ) -> lExists
WebX_Cache_Del( cKey ) -> lDeleted
WebX_Cache_Remember( cKey, nTTL, bBlock ) -> xValue
WebX_Cache_Increment( cKey [, nAmount] ) -> nNewValue
WebX_Cache_Stats() -> hStats
WebX_Cache_Flush()
```

### Sessions
```
WebX_Session_Start( [nTimeout] ) -> cSessionId
WebX_Session_Set( cKey, xValue )
WebX_Session_Get( cKey [, xDefault] ) -> xValue
WebX_Session_Has( cKey ) -> lExists
WebX_Session_Del( cKey )
WebX_Session_Destroy()
WebX_Session_Id() -> cSessionId
WebX_Session_Regenerate() -> cNewId
```

### Rate Limiting
```
WebX_RateLimit_Check( cKey, nMaxRequests, nWindowSecs ) -> lAllowed
WebX_RateLimit_Remaining( cKey, nMaxRequests, nWindowSecs ) -> nRemaining
WebX_RateLimit_Reset( cKey )
WebX_RateLimit_Headers( cKey, nMaxRequests, nWindowSecs )
```

### Code Cache Management
```
WebX_CacheClear( [cFileName] )    // clear one or all
WebX_CacheList() -> aFileNames    // list cached files
WebX_CacheInfo( cFileName ) -> hInfo
```

---

## Building mod_webx

### Requirements
- Visual Studio 2022 (C++ workload)
- Apache 2.4 (64-bit) with development headers
- Harbour 3.2+ (64-bit)

### Build
```cmd
cd mod_WebX\windows
BUILD.bat
```

Output: `mod_webx.so` copied to Apache's `modules/` directory. Apache is automatically restarted.

---

## Two Deployment Paths

WebX supports two independent deployment modes from the same `.prg` source:

| | mod_webx (Native) | webxphp.exe (Transpiled) |
|---|---|---|
| **Server** | Apache + mod_webx.so | Any PHP host |
| **Execution** | Harbour VM (native) | PHP interpreter |
| **Performance** | Fastest (compiled + persistent) | Fast (PHP 8 + OPcache) |
| **Hosting** | VPS/dedicated | Shared hosting ($5/mo) |
| **Dependencies** | Harbour runtime | None (pure PHP) |

Same source code. Choose based on your hosting and performance needs.

---

## License

mod_webx is part of the WebX Framework.

Copyright (c) 2026 MayaPOS - WebX Framework. All rights reserved.

---

## Links

- [WebX Framework](https://github.com/mayapos/WebX)
- [MayaPOS Demo](https://github.com/mayapos/MayaPOS)
- [Harbour Language](https://harbour.github.io)
- [Apache HTTP Server](https://httpd.apache.org)
- [Contact](mailto:mayabuilders@gmail.com)
