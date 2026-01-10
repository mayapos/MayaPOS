<!-- Created: 2025-01-09 -->

# WebX Deployment Options - Complete Guide

## Overview

WebX supports **6 primary deployment modes** plus multiple compatibility layers. This guide helps you choose the right deployment strategy for your project.

---

## Quick Comparison Matrix

| Feature | WebXCGI | WebXFCGI | WebXServer | WebXPHP | mod_WebX | mod_harbour |
|---------|---------|----------|------------|---------|----------|-------------|
| **Performance** | ⭐ Low | ⭐⭐⭐⭐ High | ⭐⭐⭐⭐ High | ⭐⭐⭐ Medium | ⭐⭐⭐⭐⭐ Max | ⭐⭐⭐⭐⭐ Max |
| **Complexity** | ⭐ Simple | ⭐⭐⭐ Medium | ⭐ Simple | ⭐ Simple | ⭐⭐⭐⭐ Complex | ⭐⭐⭐⭐ Complex |
| **Memory** | High | Low | Medium | Medium | Very Low | Very Low |
| **Startup** | Slow | Fast | Fast | Medium | Instant | Instant |
| **Debugging** | Easy | Medium | Easy | Easy | Hard | Hard |
| **Scalability** | Poor | Excellent | Good | Good | Excellent | Excellent |
| **Web Server** | Any | Any | None | Any | Apache | Apache |
| **Windows** | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| **Linux** | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| **Shared Host** | ❌ | ❌ | ❌ | ✅ | ❌ | ❌ |

---

## Deployment Mode Details

### 1. WebXCGI - Traditional CGI Executables

#### Architecture

```
Browser → Web Server → Spawn .exe → Execute → Return HTML → Kill Process
          (Apache/IIS)  (Per Request)
```

**Process Model:**
- Each HTTP request spawns new .exe process
- Process loads, executes, outputs HTML, terminates
- No state persists between requests
- Session data stored in files/database

#### Configuration

**Apache (.htaccess):**
```apache
Options +ExecCGI
AddHandler cgi-script .exe

<Files "*.exe">
    SetHandler cgi-script
</Files>

# Optional: Disable caching for development
Header set Cache-Control "no-cache, no-store, must-revalidate"
Header set Pragma "no-cache"
Header set Expires "0"
```

**IIS (web.config):**
```xml
<configuration>
  <system.webServer>
    <handlers>
      <add name="WebXCGI" path="*.exe" verb="*"
           modules="CgiModule" scriptProcessor=""
           resourceType="File" requireAccess="Execute" />
    </handlers>
  </system.webServer>
</configuration>
```

**Nginx:**
```nginx
location ~ \.exe$ {
    gzip off;
    root /var/www/webx;
    fastcgi_pass unix:/var/run/fcgiwrap.socket;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

#### Build Example

```batch
REM Build WebX CGI application
cd C:\xampp2025\htdocs\webx\samples
.\xBasePHPh64_web.bat myapp

REM Deploy
copy myapp.exe C:\xampp2025\htdocs\mysite\
copy .htaccess C:\xampp2025\htdocs\mysite\

REM Test
REM Navigate to: http://localhost/mysite/myapp.exe
```

#### Best Practices

**Do:**
- ✅ Use for low-traffic sites (<100 req/day)
- ✅ Use for prototyping/development
- ✅ Use for internal tools
- ✅ Keep executables small (link only needed libraries)
- ✅ Implement session management via files or database
- ✅ Cache static resources (CSS, JS, images)

**Don't:**
- ❌ Use for high-traffic production (process overhead kills performance)
- ❌ Store state in memory (process dies after response)
- ❌ Assume sequential execution (requests are independent)

#### Performance Tuning

```harbour
// Optimize CGI startup time
FUNCTION Main()
   // Load only essential libraries
   REQUEST HB_CODEPAGE_UTF8EX
   hb_cdpSelect("UTF8EX")

   // Minimize initialization
   IF Empty(GetEnv("QUERY_STRING"))
      RETURN NIL  // Exit fast for invalid requests
   ENDIF

   // Process request...
RETURN NIL
```

---

### 2. WebXFCGI - FastCGI Persistent Process

#### Architecture

```
Browser → Web Server → FastCGI Socket → Persistent Process Pool → Return HTML
          (Apache/Nginx)               (Handles Multiple Requests)
```

**Process Model:**
- Persistent process(es) started once
- Web server communicates via socket/pipe
- Handles multiple requests sequentially or in parallel
- State can persist in memory

#### Configuration

**Nginx (Recommended):**
```nginx
upstream webx_backend {
    server 127.0.0.1:9000;
    server 127.0.0.1:9001;  # Multiple processes for load balancing
    server 127.0.0.1:9002;
}

