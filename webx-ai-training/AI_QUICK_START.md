<!-- Created: 2025-01-09 -->
<!-- Updated: 2025-01-09 - Added deployment options and skill-level guidance -->

# Quick Start for AI Assistants - WebX Development

## 30-Second Primer

You are an AI assistant helping develop **WebX web applications**. WebX is a **Harbour (xBase) framework** that generates HTML/CSS/JavaScript instead of Windows GUI.

**Key Facts:**
- Language: Harbour (xBase family, like Clipper/dBase)
- Output: HTML5/CSS3 web apps (NOT Windows desktop apps)
- Deployment: Multiple options (see below)
- FiveWin-compatible API (but generates web, not Windows GUI)

## Deployment Options (Pick Your Path)

WebX supports **6 different deployment modes**. Choose based on your infrastructure:

| Mode | Use Case | Performance | Complexity |
|------|----------|-------------|------------|
| **WebXCGI** | Traditional CGI (.exe per request) | Low | Simple |
| **WebXFCGI** | FastCGI (persistent process) | High | Medium |
| **WebXServer** | Standalone HTTP server | High | Simple |
| **WebXPHP** | Transpiled to PHP (XAMPP/Apache) | Medium | Simple |
| **mod_WebX** | Apache module (like mod_harbour) | Very High | Medium |
| **mod_harbour** | Use Harbour's mod_harbour directly | Very High | Medium |

**Additional Compatibility Layers:**
- **HIX** - Legacy compatibility layer
- **Xailer** - IDE integration (future)
- **MiniGui** - Desktop GUI to WebX bridge (planned)
- **HMG/OOHG** - Desktop GUI compatibility (planned)
- **VFP Bridge** - Visual FoxPro compatibility (reserved for future)

### Quick Decision Guide

**Starting fresh?** → Use **WebXCGI** (simplest) or **WebXPHP** (familiar to PHP developers)

**High traffic site?** → Use **WebXFCGI** or **mod_WebX**

**Standalone app?** → Use **WebXServer**

**PHP infrastructure?** → Use **WebXPHP**

**Already using mod_harbour?** → Use **mod_harbour** (compatible)

---

## Skill-Level Guidance

### 🛑 STOP: Are You Already Fluent in Harbour/xHarbour?

