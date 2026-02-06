# WebX Language Rules — ESSENTIALS (AI-Optimized)

**Created:** 2026-01-11 (Trimmed from 208KB complete guide)
**Purpose:** WebX-specific patterns NOT in standard AI training data
**Author:** Bayron Landaverry (xBasePHP.com)

---

## 📋 What's In This Guide

**This guide contains ONLY WebX-specific knowledge:**
- ✅ WebX-required patterns (Designed_Resolution, etc.)
- ✅ WebX preprocessor commands (DEFINE WINDOW, @ SAY, etc.)
- ✅ WebX class hierarchy (TWindow, TButton, TAccordion, etc.)
- ✅ FiveWin compatibility notes
- ✅ WebX deployment modes
- ✅ Common WebX patterns and templates

**This guide does NOT include basic Harbour syntax (AI already knows):**
- ❌ Basic syntax (FUNCTION, LOCAL, RETURN - AI knows this)
- ❌ Control flow (IF/ENDIF, DO WHILE - AI knows this)
- ❌ Standard functions (LEFT, RIGHT, SUBSTR - AI knows this)
- ❌ Database basics (USE, SEEK, SKIP - AI knows this)

**For standard Harbour syntax:** AI models already trained on https://harbour-project.org

---

## 🚨 CRITICAL: AI Code Generation Output Format

### Rule #1: ALWAYS Generate `.prg` Files (Harbour Source Code)

**When asked to create WebX applications:**
- ✅ Generate `.prg` files with Harbour/xBase syntax
- ✅ Use WebX classes: TWindow, TLayout, TButton, TSay, TGet, TBrowse
- ✅ Follow Harbour language rules
- ❌ NEVER create `.php`, `.html`, `.css`, or `.js` files unless explicitly requested
- ❌ NEVER create `.rc` resource files (FiveWin-specific, not used in WebX)

### WebX Compilation Workflow:

```
.prg (source) → WebX compiler → .exe → Apache CGI → HTML/CSS/JS (runtime)
```

**Key Point:** WebX generates web output AT RUNTIME, not at compile time.

You write `.prg` Harbour code. WebX classes have `GenerateHTML()` methods that create HTML/CSS/JS when the .exe runs.

### Example (Correct Approach):

```harbour
// ✅ CREATE .prg FILES - WebX generates HTML at runtime
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 800, 600, "My App")
   oWnd:lPixel := .T.

   @ 100, 50 BUTTON "Save" TO oWnd SIZE 100, 40 ACTION SaveData()

   oWnd:Activate()  // This generates HTML at runtime
RETURN NIL
```

---

## 🎯 WebX-Specific Requirements (MANDATORY)

### 1. Designed Resolution (FIRST LINE IN Main())

**MANDATORY in ALL WebX applications:**

```harbour
PUBLIC Designed_Resolution := {1366, 768, .T.}
// Format: {width, height, lPixel}
```

**Common resolutions:**
- `{1920, 1080, .T.}` - Full HD
- `{1366, 768, .T.}` - HD (most common)
- `{1280, 1024, .T.}` - Legacy 5:4
- `{1024, 768, .T.}` - XGA

**Must be FIRST executable line in Main() function** (before any window creation).

---

### 2. WebX Preprocessor Commands

These commands are WebX/FiveWin extensions, NOT standard Harbour:

```harbour
// Window creation
DEFINE WINDOW oWnd TITLE "My App" MENU oMenu

// Control creation (@ row, col syntax)
@ 100, 50 SAY "Welcome!" SIZE 400 TO oWnd
@ 150, 50 GET cName SIZE 300 TO oWnd
@ 200, 50 BUTTON "Save" SIZE 120, 40 TO oWnd ACTION SaveData()

// Window activation
ACTIVATE WINDOW oWnd
ACTIVATE WINDOW oWnd CENTERED
ACTIVATE WINDOW oWnd MAXIMIZED
```

**These expand to TWindow():New(), TSay():New(), etc. via preprocessor in WebX.ch**

---

### 3. WebX Class Hierarchy

**UI Classes (all inherit from TControl):**

