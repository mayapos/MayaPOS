# MayaPOS — WebXPHP Reference Implementation
**Last Updated: February 2026**

MayaPOS is the flagship demonstration application for **WebXPHP** — a complete FiveWin/Harbour
point-of-sale system running in any browser, generated from the original `.prg` source with
a single command. No Harbour on the server. No Apache module required. Standard PHP hosting.

---

## What It Demonstrates

A real production POS application — not a toy example — transpiled from FiveWin source to PHP:

- **23 functions working**: VENTAS, FAMILIA, ARTICULO, CAMARERO, CIERRE, EMPRESA, CONFIGU, and more
- **Real DBF data**: 214 articles, 347 sales, 17 families, 14 waiters (same files as the desktop app)
- **Full interaction pipeline**:
  - Family buttons → filter articles → article click → ticket line added
  - xBrowse grids with real data, column scaling, row selection, keyboard navigation
  - Dynamic button images and captions loaded from FAMILIA.DBF memo fields
  - AJAX action chain: dialog → family DYN → article DYN (stateless PHP, stateful UI)
- **Font system**: `DEFINE FONT oFont1 SIZE 0, If(oDialog:nHeight <= 900, 14, 20) BOLD` — works
- **Resource pipeline**: 48 dialogs from .res files, 75 bitmaps extracted automatically
- **Virtual canvas**: Design at 1366×768, CSS `transform: scale()` adapts to any monitor

---

## How It's Built

```
Ventas.prg (FiveWin source)
    ↓
webxphp.exe Ventas.prg -gp -b -n -I"include;..." -o Ventas.php
    ↓
Ventas.php  ←  readable PHP ($nTotal, $oDialog, $oBrowse)
    +
webxphp_classes/  ←  protected framework (obfuscated, $local1/$local2)
    +
ventas_bootstrap.php  ←  loads only what Ventas actually uses
```

One command. No intermediate steps visible to the developer.

---

## Transpiler Status

| Metric | Value |
|--------|-------|
| Opcode coverage | 181/181 (100%) |
| Output size ratio | 7:1 vs source PCODE |
| PHP dependencies | Zero (pure PHP output) |
| Variable names (with -b) | Preserved (`$nTotal`, `$oDialog`) |
| Variable names (without -b) | Obfuscated (`$local1`, `$local2`) |
| Closures | Full `use()` clause support |
| Error handling | SEQUENCE/RECOVER/END SEQUENCE |
| Macro operations | `&cVar`, `&alias->field` |
| WITH OBJECT | Full support |

---

## Licensing Model

Three tiers. Same transpiler, same runtime. Different access.

### Runtime License — $499.99 · $199.99/update
- webxphp.exe transpiler + protected framework + lean bootstrap
- All deployment modes: PHP, CGI, FastCGI, mod_webx
- App code: obfuscated (`$local1`) · Framework: obfuscated
- 90-day support · 3 machines per license
- Automatic error reporting → proactive support

### Development License — $999.99 · $299.99/update
- Everything in Runtime
- Framework API documentation (what to call, not how it works)
- App code: readable (`$nTotal`) · Framework: obfuscated
- Priority 48-hour support
- For shops actively building new features, not just running a migrated app

### Migration License — $4,999.99 · $1,999.00/optional class update
- Everything in Developer
- ALL framework classes in readable PHP — fix bugs yourself, today
- `.ch` preprocessor files included — study command syntax, add new commands
- AI works end-to-end (no `$local1` boundary blocking context)
- OOP subclassing: overrides survive any update automatically
- Contributor model: submit fixes → ported to .prg source → next update benefits all tiers
- Class updates are optional — never required if self-sufficient

**Consulting**: $250/hour migration assistance (billed separately, any tier).

---

## Competitive Position

| Feature | Competitors | WebXPHP |
|---------|-------------|---------|
| No HTML/CSS/JS knowledge needed | ❌ | ✅ |
| Desktop-identical API (TWindow, TBrowse, etc.) | Partial | ✅ |
| Standard PHP hosting ($5/month) | ❌ | ✅ |
| .prg stays on developer's machine | ❌ | ✅ |
| Framework IP protected | N/A | ✅ |
| Automatic error reporting | ❌ | ✅ |

No direct competitor offers automatic `.prg → PHP` with a lean runtime on standard hosting.

---

## Security

WebX is secure by default. Unlike most frameworks where security is opt-in, WebX automatically
protects your application:

| Protection | What It Stops |
|------------|---------------|
| CSRF Tokens | Cross-site request forgery |
| XSS Encoding | Script injection attacks |
| Session Security | Cookie hijacking (HttpOnly) |
| AJAX Whitelist | Code injection via actions |
| JS Escaping | Parameter injection |

See [SECURITY_FEATURES.md](SECURITY_FEATURES.md) and [SECURITY.md](SECURITY.md).

---

## Source

- **Repository (WebX engine)**: https://github.com/mayapos/WebX
- **Transpiler source**: `WebXPHP/src/harbour/compiler/map2php.c`
- **Runtime**: `WebXPHP/samples/MayaPOS/webxphp_classes/webx_runtime.php`
- **Sample app**: `WebXPHP/samples/MayaPOS/`
- **Contact**: mayabuilders@gmail.com
- **Website**: https://xbasephp.com

---

*© 2026 xBasePHP.com — Built by xBase developers, for xBase developers.*
