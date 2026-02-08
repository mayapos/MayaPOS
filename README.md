# WebX - Universal xBase-to-Web Migration Platform

**Transform your desktop xBase applications into powerful web applications**

WebX is a comprehensive web development framework that enables xBase developers to build modern web applications using familiar syntax. Migrate your legacy applications to the web without complete rewrites.

**🎯 Status: BETA TESTING (February 2026)**

---

## 🌟 Why WebX?

- **Universal Compatibility** - Support for FiveWin, Harbour, xHarbour, HIX, Visual FoxPro
                                Alaska xBase++, Xalier, dBase, Clipper, FoxBase
- *Deployment Modes** - CGI, FastCGI, Apache Module, PHP, Standalone Server, Desktop
- **Production Ready** - PHP transpilation implemented (100%)
- **Rapid Migration** - Preserve your business logic while modernizing the interface
- **Battle-Tested** - Run production POS systems with 1000+ daily transactions

**Market Opportunity:** 1+ million legacy xBase applications worldwide that you can convert as SaaS

---

## 🚀 Deployment Technologies (6 Modes)

WebX offers unprecedented deployment flexibility:

### **1. WebXPHP** (PHP Transpilation) - ⚡⚡⚡ FASTEST
**Status:** ✅ **PRODUCTION READY**

Transpile xBase .prg files to native PHP for maximum performance:
```bash
webxphp myapp.prg -gx  # Generates myapp.php
```

**Benefits:**
- Works on shared hosting
- PHP Opcache optimization
- Standard PHP deployment
- Fastest execution speed

**Use for:** Production web applications

---

### **2. mod_WebX** (.hrb pre-compiled) - ⚡⚡⚡ FAST
**Status:** ✅ **PRODUCTION READY**

Execute pre-compiled .hrb files via Apache module (mod_harbour workflow):
```bash
webxphp myapp.prg -gh  # Compile to .hrb
# Deploy to Apache with MH_PRELOAD
```

**Benefits:**
- Very fast execution
- Pre-loaded WebX classes
- Persistent VM pool
- Compatible with mod_harbour

**Use for:** Production deployment (mod_harbour style)

---

### **3. mod_WebX** (.prg direct) - ⚡⚡ FAST
**Status:** ✅ **PRODUCTION READY**

Execute .prg files directly (WebX classes embedded in module):
```
http://localhost/myapp.prg  # Runs directly!
```

**Benefits:**
- Edit .prg, refresh browser
- No compilation step
- Perfect for development
- WebX classes always available

**Use for:** Development and rapid prototyping

---

### **4. WebXCGI** (.exe) - ⚡ SLOWER, but twice or more times faster than standard CGI.
**Status:** ✅ **PRODUCTION READY**

Traditional CGI executables:
```bash
xBasePHPh64_web.bat myapp  # Compile to .exe
```

**Benefits:**
- Works on any hosting with CGI
- Standalone binaries
- Simple deployment

**Use for:** Legacy systems, simple hosting

---

### **5. WebXfCGI** (FastCGI) - ⚡⚡ MEDIUM
**Status:** 🔄 **IN DEVELOPMENT**

FastCGI persistent process mode.

**Benefits:**
- Faster than CGI
- Process pooling
- Lower resource usage

**Use for:** Shared hosting with FastCGI support

---

### **6. WebXServer** (Standalone) - ⚡⚡ FAST
**Status:** 📋 **PLANNED**

Self-contained HTTP server (no Apache needed):
```bash
WebXServer.exe --port 8080
```

**Benefits:**
- No web server required
- Easy deployment
- Cross-platform

**Use for:** Standalone apps, embedded systems

---

### **7. WebXDesktop** (Headless Browser) - ⚡⚡⚡ NATIVE
**Status:** 📋 **PLANNED**

Desktop apps with web UI (Electron-style):

**Benefits:**
- Native performance
- Modern HTML5 UI
- Cross-platform desktop apps

**Use for:** Desktop applications with web technology

---

## 🔄 Framework Compatibility

WebX provides **backward compatibility** with major xBase frameworks:

### 🎯 **Flexible Development Options**

**For FiveWin Developers:**
- WebX provides compatibility with FiveWin applications
- Use your existing FiveWin License with WebX classes
- Migrate your desktop applications to the web with minimal changes
- Preserves your investment in FiveWin development