```
TControl                // Base for all controls
  ├─ TWindow           // Main window container
  ├─ TButton           // Clickable button
  ├─ TGet              // Text input
  ├─ TSay              // Static label
  ├─ TMenu             // Menu bar
  ├─ TMenuItem         // Menu items
  ├─ TBrowse           // Data grid
  ├─ TAccordion        // Expandable panels (WebX-specific)
  ├─ TCarousel         // Image carousel (WebX-specific)
  ├─ TLayout           // Window partitioning (WebX-specific)
  └─ TRibbonBar        // Office-style ribbon (WebX-specific)
```

**OOP Syntax:**
```harbour
// Create window
oWnd := TWindow():New(nTop, nLeft, nBottom, nRight, cTitle)

// Create button
oBtn := TButton():New(nRow, nCol, cCaption, bAction, oWnd, nWidth, nHeight)

// Method calls
oWnd:SetTitle("New Title")
oWnd:Center()
oWnd:Activate()
```

---

### 4. FiveWin Compatibility

**WebX is FiveWin-compatible but generates web output instead of Windows GUI.**

**FiveWin patterns that work in WebX:**

```harbour
// DEFINE WINDOW (FiveWin/WebX compatible)
DEFINE WINDOW oWnd TITLE "App" MENU oMenu

// @ SAY/GET (FiveWin/WebX compatible)
@ 1, 1 SAY "Name:" OF oWnd
@ 1, 5 GET cName OF oWnd

// ACTIVATE WINDOW (FiveWin/WebX compatible)
ACTIVATE WINDOW oWnd

// Codeblocks for actions
oBtn:bAction := {|| MsgInfo("Clicked!") }

// WITH OBJECT syntax
WITH OBJECT oWnd
   :SetTitle("Updated")
   :SetForeColor(CLR_BLACK)
END WITH
```

**FiveWin patterns that DON'T work in WebX:**
- ❌ `RESOURCE` dialogs (no .rc files)
- ❌ `hWnd` handles (no window handles in web)
- ❌ Windows API calls (`SendMessage`, etc.)
- ❌ Printer classes (use web printing)

---

## 📋 WebX Standard Application Template

**Use this as starting point for ALL WebX applications:**

```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd, oMenu

   //==========================================================================
   // STEP 1: SET DESIGNED RESOLUTION (MANDATORY - FIRST LINE)
   //==========================================================================
   PUBLIC Designed_Resolution := {1366, 768, .T.}

   //==========================================================================
   // STEP 2: CREATE MENU (OPTIONAL)
   //==========================================================================
   DEFINE MENU oMenu

   MENUITEM "File" OF oMenu SUBMENU {;
      TMenuItem():New( "New",  {|| NewFile() } ),;
      TMenuItem():New( "Open", {|| OpenFile() } ),;
      TMenuItem():New( "-" ),;
      TMenuItem():New( "Exit", {|| oWnd:End() } );
   }

   //==========================================================================
   // STEP 3: DEFINE WINDOW (MANDATORY)
   //==========================================================================
   DEFINE WINDOW oWnd TITLE "My Application" MENU oMenu

   //==========================================================================
   // STEP 4: ADD CONTROLS
   //==========================================================================
   @ 100, 50 SAY "Welcome to WebX!" SIZE 400 TO oWnd

   @ 150, 50 GET cName SIZE 300 TO oWnd

   @ 200, 50 BUTTON "Save" SIZE 120, 40 TO oWnd ACTION SaveData()

   //==========================================================================
   // STEP 5: ACTIVATE WINDOW (MANDATORY)
   //==========================================================================
   ACTIVATE WINDOW oWnd CENTERED

RETURN NIL
```

---

## 🎨 WebX Advanced Controls (Not in FiveWin)

### TAccordion - Expandable Panels

```harbour
LOCAL oAccordion

oAccordion := TAccordion():New(oWnd)
oAccordion:AddPanel("Section 1", "Content for section 1")
oAccordion:AddPanel("Section 2", "Content for section 2")
oAccordion:AddPanel("Section 3", "Content for section 3")
```

