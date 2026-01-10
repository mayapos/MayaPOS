<!-- Created: 2025-01-09 -->

# WebX Designer → AI Workflow Guide

## Purpose

This document teaches AI assistants how to work with **designer-generated WebX layouts** and enhance them with functionality while preserving the layout structure.

---

## 🚨 CRITICAL OUTPUT FORMAT RULE

### ✅ ALWAYS Generate `.prg` Files (Harbour Source Code)

**When working with WebX:**
- Generate `.prg` files with WebX classes (TWindow, TLayout, TButton, etc.)
- Use Harbour/xBase syntax
- NEVER create `.php`, `.html`, `.css`, or `.js` files unless explicitly requested
- WebX generates HTML/CSS/JS at runtime from .prg source

### ❌ DO NOT Generate Web Files Directly

**Wrong approach:**
```html
<!-- ❌ DO NOT CREATE THIS -->
<html>
  <body>
    <div class="header">...</div>
  </body>
</html>
```

**Correct approach:**
```harbour
// ✅ CREATE THIS (.prg file)
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd, oLayout

   //--------------------------------------------------------------------------
   // CRITICAL: Set to YOUR monitor resolution (Windows Display Settings)
   // Common: {1920, 1080}, {1366, 768}, {2560, 1440}, {1280, 1024}
   //--------------------------------------------------------------------------
   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 1200, 800, "MyApp")
   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
   oLayout:AddRow("header", 80)

   // WebX generates HTML automatically
   oWnd:Activate()
RETURN NIL
```

### FiveWin Compatibility

If user mentions FiveWin, still generate `.prg` with FiveWin-compatible API:
```harbour
// FiveWin-compatible .prg (still Harbour source code)
#include "FiveWin.ch"

FUNCTION Main()
   LOCAL oDlg

   DEFINE DIALOG oDlg TITLE "MyApp"

   @ 10, 10 SAY "Label"

   ACTIVATE DIALOG oDlg
RETURN NIL
```

**Key Point:** Whether WebX or FiveWin, you're ALWAYS generating `.prg` Harbour source files, NOT web files.

---

## The Workflow

```
┌─────────────────┐
│  1. Designer    │  Human designs layout visually
│  (Human)        │  → Generates .prg with TODOs
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  2. Layout.prg  │  Generated code with structure
│  (Generated)    │  → Contains section definitions
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  3. AI Enhancement│ AI reads layout + training data
│  (AI)           │  → Fills TODOs with controls
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  4. Functional  │  Complete working application
│  Application    │  → Ready to compile and run
└─────────────────┘
```

---

## Step 1: Understanding Designer Output

### Designer Tool

Location: `C:\xampp2025\htdocs\webx\tools\designer_tlayout.html`

**Features:**
- Visual section builder
- ROW/COLUMN mode toggle
- Section configuration (size, alignment, justification)
- Live preview
- Code generation
- Download .prg functionality

### Generated Code Structure

**Example Output:**
```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd, oLayout

   //--------------------------------------------------------------------------
   // SET DESIGNED RESOLUTION (MANDATORY)
   //--------------------------------------------------------------------------
   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   //--------------------------------------------------------------------------
   // CREATE WINDOW
   //--------------------------------------------------------------------------
   oWnd := TWindow():New(100, 100, 1200, 800, "MyApp")
   oWnd:lPixel := .T.

   //--------------------------------------------------------------------------
   // CREATE TLAYOUT - ROW MODE
   //--------------------------------------------------------------------------
   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
   oLayout:AddRow("header", 80, .F., "CENTER", "SPACE-BETWEEN")
   oLayout:AddRow("content", 0, .F., "TOP", "START")
   oLayout:AddRow("footer", 60, .F., "CENTER", "CENTER")
   oLayout:lBorders := .T.  // Show section borders for development

   //--------------------------------------------------------------------------
   // ADD CONTROLS TO SECTIONS
   //--------------------------------------------------------------------------
   // TODO: Add controls to "header" section
   // Example: TSay():New(10, 10, "Label", oLayout:GetSection("header"), 200, 30)
   //         TButton():New(10, 50, "Click", oLayout:GetSection("header"), 100, 30, {|| Alert("Clicked")})

   // TODO: Add controls to "content" section
   // Example: TSay():New(10, 10, "Label", oLayout:GetSection("content"), 200, 30)
   //         TButton():New(10, 50, "Click", oLayout:GetSection("content"), 100, 30, {|| Alert("Clicked")})

   // TODO: Add controls to "footer" section
   // Example: TSay():New(10, 10, "Label", oLayout:GetSection("footer"), 200, 30)
   //         TButton():New(10, 50, "Click", oLayout:GetSection("footer"), 100, 30, {|| Alert("Clicked")})

   //--------------------------------------------------------------------------
   // ACTIVATE WINDOW
   //--------------------------------------------------------------------------
   oWnd:Activate()

RETURN NIL
```