**For All Other Developers:**
- WebX includes comprehensive command infrastructure in WebX.ch
- Full xBase syntax: DEFINE WINDOW, ACTIVATE WINDOW, @ SAY, @ GET, and more
- Built on industry-standard web development practices
- No additional licensing requirements

**Both approaches provide:**
- Complete web application functionality
- Professional, responsive web interfaces
- Full database integration
- Production-ready deployment options

### ✅ **100% Production Ready**

| Framework | Version | Migration Path | Success Rate |
|-----------|---------|----------------|--------------|
| **FiveWin** | 25.12 | Direct source recompile (license required) | 95%+ |
| **Harbour** | 3.0+ | Native (WebX built on Harbour) | 100% |
| **xHarbour** | 1.3.0 | Direct source recompile | 90%+ |
| **mod_harbour** | All | mod_webx.so is mod_harbour fork | 100% |
| **HIX** | All | Compatibility layer included | 95%+ |

### 🔄 **Migration Tools Available**

| Framework | Status | Tool Chain | Timeline |
|-----------|--------|------------|----------|
| **Alaska xBase++** | Analysis Phase | Syntax converter + GUI mapper | Q1 2026 |
| **Visual FoxPro** | Design Phase | .APP decompiler + form converter | Q1 2026 |
| **Xailer** | Design Phase | .xfm form converter | Q2 2026 |
| **MiniGUI** | Design Phase | Command translator | Q2 2026 |

**Total Addressable Market:**
- FiveWin: ~50,000 apps
- Visual FoxPro: ~1,000,000 apps (Microsoft estimate)
- xBase++: ~10,000 enterprise apps
- Clipper/dBase: ~100,000 legacy apps

**WebX is the ONLY universal xBase-to-web migration platform.**

---

## 📈 Development Status (February 2026)

### Core Framework: ✅ COMPLETE

**PHP Transpilation:**
- ✅ All data types supported
- ✅ OOP system complete
- ✅ Database engine integrated
- ✅ Zero TODO comments in generated PHP

**WebX Class Library:**
- ✅ 110+ classes implemented
- ✅ 90% production-ready
- ✅ Full FiveWin API compatibility
- ✅ Layout system (TLayout, TLayoutSection)
- ✅ POS controls (Category Grid, Product Grid, Cart, NumPad)
- ✅ Advanced controls (Accordion, Carousel, Charts, Tabs)

**Runtime Libraries:**
- ✅ 2,000+ PHP function stubs for Harbour compatibility
- ✅ Harbour RTL (792 functions)
- ✅ Clipper Tools Library (200+ functions)
- ✅ NanForum Library (100+ functions)
- ✅ PCRE Regex (40+ functions)
- ✅ TIP Protocol - HTTP/SMTP/FTP (50+ functions)
- ✅ FiveWin compatibility (300+ functions)

**Deployment Infrastructure:**
- ✅ CGI execution (Windows/Linux)
- ✅ mod_webx.so Apache module
- ✅ PHP transpilation
- ✅ Build scripts (Windows/Linux)
- ✅ Comprehensive documentation

### Current Work: 🔄 IN PROGRESS

### Roadmap: 📋 UPCOMING

**Q1 2026 (Next 3 Months):**
- [ ] Visual FoxPro converter (6 weeks)
  - .APP decompiler integration
  - Form converter (.SCX → WebX)
  - Report converter (.FRX → WebX)
- [ ] Alaska xBase++ analyzer (4 weeks)
  - Syntax converter
  - GUI mapper
  - Class converter

**Q2 2026 (6 Months):**
- [ ] Xailer form converter (3 weeks)
- [ ] MiniGUI command translator (3 weeks)
- [ ] WebXfCGI completion
- [ ] WebXServer beta

**Q3 2026:**
- [ ] WebXDesktop prototype
- [ ] Automated migration service
- [ ] Commercial migration support launch

---

## 📦 What's Included

### **WebX Framework**
Complete class library for web development:
- ✅ Window and dialog management
- ✅ 110+ UI controls (buttons, inputs, grids, etc.)
- ✅ **AG-Grid integration** (enterprise-grade data grid)
- ✅ Data binding and validation
- ✅ Session management
- ✅ Database integration (DBF, SQL)
- ✅ Menu and toolbar systems
- ✅ Advanced layout management (5-panel responsive)
- ✅ POS-specific controls
- ✅ Chart and graph components
- ✅ File upload handling
- ✅ AJAX bridge (WEBX_CALL)