### TCarousel - Image Gallery

```harbour
LOCAL oCarousel

oCarousel := TCarousel():New(oWnd, 800, 400)
oCarousel:AddImage("image1.jpg", "Title 1", "Description 1")
oCarousel:AddImage("image2.jpg", "Title 2", "Description 2")
```

### TLayout - Window Partitioning

```harbour
LOCAL oLayout

// Vertical layout (header/content/footer)
oLayout := TLayout():New(oWnd, LAYOUT_VERTICAL)
oLayout:AddSection("header", 10, .F.)   // 10% fixed
oLayout:AddSection("content", 80, .T.)  // 80% resizable
oLayout:AddSection("footer", 10, .F.)   // 10% fixed

// Horizontal layout (sidebar/main)
oLayout := TLayout():New(oWnd, LAYOUT_HORIZONTAL)
oLayout:AddSection("sidebar", 20, .F.)
oLayout:AddSection("main", 80, .T.)
```

---

## 🚀 Common WebX Patterns

### Pattern 1: Form with Validation

```harbour
FUNCTION CreateCustomerForm()
   LOCAL oWnd, cName := SPACE(50), cEmail := SPACE(100)

   PUBLIC Designed_Resolution := {1366, 768, .T.}

   DEFINE WINDOW oWnd TITLE "Customer Form"

   @ 100, 50 SAY "Name:" SIZE 100 TO oWnd
   @ 100, 150 GET cName SIZE 300 TO oWnd VALID ValidateName(cName)

   @ 150, 50 SAY "Email:" SIZE 100 TO oWnd
   @ 150, 150 GET cEmail SIZE 300 TO oWnd VALID ValidateEmail(cEmail)

   @ 250, 150 BUTTON "Save" SIZE 120, 40 TO oWnd ACTION SaveCustomer(cName, cEmail)

   ACTIVATE WINDOW oWnd CENTERED
RETURN NIL

FUNCTION ValidateName(cName)
   IF Empty(cName)
      MsgAlert("Name is required!", "Validation")
      RETURN .F.
   ENDIF
RETURN .T.
```

### Pattern 2: Browse with Data

```harbour
FUNCTION ShowCustomerBrowse()
   LOCAL oWnd, oBrw, aCustomers

   PUBLIC Designed_Resolution := {1366, 768, .T.}

   aCustomers := LoadCustomers()

   DEFINE WINDOW oWnd TITLE "Customer List"

   oBrw := TBrowse():New(100, 50, 1000, 500, oWnd)
   oBrw:SetArray(aCustomers)
   oBrw:AddColumn("ID", {|| aCustomers[oBrw:nAt][1] }, "100px")
   oBrw:AddColumn("Name", {|| aCustomers[oBrw:nAt][2] }, "300px")

   @ 650, 50 BUTTON "Edit" SIZE 120, 40 TO oWnd ACTION EditCustomer(oBrw:nAt)

   ACTIVATE WINDOW oWnd
RETURN NIL
```

### Pattern 3: Menu-Driven Application

```harbour
FUNCTION Main()
   LOCAL oWnd, oMenu

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   DEFINE MENU oMenu

   MENUITEM "File" OF oMenu SUBMENU {;
      TMenuItem():New( "Customers", {|| ShowCustomers() } ),;
      TMenuItem():New( "Orders",    {|| ShowOrders() } ),;
      TMenuItem():New( "-" ),;
      TMenuItem():New( "Exit",      {|| oWnd:End() } );
   }

   DEFINE WINDOW oWnd TITLE "Business App" MENU oMenu

   @ 200, 100 SAY "Welcome!" SIZE 600 TO oWnd

   ACTIVATE WINDOW oWnd MAXIMIZED
RETURN NIL
```

---

## 💡 WebX Deployment Modes

**6 deployment options:**

1. **WebXPHP** - Transpile to PHP
   ```bash
   webxphp myapp.prg -gx
   php myapp_index.php
   ```

2. **CGI** - Compile to .exe, run via Apache
   ```bash
   xBasePHPh64_web.bat myapp
   # Access: http://localhost/myapp.exe
   ```