**If YES:** Skip sections 1-2 below. You already know the syntax. Jump to:
- [WebX Deployment Options](#webx-deployment-options-detailed) (if architecture is new to you)
- [WebX Control Syntax Cheat Sheet](#webx-control-syntax-cheat-sheet) (WebX-specific classes)
- [Designer Workflow](#designer-workflow-checklist) (if using visual designer)

**If you're experienced with Clipper/dBase/FoxPro but NEW to Harbour:** Read sections 1-2 for modern Harbour features (OOP, hashes, UTF-8, etc.)

**If you're NEW to xBase entirely:** Read everything.

### 🛑 STOP: Do You Already Know FiveWin or Other GUI Frameworks?

**If you know FiveWin:** WebX API is FiveWin-compatible! Skip syntax, go straight to:
- [WebX vs FiveWin Differences](#webx-vs-fivewin-key-differences)
- [WebX Deployment Options](#webx-deployment-options-detailed)

**If you know MiniGui/HMG/OOHG:** Similar concepts, but WebX uses FiveWin-style syntax. Review:
- [WebX Control Syntax Cheat Sheet](#webx-control-syntax-cheat-sheet)

**If you're coming from VFP (Visual FoxPro):** xBase syntax is familiar, but OOP differs. Read:
- [VFP to WebX Migration Notes](#vfp-to-webx-migration-notes)

---

## WebX Deployment Options (Detailed)

### Option 1: WebXCGI (Traditional CGI)

**How it works:** Each HTTP request spawns a .exe process

**Pros:**
- Simplest deployment
- No persistent state issues
- Easy debugging (one request = one process)
- Works with any web server (Apache, IIS, Nginx)

**Cons:**
- Slower (process startup overhead)
- Higher memory usage
- Not suitable for high-traffic sites

**When to use:**
- Learning WebX
- Low-traffic internal apps
- Simple forms/reports
- Prototyping

**Example:**
```apache
# .htaccess
Options +ExecCGI
<Files "*.exe">
    SetHandler cgi-script
</Files>
```

### Option 2: WebXFCGI (FastCGI)

**How it works:** Persistent process handles multiple requests

**Pros:**
- Much faster than CGI (no process startup)
- Lower memory footprint
- Connection pooling
- Session state in memory

**Cons:**
- More complex configuration
- Requires FastCGI support
- Debugging harder (persistent state)

**When to use:**
- Production applications
- High-traffic sites
- E-commerce platforms
- APIs with frequent requests

**Example:**
```nginx
# nginx.conf
location ~ \.exe$ {
    fastcgi_pass   127.0.0.1:9000;
    fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;
    include        fastcgi_params;
}
```

### Option 3: WebXServer (Standalone HTTP Server)

**How it works:** WebX app IS the web server (like Node.js)

**Pros:**
- No external web server needed
- Full control over HTTP handling
- Easy deployment (single .exe)
- Built-in routing and middleware

**Cons:**
- Must handle HTTP details yourself
- No automatic SSL (use reverse proxy)
- Single-threaded (unless you implement threading)

**When to use:**
- Microservices
- Internal tools
- Desktop apps with web UI
- Embedded systems

**Example:**
```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oServer := TWebXServer():New(8080)

   oServer:AddRoute("/", {|| HomePage() })
   oServer:AddRoute("/api/customers", {|| GetCustomers() })

   oServer:Start()  // Listens on port 8080
RETURN NIL
```

### Option 4: WebXPHP (Transpiled to PHP)

**How it works:** Harbour code → PHP code → Apache/Nginx

**Pros:**
- Use existing PHP infrastructure (XAMPP, cPanel, etc.)
- Familiar deployment for PHP developers
- Shared hosting compatible
- Easy debugging (read generated PHP)

**Cons:**
- Transpilation step required
- Not all Harbour features supported
- PHP runtime required
- Slightly slower than native .exe

**When to use:**
- Shared hosting environments
- Teams familiar with PHP
- Gradual migration from PHP
- Hosting providers without .exe support

**Build process:**
```batch
# Transpile to PHP
webxphp myapp.prg -gx -n

# Deploy to web server
copy myapp.php C:\xampp\htdocs\myapp\
```

### Option 5: mod_WebX (Apache Module)

**How it works:** Apache loads WebX as native module (like mod_php)

**Pros:**
- Fastest performance (no CGI overhead)
- Persistent in memory
- Direct Apache integration
- Optimal for high traffic

**Cons:**
- Complex installation
- Apache-specific
- Requires compilation
- Server restart to update code

**When to use:**
- High-traffic production sites
- Enterprise applications
- Maximum performance needed
- Apache infrastructure

**Configuration:**
```apache
# httpd.conf
LoadModule webx_module modules/mod_webx.so

<Location /webx>
    SetHandler webx-handler
</Location>
```

### Option 6: mod_harbour (Harbour's Native Module)

**How it works:** Use Harbour's official Apache module

**Pros:**
- Official Harbour project
- Battle-tested
- Active community
- Full Harbour compatibility

**Cons:**
- Apache-specific
- Requires compilation
- WebX classes must be compatible

**When to use:**
- Already using mod_harbour
- Want official Harbour support
- Need maximum compatibility
- Existing mod_harbour apps

**Integration:**
```harbour
// myapp.prg - Works with both WebX and mod_harbour
#include "WebX.ch"

FUNCTION Main()
   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   // WebX code here...

RETURN NIL
```

---

## Additional Compatibility Layers

### HIX (Legacy Compatibility)

**What it is:** Compatibility layer for older Harbour code

**Use when:**
- Migrating legacy Harbour apps
- Need older function signatures
- Third-party libraries require HIX
- Backwards compatibility critical

**Example:**
```harbour
#include "HIX.ch"  // Instead of WebX.ch

// Old-style code works
DEFINE WINDOW oWnd ...
```

### Xailer (IDE Integration) - FUTURE

**Status:** Planned integration

**What it will do:**
- Visual designer for WebX apps
- Drag-and-drop controls
- Property inspector
- Code generation

### MiniGui/HMG/OOHG Bridge - PLANNED

**Status:** Future compatibility layer

**Goal:** Convert desktop MiniGui/HMG/OOHG apps to WebX web apps

**Target use case:** Existing desktop apps → web without rewrite

### VFP Bridge (Visual FoxPro) - RESERVED

**Status:** Reserved for future development

**Goal:** VFP developers can use familiar syntax

**Potential features:**
- VFP-style form designer compatibility
- VFP function name aliases
- Cursor/table abstractions
- Report engine compatibility

**Why reserved:** Large VFP community, high demand for web migration

---

## WebX vs FiveWin (Key Differences)

### ✅ Same (Compatible)

- Method signatures (New, Activate, etc.)
- Control names (TWindow, TButton, TSay, etc.)
- Parameter order
- Codeblock syntax
- @ command positioning

### ⚠️ Different (WebX-specific)

| Feature | FiveWin | WebX |
|---------|---------|------|
| Output | Windows GUI | HTML/CSS/JS |
| Deployment | .exe on desktop | Web server |
| Resolution | Screen pixels | Designed_Resolution |
| Resources | .RC files | WebX classes |
| Painting | GDI/GDI+ | CSS/Canvas |
| Events | Windows messages | JavaScript events |

### 🆕 WebX-Only Features

- **TLayout** - Responsive flexbox layouts (no FiveWin equivalent)
- **Designed_Resolution** - Responsive scaling
- **Session management** - Built-in web sessions
- **AJAX support** - Asynchronous updates
- **Mobile-first** - Touch-friendly controls
- **CSS theming** - Visual customization

---

## VFP to WebX Migration Notes

### Familiar Concepts

| VFP | WebX Equivalent |
|-----|-----------------|
| Form Designer | TLayout Designer |
| THISFORM.AddObject() | oLayout:GetSection() |
| CREATEOBJECT() | ClassName():New() |
| .Caption | cCaption parameter |
| .Value | Variable binding via GET |
| DODEFAULT() | ::Super:Method() |
| Cursors/Tables | USE/SELECT (same!) |

### Key Differences

**VFP:**
```foxpro
PUBLIC oForm
oForm = CREATEOBJECT("MyForm")
oForm.Show()
READ EVENTS
```

**WebX:**
```harbour
FUNCTION Main()
   LOCAL oWnd

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 800, 600, "My Form")
   oWnd:lPixel := .T.

   // Add controls...

   oWnd:Activate()
RETURN NIL
```

### VFP → WebX Quick Reference

```harbour
// VFP: THISFORM.txtName.Value
// WebX: cName variable + GET control

LOCAL cName := Space(50)
@ 100, 50 GET cName TO oWnd SIZE 300, 30

// VFP: THISFORM.cmdSave.Click = SaveData
// WebX: Button with ACTION

@ 150, 50 BUTTON "Save" TO oWnd SIZE 100, 40 ACTION SaveData()

// VFP: THISFORM.grdCustomers.RecordSource = "customers"
// WebX: Browse with data array

LOCAL aBrowseData := LoadCustomers()
@ 200, 50 BROWSE oBrw DATASOURCE aBrowseData TO oWnd SIZE 600, 400
```

---

---

## 🚨 CRITICAL: Output Format Rules

### ❌ DO NOT Generate These File Types (Unless Explicitly Requested):

**NEVER create:**
- `.php` files (unless user explicitly says "transpile to PHP")
- `.html` files (WebX generates HTML at runtime)
- `.css` files (WebX uses inline styles or CSS classes)
- `.js` files (WebX handles JavaScript generation)
- `.rc` resource files (FiveWin-specific, not used in WebX)

### ✅ ALWAYS Generate These File Types:

**Default output format:**
- `.prg` files (Harbour/xBase source code)
- WebX-compatible syntax using WebX classes
- FiveWin-compatible API calls (if user has FiveWin)

### User Intent Detection:

**User says:** "Create a web application..."
→ Generate `.prg` with WebX classes (TWindow, TLayout, etc.)

**User says:** "Create a FiveWin application..."
→ Generate `.prg` with FiveWin-compatible API (still .prg, not Windows-specific)

**User says:** "Transpile this to PHP..."
→ ONLY THEN create `.php` files (using WebXPHP transpiler)

**User says:** "I need the HTML output..."
→ Explain that WebX generates HTML at runtime, show the .prg source instead

### Why This Matters:

**WebX workflow:**
```
.prg (source) → webxphp compiler → .exe → Apache CGI → HTML output
```

**NOT this:**
```
❌ .prg → .php → Apache (only if user explicitly requests WebXPHP mode)
❌ .prg → .html (WebX generates HTML dynamically, not static files)
```

### Example Responses:

**User:** "Create a login page"
**You:** ✅ Generate login.prg with TWindow, TLayout, TGet controls

**User:** "I need PHP code for this"
**You:** ✅ Generate .prg AND mention: "Run `webxphp login.prg -gx` to transpile to PHP"

**User:** "Show me the HTML output"
**You:** ✅ Explain: "WebX generates HTML at runtime. Here's the .prg source. Run it to see HTML."

---

## Essential Reading Order

### 1. If User Provides a Designer-Generated Layout

**READ FIRST:**
1. [`webx_designer_workflow.md`](webx_designer_workflow.md) - Your workflow guide
2. [`webx_gui_classes.md`](webx_gui_classes.md) - Class reference

**KEY RULES:**
- ✅ PRESERVE all layout structure (AddRow/AddColumn calls)
- ✅ ONLY modify TODO comment sections
- ✅ Use section-relative coordinates (@ 20, 20 not @ 180, 50)
- ✅ Extract business logic to helper functions
- ❌ DON'T change Designed_Resolution
- ❌ DON'T modify window or layout creation code

### 2. If User Asks for New Application

**READ FIRST:**
1. [`webx_language_rules.md`](webx_language_rules.md) (sections 1-13) - Syntax basics
2. [`webx_gui_classes.md`](webx_gui_classes.md) - Available controls

**MANDATORY Template:**
```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd

   //--------------------------------------------------------------------------
   // CRITICAL: Set Designed_Resolution to YOUR monitor resolution
   // Check Windows Display Settings → Resolution (e.g., 1920x1080, 1366x768)
   // Common values: {1920, 1080}, {1366, 768}, {2560, 1440}, {1280, 1024}
   //--------------------------------------------------------------------------
   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 800, 600, "My App")
   oWnd:lPixel := .T.

   // Add controls here

   oWnd:Activate()
RETURN NIL
```

**About Designed_Resolution:**
- **Required** in every WebX application
- Must be set to **your monitor's resolution** (not hardcoded)
- Find it: Windows Display Settings → Display resolution
- Format: `{width, height, .T.}`
- Enables responsive scaling across screen sizes

### 3. If User Asks About Harbour Syntax

**READ:**
- [`webx_language_rules.md`](webx_language_rules.md) - Complete syntax reference
- [`SPEC_webx_functions.md`](SPEC_webx_functions.md) - Function reference

---

## Critical Syntax Rules (Harbour Basics)

### Variable Declaration

```harbour
LOCAL cName := "John"      // String
LOCAL nAge := 30           // Number
LOCAL lActive := .T.       // Logical (boolean)
LOCAL dDate := Date()      // Date
LOCAL aItems := {}         // Array
LOCAL hData := {=>}        // Hash
```

**Case-insensitive:** `LOCAL` = `local` = `Local`

### Logical Values

```harbour
.T.   // True
.F.   // False
```

**NOT:**  ~~true~~, ~~false~~, ~~TRUE~~, ~~FALSE~~

### String Concatenation

```harbour
cFullName := cFirst + " " + cLast   // Use + operator
```

### Comments

```harbour
// Single-line comment
/* Multi-line
   comment */
```

### Control Flow

```harbour
IF condition
   // code
ELSEIF condition2
   // code
ELSE
   // code
ENDIF

DO CASE
CASE condition1
   // code
CASE condition2
   // code
OTHERWISE
   // code
ENDCASE

FOR i := 1 TO 10
   // code
NEXT

WHILE condition
   // code
END
```

### Codeblocks (Lambdas)

```harbour
bAction := {|| Alert("Clicked") }
bAction := {|x| x * 2 }
bAction := {|x, y| x + y }
```

---

## WebX Control Syntax Cheat Sheet

### Window

```harbour
oWnd := TWindow():New(nTop, nLeft, nBottom, nRight, cTitle)
oWnd:lPixel := .T.  // MANDATORY
oWnd:Activate()
```

### Layout

```harbour
// Row-based (vertical stack)
oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
oLayout:AddRow("header", 80, .F., "CENTER", "SPACE-BETWEEN")
oLayout:AddRow("content", 0, .F., "TOP", "START")  // 0 = flexible

// Column-based (horizontal stack)
oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "COLUMN")
oLayout:AddColumn("sidebar", 250, .F., "LEFT", "START")
oLayout:AddColumn("main", 0, .F., "CENTER", "START")  // 0 = flexible
```

### Say (Label)

```harbour
@ 100, 50 SAY "Text" TO oWnd SIZE 200, 30

// With variable
LOCAL cName := "User"
@ 100, 50 SAY {|| "Hello, " + cName } TO oWnd SIZE 300, 30
```

### Button

```harbour
@ 200, 50 BUTTON "Click Me" TO oWnd SIZE 100, 40 ACTION DoSomething()

// Inline action
@ 200, 50 BUTTON "Click Me" TO oWnd SIZE 100, 40 ;
   ACTION {|| Alert("Clicked!") }
```

### Get (Input)

```harbour
LOCAL cName := Space(50)
@ 150, 50 GET cName TO oWnd SIZE 300, 30
```

### ComboBox

```harbour
LOCAL nChoice := 1
LOCAL aOptions := {"Red", "Green", "Blue"}
@ 200, 50 COMBOBOX {|u| IF(u==NIL, nChoice, nChoice:=u) } ;
   ITEMS aOptions TO oWnd SIZE 200, 30
```

### Browse (Grid)

```harbour
LOCAL oBrw
LOCAL aHeaders := {"Name", "Age", "City"}
LOCAL aData := {{"John", 30, "NYC"}, {"Jane", 25, "LA"}}
@ 100, 50 BROWSE oBrw HEADERS aHeaders DATASOURCE aData ;
   TO oWnd SIZE 600, 400
```

---

## Layout Section Targeting

**CRITICAL:** When using TLayout, target sections for controls:

```harbour
// ✅ CORRECT
@ 20, 50 SAY "Text" TO oLayout:GetSection("header")

// ❌ WRONG
@ 20, 50 SAY "Text" TO oWnd  // Goes to window, not section!
```

**Coordinates are RELATIVE to section:**
```harbour
oLayout:AddRow("header", 80)    // Header is 80px tall
@ 20, 50 SAY "Title" TO oLayout:GetSection("header")
// Appears 20px from TOP OF HEADER (not top of window!)
```

---

## Common Patterns

### Pattern 1: Simple Form

```harbour
FUNCTION Main()
   LOCAL oWnd
   LOCAL cName := Space(50)
   LOCAL cEmail := Space(100)

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 600, 400, "Form")
   oWnd:lPixel := .T.

   @ 50, 50 SAY "Name:" TO oWnd SIZE 100, 30
   @ 50, 160 GET cName TO oWnd SIZE 300, 30

   @ 100, 50 SAY "Email:" TO oWnd SIZE 100, 30
   @ 100, 160 GET cEmail TO oWnd SIZE 300, 30

   @ 150, 200 BUTTON "Submit" TO oWnd SIZE 120, 40 ;
      ACTION SubmitForm(cName, cEmail)

   oWnd:Activate()
RETURN NIL

STATIC FUNCTION SubmitForm(cName, cEmail)
   IF Empty(cName)
      Alert("Name is required")
      RETURN .F.
   ENDIF
   Alert("Form submitted!")
RETURN .T.
```

### Pattern 2: Layout-Based App

```harbour
FUNCTION Main()
   LOCAL oWnd, oLayout

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 1200, 800, "App")
   oWnd:lPixel := .T.

   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
   oLayout:AddRow("header", 80, .F., "CENTER", "SPACE-BETWEEN")
   oLayout:AddRow("content", 0)
   oLayout:AddRow("footer", 60, .F., "CENTER", "CENTER")

   @ 25, 50 SAY "MyApp" TO oLayout:GetSection("header") SIZE 200, 30
   @ 50, 50 SAY "Content Area" TO oLayout:GetSection("content") SIZE 400, 30
   @ 20, 500 SAY "© 2025" TO oLayout:GetSection("footer") SIZE 200, 20

   oWnd:Activate()
RETURN NIL
```

---

## What NOT to Do

### ❌ Wrong: No Designed_Resolution

```harbour
FUNCTION Main()
   LOCAL oWnd := TWindow():New(0, 0, 800, 600, "App")
   // ERROR: Missing PUBLIC Designed_Resolution!
```

### ❌ Wrong: Dialog Units (Not Pixel Mode)

```harbour
oWnd:lPixel := .F.  // DON'T use dialog units!
```

### ❌ Wrong: Using true/false

```harbour
LOCAL lActive := true   // WRONG - use .T.
```

### ❌ Wrong: Using == for assignment

```harbour
cName == "John"   // WRONG - this is comparison
cName := "John"   // CORRECT - use := for assignment
```

### ❌ Wrong: Forgetting TO keyword

```harbour
@ 100, 50 SAY "Text" SIZE 200, 30  // WRONG - missing TO oWnd
```

---

## Quick Troubleshooting

### "Variable does not exist"
→ Add LOCAL declaration at top of function

### "Control not visible"
→ Check you used correct parent (oWnd or oLayout:GetSection())

### "Layout sections overlap"
→ Use section-relative coordinates, not window coordinates

### "Compilation error"
→ Check syntax: .T./.F. (not true/false), := (not =), ENDIF/NEXT/ENDCASE

### "Wrong alignment"
→ Verify AddRow/AddColumn parameters (align and justify swapped?)

---

## Designer Workflow Checklist

When user provides designer-generated code:

1. ✅ Identify layout type (ROW or COLUMN)
2. ✅ List all section names and sizes
3. ✅ Note alignment/justification for each section
4. ✅ Find all TODO comments
5. ✅ Replace TODOs with controls (preserve structure!)
6. ✅ Add LOCAL variable declarations
7. ✅ Extract functions for business logic
8. ✅ Use section-relative coordinates
9. ✅ Test coordinates fit within section boundaries
10. ✅ Verify all controls target correct sections

---

## Response Template

When enhancing a layout:

```markdown
I've enhanced your layout with the following:

**Header Section (80px fixed):**
- App title at left
- User info at right

**Content Section (flexible):**
- Search form with filters
- Browse grid (600px height)
- Action buttons

**Footer Section (60px fixed):**
- Record count display
- Copyright notice

**Variables Added:**
- cSearch (search input)
- oBrw (browse control)
- aData (grid data)

**Helper Functions:**
- SearchRecords() - Filters grid
- ShowRecord() - Displays selected item

Layout structure preserved. All coordinates section-relative.
```

---

## When in Doubt

1. **Check syntax:** [`webx_language_rules.md`](webx_language_rules.md)
2. **Check classes:** [`webx_gui_classes.md`](webx_gui_classes.md)
3. **Check workflow:** [`webx_designer_workflow.md`](webx_designer_workflow.md)
4. **Ask user:** If requirement unclear, ask before generating code

---

## Final Checklist Before Delivering Code

- [ ] All LOCAL variables declared
- [ ] All functions use STATIC or FUNCTION keyword
- [ ] All logical values use .T. or .F.
- [ ] All assignments use := operator
- [ ] All control statements have END* keywords
- [ ] Designed_Resolution is set
- [ ] oWnd:lPixel := .T. is set
- [ ] oWnd:Activate() is called
- [ ] All controls have TO clause
- [ ] Layout structure unchanged (if designer-generated)
- [ ] Section-relative coordinates used
- [ ] Business logic extracted to functions
- [ ] Code follows `personal_coding_standards.md`

---

**You're ready!** Start by reading the user's request and selecting the appropriate guide above.

© 2025 - WebX AI Assistant Quick Start