### What NOT to Change

**PRESERVE THESE SECTIONS:**
- ✅ `#include "WebX.ch"`
- ✅ `PUBLIC Designed_Resolution := {...}`
- ✅ Window creation (`TWindow():New(...)`)
- ✅ Layout creation (`TLayout():New(...)`)
- ✅ Section definitions (`AddRow`/`AddColumn` calls)
- ✅ `oWnd:Activate()` at the end
- ✅ `RETURN NIL`

**ONLY MODIFY:**
- ❌ TODO comment sections
- ❌ Add FUNCTION/PROCEDURE definitions below Main()
- ❌ Add LOCAL variable declarations at top of Main()

---

## Step 2: Reading the Layout Structure

### Section Analysis

When you receive a designer-generated .prg file, **identify these key elements:**

1. **Layout Type:** "ROW" or "COLUMN"
   ```harbour
   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")  // ROW mode
   ```

2. **Section Names and Sizes:**
   ```harbour
   oLayout:AddRow("header", 80, ...)   // Fixed 80px header
   oLayout:AddRow("content", 0, ...)   // Flexible content (takes remaining space)
   oLayout:AddRow("footer", 60, ...)   // Fixed 60px footer
   ```

3. **Alignment and Justification:**
   ```harbour
   // "header", 80, .F., "CENTER", "SPACE-BETWEEN"
   //                    ^^^^^^^^  ^^^^^^^^^^^^^^
   //                    Vertical  Distribution
   //                    alignment (left/right for items)
   ```

### Common Layout Patterns

**Pattern 1: Header-Content-Footer** (3 rows)
```harbour
oLayout:AddRow("header", 80)   // Fixed top bar
oLayout:AddRow("content", 0)   // Flexible main area
oLayout:AddRow("footer", 60)   // Fixed bottom bar
```

**Pattern 2: Sidebar-Main** (2 columns)
```harbour
oLayout:AddColumn("sidebar", 250)  // Fixed left sidebar
oLayout:AddColumn("main", 0)       // Flexible main content
```

**Pattern 3: Dashboard** (header + 3-column body)
```harbour
// Main layout (ROW)
oLayout:AddRow("header", 80)
oLayout:AddRow("body", 0)

// Nested layout in "body" (COLUMN)
oLayoutBody := TLayout():New(oLayout:GetSection("body"), 0, 0, 0, 0, "COLUMN")
oLayoutBody:AddColumn("sidebar", 200)
oLayoutBody:AddColumn("content", 0)
oLayoutBody:AddColumn("panel", 300)
```

---

## Step 3: AI Enhancement Instructions

### Rule 1: Preserve Structure, Fill TODOs

**Your task:** Replace TODO comments with functional controls.

**Example Input (from designer):**
```harbour
// TODO: Add controls to "header" section
// Example: TSay():New(10, 10, "Label", oLayout:GetSection("header"), 200, 30)
```

**Example Output (AI-enhanced):**
```harbour
// Header: Application title and logout button
@ 25, 50 SAY "Customer Management System" TO oLayout:GetSection("header") SIZE 400, 30
@ 20, 1050 BUTTON "Logout" TO oLayout:GetSection("header") SIZE 100, 40 ;
   ACTION {|| LogoutUser() }
```

### Rule 2: Use Section-Relative Coordinates

**Position controls WITHIN the section**, not from the window origin.

```harbour
// ✅ CORRECT: Coordinates relative to section
@ 20, 20 SAY "Text" TO oLayout:GetSection("content")
// Appears 20px from top, 20px from left OF THE SECTION

// ❌ WRONG: Using absolute window coordinates
@ 100, 50 SAY "Text" TO oLayout:GetSection("content")
// Might overflow section boundaries!
```

### Rule 3: Respect Section Semantics

**Header sections:** Titles, navigation, logout buttons
```harbour
@ 20, 50 SAY "MyApp" TO oLayout:GetSection("header") SIZE 200, 40
@ 20, 1050 BUTTON "Settings" TO oLayout:GetSection("header") SIZE 100, 40
```