server {
    listen 80;
    server_name mysite.com;

    location / {
        fastcgi_pass webx_backend;
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;

        # Timeouts for long-running requests
        fastcgi_read_timeout 300;
        fastcgi_send_timeout 300;

        # Buffer settings
        fastcgi_buffer_size 16k;
        fastcgi_buffers 4 16k;
    }
}
```

**Apache with mod_fcgid:**
```apache
<IfModule mod_fcgid.c>
    FcgidMaxProcesses 10
    FcgidMaxRequestsPerProcess 1000
    FcgidIOTimeout 300

    <Directory "/var/www/webx">
        Options +ExecCGI
        AddHandler fcgid-script .exe
    </Directory>
</IfModule>
```

#### Application Code

```harbour
#include "WebX.ch"

STATIC hSessionCache := {=>}  // In-memory cache (persists!)

FUNCTION Main()
   LOCAL cSessionID, hSession

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   // Get session from cache (FastCGI advantage!)
   cSessionID := GetCookie("SESSIONID")
   IF HHasKey(hSessionCache, cSessionID)
      hSession := hSessionCache[cSessionID]
   ELSE
      hSession := CreateNewSession()
      hSessionCache[cSessionID] := hSession
   ENDIF

   // Process request with persistent session...

RETURN NIL
```

#### Process Management

**Spawn FastCGI Process (Linux):**
```bash
#!/bin/bash
# start_fcgi.sh

APP="/var/www/webx/myapp.exe"
SOCKET="/var/run/webx_fcgi.sock"
PROCESSES=4

spawn-fcgi -a 127.0.0.1 -p 9000 -F $PROCESSES -- $APP
```

**Spawn FastCGI Process (Windows):**
```batch
REM start_fcgi.bat
SET APP=C:\webx\myapp.exe
SET PORT=9000

REM Using fcgiwrap or custom launcher
fcgiwrap.exe -c 4 -p %PORT% -f %APP%
```

#### Best Practices

**Do:**
- ✅ Use for production high-traffic sites
- ✅ Implement connection pooling (database, cache)
- ✅ Monitor memory usage (persistent process can leak)
- ✅ Graceful restart mechanism
- ✅ Use multiple processes for load balancing
- ✅ Implement health checks

**Don't:**
- ❌ Store unbounded data in memory (memory leak!)
- ❌ Use global variables without cleanup
- ❌ Assume process will restart (it won't!)
- ❌ Ignore memory growth (implement periodic restart)

#### Memory Management

```harbour
// Periodic cleanup to prevent memory bloat
STATIC nRequestCount := 0
STATIC nMaxRequests := 1000

FUNCTION Main()
   nRequestCount++

   // Process request...

   // Cleanup every N requests
   IF nRequestCount >= nMaxRequests
      CleanupCache()
      hb_gcAll(.T.)  // Force garbage collection
      nRequestCount := 0
   ENDIF

RETURN NIL

STATIC FUNCTION CleanupCache()
   LOCAL cKey, hEntry, nNow := Seconds()

   // Remove expired session cache entries
   FOR EACH cKey IN hSessionCache:Keys()
      hEntry := hSessionCache[cKey]
      IF (nNow - hEntry["timestamp"]) > 1800  // 30 min expiry
         hSessionCache:Del(cKey)
      ENDIF
   NEXT

RETURN NIL
```

---

### 3. WebXServer - Standalone HTTP Server

#### Architecture

```
Browser → WebX Application (IS the HTTP Server)
          ↓
          Handles sockets, routing, responses directly
```

**Process Model:**
- Your .exe IS the web server (like Node.js, Go)
- Listens on port, handles HTTP protocol
- Single process or multi-threaded
- Full control over all HTTP aspects

#### Application Code

```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oServer

   // Create HTTP server
   oServer := TWebXServer():New()
   oServer:nPort := 8080
   oServer:cDocRoot := "C:\webx\www"

   // Define routes
   oServer:AddRoute("GET", "/", {|| HomePage() })
   oServer:AddRoute("GET", "/api/customers", {|| GetCustomers() })
   oServer:AddRoute("POST", "/api/save", {|oReq| SaveData(oReq) })
   oServer:AddRoute("*", "/static/*", {|oReq| ServeStatic(oReq) })

   // Middleware
   oServer:AddMiddleware({|oReq, oNext| LogRequest(oReq), oNext:Eval() })
   oServer:AddMiddleware({|oReq, oNext| CheckAuth(oReq), oNext:Eval() })

   // Start server (blocking)
   ? "WebX Server listening on http://localhost:8080"
   oServer:Start()