### **Development Tools**
- ✅ WebXPHP transpiler 
- ✅ Python Analyzer (instant bug detection)
- ✅ Build scripts (Windows/Linux)
- ✅ Debug utilities
- ✅ 30+ sample applications
- ✅ Comprehensive documentation (200+ docs)

### **Runtime Libraries**
- ✅ Pre-compiled class libraries
- ✅ Database drivers (DBFNTX, DBFCDX, DBFNSX)
- ✅ HTTP protocol handlers
- ✅ Template engines
- ✅ HIX compatibility layer

---

## 🎯 Use Cases

### **Legacy Application Modernization** (Primary)
Migrate decades-old xBase applications to the web:
- Preserve business logic (tested over decades)
- Keep existing DBF databases
- Reuse developer expertise
- No complete rewrite needed
- 95%+ code reuse for FiveWin apps

### **Cross-Platform Deployment**
Deploy to Windows, Linux, macOS servers without code changes.

### **Mobile Access**
Make desktop applications accessible from tablets/smartphones.
The nature of the source code, prevents to use of responsive pages.

### **Cloud Migration**
Move on-premise apps to AWS, Azure, Google Cloud.

### **Hybrid Deployment**
Run desktop and web versions from same codebase.

---

## 📚 Getting Started

### **Quick Start (5 Minutes)**

**1. Choose Deployment Mode:**
- **Development:** mod_WebX (.prg direct) - edit & refresh
- **Production:** WebXPHP (transpile) - fastest
- **Legacy:** WebXCGI (.exe) - simple hosting

**2. Write Your Application:**
```fivewin
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd
   PUBLIC Designed_Resolution := {1366, 768, .T.}

   DEFINE WINDOW oWnd TITLE "Hello WebX"

   @ 100, 50 SAY "Welcome to WebX!" TO oWnd
   @ 150, 50 BUTTON "Click Me" TO oWnd ACTION ShowMessage()

   ACTIVATE WINDOW oWnd
RETURN NIL

FUNCTION ShowMessage()
   ? "Button clicked!"
RETURN NIL
```

**3. Deploy:**
```bash
# WebXPHP (fastest)
webxphp myapp.prg -gx
# Access: http://localhost/myapp.php

# mod_WebX (direct .prg)
# Access: http://localhost/myapp.prg

# WebXCGI
xBasePHPh64_web.bat myapp
# Access: http://localhost/myapp.exe
```

### **Documentation**

Comprehensive guides in `docs/` folder:
- **[WEBX_DEPLOYMENT_MODES.md](docs/WEBX_DEPLOYMENT_MODES.md)** - All modes explained
- **[COMPATIBILITY_MATRIX.md](docs/COMPATIBILITY_MATRIX.md)** - Framework compatibility
- **[Quick Start Guide](docs/guides/QUICK_START.md)** - Get running in minutes
- **[API Reference](docs/reference/API_SIGNATURES.md)** - Complete class documentation
- **[Migration Guides](docs/guides/)** - Move from FiveWin, VFP, Clipper
- **[Deployment Guide](docs/guides/DEPLOYMENT_GUIDE.md)** - Production best practices
- **[Sample Applications](samples/)** - 30+ real-world examples

---

## 🏆 Production Deployments

**Real-world applications running WebX:**

### **MayaPOS Premium**
- Full-featured point of sale system
- 1000+ daily transactions
- Real-time inventory
- Multi-payment processing (CASH, CARD, SPLIT)
- Customer management
- Sales reporting

### **WebX Showcase Applications**
- CRM systems
- Dashboard analytics
- E-commerce platforms
- Healthcare management
- Manufacturing ERP
- Financial services

---

## 🏢 Commercial Support

### **MayaPOS Professional Services**

**Migration Services:**
- ✅ **Free Compatibility Analysis** - Assess your codebase
- ✅ **Migration Consulting** - Expert guidance
- ✅ **Automated Conversion** - FiveWin, VFP, xBase++ converters
- ✅ **Custom Development** - Tailored solutions
- ✅ **Training Programs** - On-site or remote
- ✅ **Priority Support** - Direct access to dev team