**Content sections:** Main workspace, forms, grids
```harbour
LOCAL oBrw
@ 50, 50 BROWSE oBrw ... TO oLayout:GetSection("content") SIZE 1000, 600
```

**Footer sections:** Copyright, status, pagination
```harbour
@ 20, 500 SAY "© 2025 MyCompany" TO oLayout:GetSection("footer") SIZE 200, 20
@ 15, 900 SAY {|| "Records: " + AllTrim(Str(RecCount())) } TO oLayout:GetSection("footer")
```

**Sidebar sections:** Navigation links, filters
```harbour
@ 20, 20 BUTTON "Dashboard" TO oLayout:GetSection("sidebar") SIZE 200, 40 ACTION ShowDashboard()
@ 70, 20 BUTTON "Reports" TO oLayout:GetSection("sidebar") SIZE 200, 40 ACTION ShowReports()
```

### Rule 4: Add Helper Functions Below Main()

**Don't clutter Main()** with business logic. Extract to functions.

```harbour
FUNCTION Main()
   // ... layout code ...

   @ 100, 50 BUTTON "Save" TO oLayout:GetSection("content") SIZE 100, 40 ;
      ACTION SaveCustomer()

   oWnd:Activate()
RETURN NIL

//--------------------------------------------------------------------------
// Helper Functions
//--------------------------------------------------------------------------

STATIC FUNCTION SaveCustomer()
   // Validation
   IF Empty(cCustomerName)
      Alert("Name is required")
      RETURN .F.
   ENDIF

   // Save to database
   USE customers NEW
   APPEND BLANK
   REPLACE name WITH cCustomerName, email WITH cEmail
   COMMIT
   CLOSE

   Alert("Customer saved successfully!")
RETURN .T.

STATIC FUNCTION LogoutUser()
   IF MsgYesNo("Are you sure you want to logout?")
      // Clear session
      SessionDestroy()
      // Redirect to login
      RedirectTo("login.exe")
   ENDIF
RETURN NIL
```

### Rule 5: Declare Variables at Top of Main()

**Add LOCAL declarations** for any variables used in controls.

```harbour
FUNCTION Main()
   LOCAL oWnd, oLayout
   LOCAL cCustomerName := Space(100)  // Add this
   LOCAL cEmail := Space(100)         // Add this
   LOCAL nAge := 0                    // Add this

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   // ... rest of code ...

   @ 100, 50 GET cCustomerName TO oLayout:GetSection("content") SIZE 300, 30
   @ 150, 50 GET cEmail TO oLayout:GetSection("content") SIZE 300, 30
```

---

## Step 4: Common AI Enhancement Scenarios

### Scenario 1: Login Form

**Designer Output:**
```harbour
oLayout:AddRow("header", 100)
oLayout:AddRow("content", 0)
oLayout:AddRow("footer", 60)

// TODO: Add controls to sections
```

**AI Enhancement:**
```harbour
FUNCTION Main()
   LOCAL oWnd, oLayout
   LOCAL cUsername := Space(50)
   LOCAL cPassword := Space(50)

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 500, 400, "Login")
   oWnd:lPixel := .T.

   oLayout := TLayout():New(oWnd, 0, 0, 500, 400, "ROW")
   oLayout:AddRow("header", 100, .F., "CENTER", "CENTER")
   oLayout:AddRow("content", 0, .F., "CENTER", "CENTER")
   oLayout:AddRow("footer", 60, .F., "CENTER", "CENTER")

   // Header: App title
   @ 30, 150 SAY "Welcome to MyApp" TO oLayout:GetSection("header") SIZE 200, 40

   // Content: Login form
   @ 50, 100 SAY "Username:" TO oLayout:GetSection("content") SIZE 100, 30
   @ 50, 210 GET cUsername TO oLayout:GetSection("content") SIZE 200, 30

   @ 100, 100 SAY "Password:" TO oLayout:GetSection("content") SIZE 100, 30
   @ 100, 210 GET cPassword TO oLayout:GetSection("content") SIZE 200, 30

   @ 150, 150 BUTTON "Login" TO oLayout:GetSection("content") SIZE 120, 40 ;
      ACTION DoLogin(cUsername, cPassword)

   // Footer: Version info
   @ 20, 180 SAY "v1.0.0" TO oLayout:GetSection("footer") SIZE 100, 20

   oWnd:Activate()
RETURN NIL

STATIC FUNCTION DoLogin(cUser, cPass)
   IF Empty(cUser) .OR. Empty(cPass)
      Alert("Please enter username and password")
      RETURN .F.
   ENDIF

   // Authenticate user
   IF ValidateCredentials(cUser, cPass)
      RedirectTo("dashboard.exe")
   ELSE
      Alert("Invalid credentials")
   ENDIF
RETURN NIL
```