RETURN NIL

STATIC FUNCTION HomePage()
   LOCAL cHTML := ""

   cHTML += '<!DOCTYPE html><html><head><title>Home</title></head>'
   cHTML += '<body><h1>Welcome to WebX Server</h1></body></html>'

RETURN { "status" => 200, "headers" => {=>}, "body" => cHTML }

STATIC FUNCTION GetCustomers()
   LOCAL aData, cJSON

   aData := LoadCustomersFromDB()
   cJSON := hb_jsonEncode(aData)

RETURN { "status" => 200, ;
         "headers" => {"Content-Type" => "application/json"}, ;
         "body" => cJSON }
```

#### Production Deployment

**Behind Nginx Reverse Proxy (Recommended):**
```nginx
server {
    listen 80;
    server_name mysite.com;

    # SSL termination
    listen 443 ssl;
    ssl_certificate /etc/ssl/certs/mysite.crt;
    ssl_certificate_key /etc/ssl/private/mysite.key;

    location / {
        proxy_pass http://127.0.0.1:8080;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;

        # WebSocket support (if needed)
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "upgrade";
    }

    # Serve static files directly (bypass WebX)
    location /static/ {
        alias /var/www/webx/static/;
        expires 30d;
    }
}
```

**Systemd Service (Linux):**
```ini
# /etc/systemd/system/webx-server.service
[Unit]
Description=WebX HTTP Server
After=network.target

[Service]
Type=simple
User=webx
WorkingDirectory=/var/www/webx
ExecStart=/var/www/webx/myapp.exe
Restart=always
RestartSec=5
StandardOutput=journal
StandardError=journal

[Install]
WantedBy=multi-user.target
```

```bash
# Enable and start service
sudo systemctl enable webx-server
sudo systemctl start webx-server
sudo systemctl status webx-server
```

**Windows Service:**
```batch
REM Install as Windows Service using NSSM (Non-Sucking Service Manager)
nssm install WebXServer "C:\webx\myapp.exe"
nssm set WebXServer AppDirectory "C:\webx"
nssm set WebXServer AppStdout "C:\webx\logs\stdout.log"
nssm set WebXServer AppStderr "C:\webx\logs\stderr.log"

REM Start service
nssm start WebXServer
```

#### Best Practices

**Do:**
- ✅ Use reverse proxy (Nginx/Apache) for SSL, static files, load balancing
- ✅ Implement graceful shutdown
- ✅ Log to file/syslog (not console)
- ✅ Implement health check endpoint
- ✅ Use systemd/Windows Service for auto-restart
- ✅ Implement request timeouts
- ✅ Handle signals (SIGTERM, SIGINT)

**Don't:**
- ❌ Expose directly to internet (use reverse proxy)
- ❌ Run as root/Administrator
- ❌ Serve large static files (use Nginx)
- ❌ Implement SSL yourself (use reverse proxy)
- ❌ Ignore error handling (server crashes = downtime)

---

### 4. WebXPHP - Transpiled to PHP

#### Architecture

```
.prg Source → WebXPHP Transpiler → .php Files → Apache/Nginx + PHP-FPM → Browser
```

**Process Model:**
- Harbour code transpiled to PHP once
- PHP-FPM handles execution
- Leverages existing PHP infrastructure
- No Harbour runtime needed on server

#### Transpilation Workflow

**Development:**
```batch
REM 1. Write Harbour code
REM myapp.prg

REM 2. Transpile to PHP
cd C:\xampp2025\htdocs\webx\samples
..\WebXPHP\bin\win\msvc64\webxphp.exe myapp.prg -gx -n