**Pricing Models:**
- **Per-Application:** Fixed price for single app migration
- **Enterprise License:** Unlimited apps + support
- **Time & Materials:** Hourly consulting
- **Revenue Share:** Partner program for resellers

**Contact:** mayabuilders@gmail.com
**Website:** https://www.xBasePHP.com

---

## 🛠️ System Requirements

### **Development Environment**
- Windows 10/11, Linux, or macOS
- 2GB RAM minimum (4GB recommended)
- 500MB disk space
- Any modern web browser

### **Server Requirements**

**Minimum:**
- Apache 2.4+ (for mod_webx) OR any web server (for CGI/PHP)
- Linux or Windows Server
- PHP 7.4+ (for WebXPHP deployment)
- 1GB RAM minimum

**Recommended (Production):**
- VPS or Dedicated Server
- 4GB RAM
- SSD storage
- Apache 2.4 with mod_webx.so
- PHP 8.0+ with Opcache

---

## 📖 License

**WebX Framework:**
- Commercial framework by xBasePHP.com
- Commercial license required for production
- Source code available to Enterprise licensed customers
- Royalty-free runtime distribution. Buy it once, use it forever.

**Open Source Components:**
- Harbour 3.0.0 (GPL with linking exception)
- mod_harbour (MIT License)
- Tailwind CSS (MIT License)
- Alpine.js (MIT License)

**Licensing Options:**
1. **Developer License** - Single developer, unlimited apps
3. **Enterprise License** - Source code + support
4. **OEM/Reseller** - Custom terms available

Contact: mayabuilders@gmail.com

---

## 🌍 Community

### **Resources**
- **Documentation:** [docs/](docs/)
- **Sample Applications:** [samples/](samples/)
- **GitHub (Public):** https://github.com/mayapos
- **Website:** https://xBasePHP.com
- **Forum:** https://forum.xBasePHP.com (coming soon)

### **Support Channels**
- **Email Support:**
- **Commercial Inquiries:** 
  mayabuilders@gmail.com

---

## 🔐 Security

**WebX is secure by default.** Unlike most frameworks where security is opt-in, WebX automatically protects your application:

### Automatic Protections (No Configuration Required)

| Protection | What It Stops | Status |
|------------|---------------|--------|
| **CSRF Tokens** | Cross-site request forgery | Automatic |
| **XSS Encoding** | Script injection attacks | Automatic |
| **Session Security** | Cookie hijacking (HttpOnly) | Automatic |
| **AJAX Whitelist** | Code injection via actions | Automatic |
| **JS Escaping** | Parameter injection | Automatic |

### Why This Matters

SQL doesn't protect against injection. Apache doesn't ship secure. PHP's `mysqli_real_escape_string()` exists because the language won't protect you automatically.

**WebX went further.** You have to actively *disable* protections to create a vulnerability.

### Learn More

- **[SECURITY_FEATURES.md](SECURITY_FEATURES.md)** - Detailed security documentation
- **[SECURITY.md](SECURITY.md)** - Vulnerability reporting policy

---

## 📊 Performance Benchmarks

**Production Metrics:**
Hire our own Server Hosting.
- **Requests/Second:** 1000+ (WebXPHP with Opcache)
- **Response Time:** < 50ms (average)
- **Memory Usage:** 5MB/request (WebXPHP)
- **Concurrent Users:** 100+ simultaneous
- **Uptime:** 99.9%

**Deployment Mode Comparison:**

| Mode            | Requests/Sec | Memory/Request | Response Time |
|-----------------|--------------|----------------|---------------|
| WebXPHP         | 1000+        | 5MB            | < 50ms        |
| mod_WebX (.hrb) | 520+         | 10MB           | 2ms           |
| mod_WebX (.prg) | 280+         | 10MB           | 20ms          |
| WebXfCGI        | 100+         | 15MB           | 10ms          |
| WebXCGI (.exe)  | 50-100       | 50MB           | 125ms         |

---

## 🎉 Success Metrics

**As of February 2026:**
- ✅ 110+ WebX classes (90% production-ready)
- ✅ 2,000+ runtime functions (Harbour RTL, Clipper Tools, NanForum, etc.)
- ✅ 30+ sample applications
- ✅ 200+ documentation files
- ✅ 7 deployment modes (4 production-ready)
- ✅ 5 framework converters (FiveWin, Harbour, xHarbour, HIX, mod_Harbour)
- ✅ 1,000,000+ addressable legacy applications