### Scenario 2: Data Browser with Search

**Designer Output:**
```harbour
oLayout:AddRow("toolbar", 60)
oLayout:AddRow("content", 0)
oLayout:AddRow("statusbar", 40)
```

**AI Enhancement:**
```harbour
FUNCTION Main()
   LOCAL oWnd, oLayout
   LOCAL cSearch := Space(100)
   LOCAL oBrw
   LOCAL aHeaders := {"ID", "Name", "Email", "Phone", "City"}
   LOCAL aData := LoadCustomerData()

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 1200, 800, "Customer Browser")
   oWnd:lPixel := .T.

   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
   oLayout:AddRow("toolbar", 60, .F., "CENTER", "START")
   oLayout:AddRow("content", 0, .F., "TOP", "START")
   oLayout:AddRow("statusbar", 40, .F., "CENTER", "SPACE-BETWEEN")

   // Toolbar: Search controls
   @ 15, 20 SAY "Search:" TO oLayout:GetSection("toolbar") SIZE 80, 30
   @ 15, 110 GET cSearch TO oLayout:GetSection("toolbar") SIZE 400, 30
   @ 15, 520 BUTTON "Search" TO oLayout:GetSection("toolbar") SIZE 100, 30 ;
      ACTION RefreshBrowse(oBrw, cSearch)
   @ 15, 630 BUTTON "Clear" TO oLayout:GetSection("toolbar") SIZE 100, 30 ;
      ACTION {|| cSearch := Space(100), RefreshBrowse(oBrw, "") }
   @ 15, 740 BUTTON "New Customer" TO oLayout:GetSection("toolbar") SIZE 140, 30 ;
      ACTION AddNewCustomer()

   // Content: Browse grid
   @ 20, 20 BROWSE oBrw HEADERS aHeaders DATASOURCE aData ;
      TO oLayout:GetSection("content") SIZE 1160, 680

   // Status bar: Record count
   @ 10, 20 SAY {|| "Total Records: " + AllTrim(Str(Len(aData))) } ;
      TO oLayout:GetSection("statusbar") SIZE 200, 20
   @ 10, 1000 SAY {|| Time() } TO oLayout:GetSection("statusbar") SIZE 100, 20

   oWnd:Activate()
RETURN NIL

STATIC FUNCTION LoadCustomerData()
   LOCAL aData := {}
   USE customers NEW
   WHILE !Eof()
      AAdd(aData, {customers->id, customers->name, customers->email, ;
                   customers->phone, customers->city})
      SKIP
   END
   CLOSE
RETURN aData
```

### Scenario 3: Nested Dashboard Layout

**Designer Output:**
```harbour
// Main layout
oLayout:AddRow("header", 80)
oLayout:AddRow("body", 0)

// Nested layout in body
oLayoutBody := TLayout():New(oLayout:GetSection("body"), 0, 0, 0, 0, "COLUMN")
oLayoutBody:AddColumn("sidebar", 200)
oLayoutBody:AddColumn("main", 0)
```

**AI Enhancement:**
```harbour
// Header: App title and user info
@ 25, 50 SAY "Dashboard" TO oLayout:GetSection("header") SIZE 200, 30
@ 20, 1000 SAY {|| "User: " + GetCurrentUser() } ;
   TO oLayout:GetSection("header") SIZE 150, 40

// Sidebar: Navigation menu
@ 20, 20 BUTTON "Home" TO oLayoutBody:GetSection("sidebar") SIZE 160, 40 ;
   ACTION ShowHome()
@ 70, 20 BUTTON "Customers" TO oLayoutBody:GetSection("sidebar") SIZE 160, 40 ;
   ACTION ShowCustomers()
@ 120, 20 BUTTON "Orders" TO oLayoutBody:GetSection("sidebar") SIZE 160, 40 ;
   ACTION ShowOrders()
@ 170, 20 BUTTON "Reports" TO oLayoutBody:GetSection("sidebar") SIZE 160, 40 ;
   ACTION ShowReports()

// Main content: Dynamic workspace
@ 50, 50 SAY "Welcome to Dashboard" TO oLayoutBody:GetSection("main") SIZE 400, 40
@ 120, 50 SAY "Select a menu item to begin" ;
   TO oLayoutBody:GetSection("main") SIZE 300, 30
```

---