3. **FastCGI** - Persistent process (better performance)
4. **Apache Module** - mod_webx.so
5. **Standalone Server** - Built-in HTTP server
6. **Docker** - Containerized deployment

**See:** `webx_deployment_options.md` for complete deployment guides.

---

## 🎨 Coding Standards

### Color Constants

```harbour
// Standard VGA colors
CLR_BLACK   := RGB(0, 0, 0)
CLR_BLUE    := RGB(0, 0, 128)
CLR_GREEN   := RGB(0, 128, 0)
CLR_RED     := RGB(128, 0, 0)
CLR_WHITE   := RGB(255, 255, 255)

// Custom colors
CLR_CUSTOM := RGB(75, 150, 225)
```

### Variable Naming (Hungarian Notation)

```harbour
LOCAL cString := ""      // c = character
LOCAL nNumber := 0       // n = numeric
LOCAL lFlag := .F.       // l = logical
LOCAL dDate := Date()    // d = date
LOCAL aArray := {}       // a = array
LOCAL hHash := {=>}      // h = hash
LOCAL oObject := NIL     // o = object
LOCAL bBlock := {|| }    // b = codeblock
```

### Code Style

```harbour
// Use WITH OBJECT for multiple property sets
WITH OBJECT oWnd
   :SetTitle("My App")
   :SetForeColor(CLR_BLACK)
   :Center()
END WITH
```

---

## 🚫 Common Pitfalls

### 1. Forgetting Designed_Resolution

```harbour
// ❌ WRONG
FUNCTION Main()
   LOCAL oWnd
   DEFINE WINDOW oWnd TITLE "App"
   ACTIVATE WINDOW oWnd
RETURN NIL

// ✅ CORRECT
FUNCTION Main()
   LOCAL oWnd
   PUBLIC Designed_Resolution := {1366, 768, .T.}
   DEFINE WINDOW oWnd TITLE "App"
   ACTIVATE WINDOW oWnd
RETURN NIL
```

### 2. Creating Web Files Instead of .prg

```harbour
// ❌ WRONG - Don't create .html files
<html>...</html>

// ✅ CORRECT - Create .prg files
#include "WebX.ch"
FUNCTION Main()
```

### 3. Not Using TO oWnd

```harbour
// ❌ WRONG
@ 100, 50 SAY "Text" SIZE 400

// ✅ CORRECT
@ 100, 50 SAY "Text" SIZE 400 TO oWnd
```

---

## 📚 Additional Resources

**WebX Documentation (in webx-ai-training/):**
- `webx_gui_classes.md` - Complete class reference
- `webx_deployment_options.md` - Deployment guides
- `webx_designer_workflow.md` - Visual designer usage

**Standard Harbour (AI already knows):**
- https://harbour-project.org/docs/ - Full Harbour documentation

**FiveWin Compatibility:**
- WebX implements FiveWin 2512 compatible APIs
- Class signatures match FiveWin
- Adapted for web (no Windows API)

---

## 🎯 Quick Reference: What's Different

| Feature | Standard Harbour | FiveWin | WebX |
|---------|-----------------|---------|------|
| Basic syntax | ✅ | ✅ | ✅ |
| TWindow class | ❌ | ✅ | ✅ |
| DEFINE WINDOW | ❌ | ✅ | ✅ |
| @ SAY/GET | ❌ | ✅ | ✅ |
| Windows API | ❌ | ✅ | ❌ |
| Web output | ❌ | ❌ | ✅ |
| Designed_Resolution | ❌ | ❌ | ✅ (required) |
| TAccordion/TCarousel | ❌ | ❌ | ✅ |

---

**Version:** 1.0 ESSENTIALS
**Created:** 2026-01-11
**Author:** Bayron Landaverry
**Company:** xBasePHP.com
**Based on:** webx_language_rules_COMPLETE.md (trimmed 208KB → 50KB)
**File Size:** ~50 KB (75% reduction from complete guide)

**Philosophy:** "AI already knows Harbour basics. Focus on what makes WebX unique." 🎯