**Migration Success Rates:**
- FiveWin → WebX: 95%+ code reuse
- Harbour → WebX: 100% (native)
- xHarbour → WebX: 90%+ compatibility
- HIX → WebX: 95%+ (compatibility layer)

---

## 📞 Get Started Today

**Ready to modernize your xBase applications?**

---

## 🏆 Why Choose WebX?

**1. Only Universal Platform**
- No other framework supports FiveWin, VFP, xBase++, Xailer, MiniGUI
- Single codebase → multiple deployment modes

**2. Proven Technology**
- Built on Harbour 3.0 (25+ years proven)
- Running production systems today
- 1000+ daily transactions processed

**3. Investment Protection**
- Preserve decades of business logic
- Keep existing developers
- Reuse DBF databases
- No vendor lock-in

**4. Flexible Deployment**
- 7 deployment modes
- Shared hosting → Enterprise servers
- CGI → PHP → Apache Module
- Choose what fits your infrastructure

**5. Active Development**
- Approaching General Availability (Q1 2026)
- Regular updates and improvements
- Growing community
- Commercial support available

---

## 🚀 Current Status: BETA TESTING

**Final testing phase before General Availability!**

**Core Complete:**
- ✅ PHP Transpilation: 100% from Fivewin, x/harbour, hix and mod_Harbour
- ✅ Class Library: 90% production-ready (110+ classes)
- ✅ Deployment Modes: 4/7 production-ready
- ✅ Framework Compatibility: FiveWin, Harbour, xHarbour, HIX

**Final Phase (Q1 2026):**
- 📋 VFP converter development (6 weeks)
- 📋 xBase++ analyzer (4 weeks)
- 📋 General Availability announcement


---

*WebX - Bridging Desktop and Web. Preserving xBase Excellence.*

**© 2026 xBasePHP.com All rights reserved.**

**Built with ❤️ by xBase developers, for xBase developers.**

---

## 📜 Trademarks and Acknowledgments

### Trademarks

All trademarks, service marks, trade names, product names, and logos are the property of their respective owners.

**Mentioned Technologies:**
- FiveWin™ - FiveTech Software
- Visual FoxPro™ - Microsoft Corporation
- Alaska xBase++™ - Alaska Software
- Xailer™ - Xailer Software
- Harbour - Open source (GPL with linking exception)
- Apache™ - Apache Software Foundation
- All other marks are property of their respective owners

### Special Thanks

WebX stands on the foundation of exceptional open-source projects:

**Core Technologies:**
- **Harbour Project** (GPL) - The xBase compiler that makes it all possible
- **mod_harbour** (MIT) - Apache module foundation
- **Apache HTTP Server** (Apache 2.0) - Web server excellence
- **PHP** (PHP License) - Transpilation target

**Frontend Excellence:**
- **Tailwind CSS** (MIT) - Beautiful, responsive design
- **Alpine.js** (MIT) - Lightweight JavaScript framework
- **Chart.js** (MIT) - Data visualization
- **AG-Grid** (MIT) - Enterprise-grade data grid

**Community:**
- 40+ years of xBase developer innovation
- mod_harbour contributors for pioneering web integration
- All open-source maintainers whose work enables WebX

### Open Source Compliance

WebX properly attributes all open-source components:
- Full license texts included in distribution
- MIT License acknowledgments (mod_harbour, Tailwind, Alpine.js, Chart.js, AG-Grid)
- GPL compliance (Harbour linking exception)
- Apache 2.0 compliance (Apache HTTP Server)

See `LICENSE_MOD_HARBOUR.txt`, `HARBOUR_LICENSE.txt`, and `licenses/` directory.

### Disclaimer

WebX is developed by xBasePHP.com and is not affiliated with, endorsed by, or sponsored by any trademark owner mentioned herein. WebX is an independent product providing web development solutions for the xBase community.

---

## 📍 Project Information

**WebX is part of xBasePHP.com**

**Repository Status:**
- This repository (MayaPOS) is **PUBLIC** - Community showcase and documentation
- All other WebX repositories are **PRIVATE** - Development and source code

**Official Websites:**
- **xBasePHP.com** - Main project website
- **MayaPOS.com** - Commercial support and licensing

**Contact:**
- Email: mayabuilders@gmail.com
- Website: https://xbasephp.com