## Step 5: AI Checklist Before Delivering Code

### ✅ Structure Preservation
- [ ] Did NOT modify window creation code
- [ ] Did NOT modify layout type (ROW/COLUMN)
- [ ] Did NOT modify section definitions (AddRow/AddColumn)
- [ ] Did NOT remove `oWnd:Activate()`
- [ ] Did NOT change `Designed_Resolution`

### ✅ Control Placement
- [ ] All controls use section-relative coordinates
- [ ] Used `TO oLayout:GetSection("name")` correctly
- [ ] Coordinates fit within section boundaries
- [ ] Controls logically placed based on section semantics

### ✅ Code Quality
- [ ] Added LOCAL declarations for all variables
- [ ] Extracted business logic to helper functions
- [ ] Used meaningful variable and function names
- [ ] Added comments explaining complex logic
- [ ] Followed Harbour syntax (from webx_language_rules.md)

### ✅ Functionality
- [ ] Controls do what user requested
- [ ] Buttons have proper ACTION codeblocks
- [ ] GETs linked to LOCAL variables
- [ ] BROWSEs have proper data sources
- [ ] Error handling where appropriate

---

## Common Mistakes to Avoid

### ❌ Mistake 1: Breaking the Layout Structure
```harbour
// WRONG: Removing sections
oLayout:AddRow("header", 80)
// oLayout:AddRow("content", 0)  ← Commented out!
oLayout:AddRow("footer", 60)
```

**Fix:** Keep all sections, even if temporarily empty.

### ❌ Mistake 2: Using Absolute Window Coordinates
```harbour
// WRONG: Positioning from window origin
@ 180, 50 SAY "Text" TO oLayout:GetSection("content")
// This assumes header is 80px + content starts at 100px = 180px
// But what if header height changes?
```

**Fix:** Always use section-relative coordinates:
```harbour
@ 20, 50 SAY "Text" TO oLayout:GetSection("content")
// 20px from top of content section (regardless of header size)
```

### ❌ Mistake 3: Forgetting Variable Declarations
```harbour
FUNCTION Main()
   LOCAL oWnd, oLayout
   // Missing: LOCAL cName := Space(50)

   @ 100, 50 GET cName TO oWnd  // cName not declared!
```

**Fix:** Declare all variables at top:
```harbour
FUNCTION Main()
   LOCAL oWnd, oLayout
   LOCAL cName := Space(50)
```

### ❌ Mistake 4: Inline Business Logic
```harbour
@ 100, 50 BUTTON "Save" TO oWnd SIZE 100, 40 ACTION {|| ;
   IF Empty(cName), Alert("Name required"), RETURN .F., ENDIF, ;
   USE customers, APPEND BLANK, REPLACE name WITH cName, COMMIT, ;
   Alert("Saved!") }
```

**Fix:** Extract to function:
```harbour
@ 100, 50 BUTTON "Save" TO oWnd SIZE 100, 40 ACTION SaveCustomer()

STATIC FUNCTION SaveCustomer()
   IF Empty(cName)
      Alert("Name required")
      RETURN .F.
   ENDIF
   USE customers
   APPEND BLANK
   REPLACE name WITH cName
   COMMIT
   Alert("Saved!")
RETURN .T.
```

---

## AI Response Template

When enhancing a designer-generated layout, use this response format:

```markdown
I've enhanced your layout with the following functionality:

**Header Section:**
- Application title
- User info display
- Logout button

**Content Section:**
- Search form with filters
- Browse grid displaying customer data
- Action buttons (Edit, Delete)

**Footer Section:**
- Record count display
- Current time

**Helper Functions Added:**
- `LoadCustomerData()` - Loads data from database
- `SearchCustomers()` - Filters grid based on search criteria
- `EditCustomer()` - Opens edit form
- `DeleteCustomer()` - Removes selected customer

**Variables Declared:**
- `cSearch` - Search input field
- `oBrw` - Browse control reference
- `aData` - Customer data array

The layout structure has been preserved exactly as designed. All controls use section-relative positioning for responsive behavior.
```

Then provide the complete enhanced code.

---

## See Also

- [webx_gui_classes.md](webx_gui_classes.md) - Complete GUI class reference
- [webx_language_rules.md](webx_language_rules.md) - Harbour syntax rules
- [tools/designer_tlayout.html](../../tools/designer_tlayout.html) - Visual layout designer
- [test/test_layout_nested.prg](../../test/test_layout_nested.prg) - Example with nested layouts

---

© 2025 - WebX Designer Workflow AI Training Guide
