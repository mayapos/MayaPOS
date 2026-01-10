# WebX - Modern Web Development for xBase Applications

**Transform your desktop xBase applications into powerful web applications**

WebX is a comprehensive web development framework that enables xBase developers to build modern web applications using familiar syntax and paradigms. Migrate your legacy applications to the web without complete rewrites.

---

## 🌟 Why WebX?

- **Familiar Syntax** - Write web applications using xBase code you already know
- **Multiple Deployment Options** - CGI, FastCGI, Apache Module, or native PHP
- **Maximum Compatibility** - Support for multiple xBase dialects and frameworks
- **Rapid Migration** - Preserve your business logic while modernizing the interface
- **Production Ready** - Built on proven web technologies

---

## 🚀 Deployment Technologies

WebX offers flexible deployment options to match your infrastructure:

### **WebXCGI**
Traditional CGI deployment for maximum compatibility. Perfect for shared hosting and simple deployments.

### **WebXfCGI** (FastCGI)
High-performance FastCGI implementation for production environments. Offers persistent processes and better resource management.

### **mod_WebX**
Native Apache module for optimal performance. Direct integration with Apache web server for enterprise-grade deployments.

### **WebXServer**
Standalone HTTP server for development and testing. No external dependencies required.

### **WebXPHP**
PHP code generation for maximum portability. Run your xBase applications anywhere PHP runs.

---

## 🔄 Compatibility

WebX provides compatibility with popular xBase dialects and frameworks:

### **Fully Supported**
- ✅ **Harbour** - Complete compatibility with Harbour language features
- ✅ **mod_Harbour** - Compatible with mod_harbour applications and APIs

### **In Progress**
- 🔧 **HIX** - HIX-compatible API implementation
- 🔧 **FiveWin** - Visual class library compatibility
- 🔧 **MiniGUI** - Extended MiniGUI support
- 🔧 **Xailer** - Xailer RAD tool compatibility
- 🔧 **xBase++** - xBase++ dialect support
- 🔧 **OHM** - Object Harbour MiniGUI integration
- 🔧 **Visual FoxPro** - VFP migration path

**Compatibility Status:** Actively expanding framework support to cover the entire xBase ecosystem.

---

## 📦 What's Included

### **WebX Framework**
Complete class library for web development including:
- Window and dialog management
- Form controls (buttons, inputs, grids, etc.)
- Data binding and validation
- Session management
- Database integration
- Menu and toolbar systems
- Layout management

### **Development Tools**
- Command-line compiler
- Debug utilities
- Code analysis tools
- Sample applications
- Comprehensive documentation

### **Runtime Libraries**
- Pre-compiled class libraries
- Database drivers
- HTTP protocol handlers
- Template engines

---

## 🎯 Use Cases

### **Legacy Application Modernization**
Migrate decades-old xBase applications to the web while preserving business logic and database structures.

### **Cross-Platform Deployment**
Deploy applications to Windows, Linux, macOS servers without code changes.

### **Mobile Access**
Make desktop applications accessible from tablets and smartphones through responsive web interfaces.

### **Cloud Migration**
Move on-premise applications to cloud platforms (AWS, Azure, Google Cloud).

### **Hybrid Deployment**
Run desktop and web versions simultaneously from the same codebase.

---

## 📚 Getting Started

### **Quick Start**

1. **Choose Your Deployment Method**
   - WebXCGI for simple hosting
   - WebXfCGI for production
   - mod_WebX for Apache integration
   - WebXPHP for PHP environments

2. **Write Your Application**
   ```harbour
   #include "WebX.ch"

   FUNCTION Main()
      LOCAL oWnd

      DEFINE WINDOW oWnd TITLE "Hello WebX"

      @ 100, 50 SAY "Welcome to WebX!" TO oWnd
      @ 150, 50 BUTTON "Click Me" TO oWnd ACTION ShowMessage()

      ACTIVATE WINDOW oWnd
   RETURN NIL
   ```

3. **Deploy to Web Server**
   - Compile your application
   - Deploy to your chosen environment
   - Access via web browser

### **Documentation**

Comprehensive guides available in the `docs/` folder:
- **Quick Start Guide** - Get running in minutes
- **API Reference** - Complete class and method documentation
- **Migration Guides** - Move from FiveWin, VFP, Clipper, etc.
- **Deployment Guide** - Production deployment best practices
- **Sample Applications** - Real-world examples

---

## 🏢 Commercial Support

### **MayaPOS Professional Services**

- **Migration Consulting** - Expert guidance for legacy application migration
- **Custom Development** - Tailored solutions for your business needs
- **Training** - On-site or remote WebX training programs
- **Priority Support** - Direct access to WebX development team
- **Compatibility Analysis** - Free assessment of your existing codebase

**Contact:** sales@mayapos.com
**Website:** https://webx.mayapos.com

---

## 🛠️ System Requirements

### **Development Environment**
- Windows, Linux, or macOS
- 2GB RAM minimum (4GB recommended)
- 500MB disk space
- Any modern web browser

### **Server Requirements**
- Apache 2.4+ (for mod_WebX) or any web server (for CGI/FastCGI)
- Linux or Windows Server
- PHP 7.4+ (for WebXPHP deployment)
- 1GB RAM minimum

---

## 📖 License

WebX is a commercial framework by MayaPOS.

- **Free for evaluation and development**
- **Commercial license required for production deployment**
- **Source code available to licensed customers**
- **Royalty-free runtime distribution**

Contact sales@mayapos.com for licensing information.

---

## 🌍 Community

### **Resources**
- **Documentation:** [docs/](docs/)
- **Sample Applications:** [samples/](samples/)
- **GitHub:** https://github.com/mayapos/WebX
- **Website:** https://webx.mayapos.com

### **Support**
- **Email:** support@mayapos.com
- **Forum:** https://forum.mayapos.com
- **Issue Tracker:** https://github.com/mayapos/WebX/issues

---

## 🔐 Security

WebX takes security seriously:
- Regular security updates
- Input validation and sanitization
- SQL injection prevention
- XSS protection
- Session security
- HTTPS support

Report security issues to: security@mayapos.com

---

## 🎉 Success Stories

**Companies using WebX in production:**
- Retail POS systems serving 1000+ daily transactions
- Healthcare management applications
- Manufacturing ERP systems
- Financial services platforms

*Join the growing community of xBase developers building modern web applications with WebX.*

---

## 📞 Get Started Today

1. **Download WebX** - Get the latest version from our website
2. **Try the Samples** - Explore working applications in `samples/`
3. **Read the Docs** - Comprehensive guides in `docs/`
4. **Build Your App** - Start migrating your application
5. **Go Live** - Deploy to production with confidence

**Ready to modernize your xBase applications?**

Contact us: sales@mayapos.com
Visit: https://webx.mayapos.com

---

*WebX - Bridging Desktop and Web. Preserving xBase Excellence.*

**© 2025 MayaPOS. All rights reserved.**