REM 3. Generated files:
REM    myapp.php - Main code
REM    webxphp_classes/*.php - WebX classes (if not already present)

REM 4. Deploy to web server
copy myapp.php C:\xampp\htdocs\mysite\
xcopy /E /Y ..\..\webxphp_classes C:\xampp\htdocs\mysite\webxphp_classes\
```

**Production:**
```bash
#!/bin/bash
# deploy.sh

APP="myapp"
SRC_DIR="/home/user/webx/src"
DEST_DIR="/var/www/html/mysite"

# Transpile
cd $SRC_DIR
webxphp $APP.prg -gx -n

# Deploy
cp $APP.php $DEST_DIR/
cp -r ../webxphp_classes $DEST_DIR/

# Set permissions
chown -R www-data:www-data $DEST_DIR
chmod -R 755 $DEST_DIR
```

#### PHP Index File

```php
<?php
// index.php - Entry point for WebXPHP app
require_once(__DIR__ . '/webxphp_classes/webx_all.php');
require_once(__DIR__ . '/myapp.php');

// Set headers
header('Content-Type: text/html; charset=utf-8');

// Execute main function
try {
    MAIN();
} catch (Exception $e) {
    error_log("WebX Error: " . $e->getMessage());
    http_response_code(500);
    echo "<h1>Internal Server Error</h1>";
}
?>
```

#### Apache Configuration

```apache
<VirtualHost *:80>
    ServerName mysite.com
    DocumentRoot /var/www/html/mysite

    <Directory /var/www/html/mysite>
        Options -Indexes +FollowSymLinks
        AllowOverride All
        Require all granted

        # Route all requests to index.php
        RewriteEngine On
        RewriteCond %{REQUEST_FILENAME} !-f
        RewriteCond %{REQUEST_FILENAME} !-d
        RewriteRule ^(.*)$ index.php [QSA,L]
    </Directory>

    # PHP-FPM configuration
    <FilesMatch \.php$>
        SetHandler "proxy:unix:/var/run/php/php8.1-fpm.sock|fcgi://localhost"
    </FilesMatch>
</VirtualHost>
```

#### Best Practices

**Do:**
- ✅ Version control both .prg AND .php files
- ✅ Use automated transpilation in CI/CD
- ✅ Test transpiled PHP before deployment
- ✅ Use PHP opcode cache (OPcache)
- ✅ Implement error logging
- ✅ Use PHP-FPM (not mod_php)

**Don't:**
- ❌ Edit .php files directly (changes will be overwritten!)
- ❌ Assume all Harbour features work (some don't transpile)
- ❌ Use Harbour-specific functions without testing
- ❌ Deploy without testing transpiled code

---

### 5. mod_WebX - Apache Native Module

#### Architecture

```
Browser → Apache → mod_WebX (In-Process) → WebX Classes → HTML
```

**Process Model:**
- WebX runtime loaded INTO Apache process
- No process spawning (fastest)
- Persistent in memory
- Direct Apache API access

#### Installation (Linux)

```bash
# 1. Compile mod_webx
cd /usr/src/webx/mod_webx
apxs -c -i -a mod_webx.c -lhbvm -lhbrtl -lwebx_override

# 2. Verify installation
ls -l /usr/lib/apache2/modules/mod_webx.so

# 3. Enable module
a2enmod webx

# 4. Restart Apache
systemctl restart apache2
```

#### Apache Configuration

```apache
# /etc/apache2/mods-available/webx.conf
LoadModule webx_module modules/mod_webx.so

<IfModule mod_webx.c>
    # WebX runtime configuration
    WebXLibPath /usr/lib/webx
    WebXCodePage UTF8EX
    WebXMaxMemory 256M

    # Handle .prg files
    <FilesMatch "\.prg$">
        SetHandler webx-handler
    </FilesMatch>

    # Virtual directory for WebX apps
    <Location /webx>
        SetHandler webx-handler
        WebXAppRoot /var/www/webx/apps
    </Location>
</IfModule>
```

#### Application Code

```harbour
// myapp.prg - Runs directly in Apache via mod_webx
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 800, 600, "mod_WebX App")
   oWnd:lPixel := .T.

   @ 100, 50 SAY "Running in Apache via mod_WebX!" TO oWnd SIZE 400, 30

   oWnd:Activate()
RETURN NIL
```

**No compilation needed!** Apache executes .prg directly.

#### Best Practices

**Do:**
- ✅ Preload frequently used libraries
- ✅ Implement request timeouts
- ✅ Monitor Apache memory usage
- ✅ Use MPM prefork or worker
- ✅ Implement graceful restart for code updates
- ✅ Use separate VirtualHost for WebX apps

**Don't:**
- ❌ Load untested code (crashes Apache!)
- ❌ Use blocking operations (freezes server)
- ❌ Ignore memory leaks (affects ALL requests)
- ❌ Mix with mod_php (namespace conflicts)

---

### 6. mod_harbour - Official Harbour Module

#### Architecture

```
Browser → Apache → mod_harbour → Harbour VM → .prg Execution → HTML
```

**Process Model:**
- Official Harbour project
- .prg files executed directly
- Harbour VM in Apache process
- Active community support

#### Installation

```bash
# Download mod_harbour
git clone https://github.com/FiveTechSoft/mod_harbour.git
cd mod_harbour/linux

# Compile
./build.sh

# Install
sudo cp mod_harbour.so /usr/lib/apache2/modules/
sudo cp harbour.conf /etc/apache2/mods-available/

# Enable
sudo a2enmod harbour
sudo systemctl restart apache2
```

#### Configuration

```apache
# /etc/apache2/mods-available/harbour.conf
LoadModule harbour_module /usr/lib/apache2/modules/mod_harbour.so

<IfModule harbour_module>
    <FilesMatch "\.(prg|hrb)$">
        SetHandler harbour
    </FilesMatch>
</IfModule>
```

#### WebX Integration

```harbour
// myapp.prg - WebX code runs in mod_harbour
{% LoadHRB "webx.hrb" %}  // Load WebX library

#include "WebX.ch"

FUNCTION Main()
   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   // WebX code works transparently
   LOCAL oWnd := TWindow():New(100, 100, 800, 600, "WebX + mod_harbour")
   oWnd:lPixel := .T.

   @ 100, 50 SAY "Running on mod_harbour!" TO oWnd SIZE 400, 30

   oWnd:Activate()
RETURN NIL
```

#### Best Practices

**Do:**
- ✅ Use {% %} tags for mod_harbour directives
- ✅ Compile libraries to .hrb format
- ✅ Leverage mod_harbour's built-in functions
- ✅ Follow mod_harbour documentation
- ✅ Use mod_harbour community resources
- ✅ Keep mod_harbour updated

**Don't:**
- ❌ Assume WebX-specific features work (test first!)
- ❌ Mix mod_harbour syntax with pure WebX (stay consistent)
- ❌ Ignore mod_harbour best practices

---

## Additional Compatibility Layers

### HIX - Legacy Harbour Compatibility

**Purpose:** Run older Harbour code without modification

**Use Cases:**
- Migrating legacy Clipper apps
- Third-party libraries using old syntax
- Gradual modernization

**Example:**
```harbour
#include "HIX.ch"  // Instead of WebX.ch

// Old-style commands work
SET DATE FORMAT "DD/MM/YYYY"
USE customers
BROWSE

// Old function names
cName := AllTrim(customers->name)
```

### Xailer - Visual Designer (Planned)

**Status:** Future development

**Features:**
- Drag-and-drop designer
- Property inspector
- Event handler wizard
- Code generation
- Integration with WebX classes

### MiniGui/HMG/OOHG Bridge (Planned)

**Status:** Compatibility layer in planning

**Goal:** Desktop → Web migration

**Concept:**
```harbour
// Existing MiniGui app
DEFINE WINDOW Form_1 ;
   AT 0,0 ;
   WIDTH 640 ;
   HEIGHT 480 ;
   TITLE 'MiniGui App'

   DEFINE BUTTON Button_1
      ROW 100
      COL 100
      WIDTH 100
      HEIGHT 30
      CAPTION 'Click Me'
      ACTION MsgInfo("Hello!")
   END BUTTON
END WINDOW

ACTIVATE WINDOW Form_1

// Bridge transpiles to WebX automatically!
```

### VFP Bridge (Reserved)

**Status:** Reserved for future development

**Target:** VFP developers migrating to web

**Planned Features:**
- VFP form (.scx) parser
- VFP report (.frx) converter
- VFP function aliases (CREATEOBJECT → New())
- Cursor → Array/Hash mapping
- Data environment compatibility

---

## Choosing the Right Deployment

### Decision Tree

```
Start
  │
  ├─→ Need simplest setup?
  │   └─→ WebXCGI or WebXPHP
  │
  ├─→ High traffic (>1000 req/day)?
  │   └─→ WebXFCGI or mod_WebX
  │
  ├─→ Standalone app (no web server)?
  │   └─→ WebXServer
  │
  ├─→ Shared hosting (no .exe support)?
  │   └─→ WebXPHP
  │
  ├─→ Already using mod_harbour?
  │   └─→ mod_harbour + WebX classes
  │
  └─→ Maximum performance?
      └─→ mod_WebX or mod_harbour
```

### Migration Path

**Phase 1: Development**
→ Use **WebXCGI** (simplest debugging)

**Phase 2: Testing**
→ Switch to **WebXFCGI** (production-like performance)

**Phase 3: Production**
→ Deploy with **mod_WebX** or **WebXFCGI** (maximum performance)

---

## See Also

- [AI_QUICK_START.md](AI_QUICK_START.md) - Quick primer for AI assistants
- [webx_gui_classes.md](webx_gui_classes.md) - WebX class reference
- [webx_language_rules.md](webx_language_rules.md) - Harbour syntax guide

---

© 2025 - WebX Deployment Options Guide
