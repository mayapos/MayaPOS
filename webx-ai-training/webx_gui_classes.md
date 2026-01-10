<!-- Created: 2025-01-09 -->

# WebX GUI Classes — AI Training Reference

## Introduction

**Purpose.** Provide AI-consumable documentation for WebX's proprietary GUI classes that generate HTML/CSS/JavaScript instead of native Windows controls.

WebX provides **FiveWin-compatible API signatures** with 100% original implementations that target web browsers instead of Windows GUI. This allows desktop xBase applications to be ported to the web with minimal code changes.

**Architecture:**
- WebX classes inherit from TControl base class
- Each class generates clean HTML5/CSS3/JavaScript
- Responsive design built-in
- Mobile-compatible output
- CGI or mod_harbour compatible

---

## Core Concepts

### Designed Resolution (MANDATORY)

**Every WebX application MUST set the designed resolution** as the first line in Main():

```harbour
FUNCTION Main()
   PUBLIC Designed_Resolution := {1920, 1080, .T.}
   // {width, height, lPixel}
```

**Common resolutions:**
- Desktop: {1920, 1080}, {1366, 768}, {1280, 1024}
- Tablet: {1024, 768}, {768, 1024}
- Mobile: {375, 667}, {414, 896}

### Pixel Mode vs Dialog Units

WebX uses **pixel mode** for precise control:

```harbour
oWnd := TWindow():New(100, 100, 800, 600, "My App")
oWnd:lPixel := .T.  // Always use pixel mode
```

### Control Positioning

All controls use **absolute positioning** within their parent container:

```harbour
@ nTop, nLeft CONTROL_TYPE ... SIZE nWidth, nHeight TO oParent
```

**Parent types:**
- `oWnd` - TWindow object (main window)
- `oLayout:GetSection("name")` - TLayout section
- `oDialog` - TDialog object (future)

---

## Class Reference

### TWindow - Main Application Window

**Purpose:** Root container for all WebX applications. Generates HTML document structure.

**Signature:**
```harbour
CLASS TWindow
   METHOD New(nTop, nLeft, nBottom, nRight, cTitle, nStyle, oMenu,
              oBrush, oIcon, oParent, lVScroll, lHScroll, nClrFore,
              nClrBack, oCursor, cBorder, lSysMenu, lCaption, lMin,
              lMax, lPixel, nExStyle, cVarName, nHelpId, lUnicode,
              nWidth, nHeight, oFont, nMenuInfo) CONSTRUCTOR

   METHOD Activate(cShowState, uLClicked, uRClicked, uMoved, uResized,
                   uPainted, p1, uInit, uUp, uDown, p2, p3, p4, p5,
                   p6, p7, uValid, p8, p9, lCentered)
ENDCLASS
```

**Essential Parameters:**
- `nTop, nLeft` - Window position (ignored if centered)
- `nBottom, nRight` OR `nWidth, nHeight` - Window size
- `cTitle` - Window title (shown in titlebar)
- `lPixel` - MUST be .T. for pixel mode

**Common Usage:**
```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 800, 600, "My Application")
   oWnd:lPixel := .T.

   // Add controls here

   oWnd:Activate()
RETURN NIL
```

**With Centering:**
```harbour
oWnd:Activate(,,,,,,,,,,,,,,,,,,, .T.)  // Last param = lCentered
```

**Generated Output:**
- Full HTML5 document structure
- Responsive CSS
- Window with titlebar and content area
- Proper CGI headers

---

### TLayout - Flexible Window Partitioning

**Purpose:** Divide windows or sections into responsive ROW or COLUMN layouts. Supports infinite nesting.

**Signature:**
```harbour
CLASS TLayout FROM TControl
   METHOD New(oParent, nTop, nLeft, nWidth, nHeight, cType) CONSTRUCTOR
   METHOD AddRow(cName, nHeight, lBorder, cAlign, cJustify)
   METHOD AddColumn(cName, nWidth, lBorder, cAlign, cJustify)
   METHOD GetSection(cName) -> oSection
ENDCLASS
```

**Parameters:**
- `oParent` - TWindow OR another TLayout section (for nesting)
- `nTop, nLeft` - Position within parent
- `nWidth, nHeight` - Total layout size (use 0 for parent-fill)
- `cType` - "ROW" (vertical stack) or "COLUMN" (horizontal stack)

**AddRow Parameters:**
- `cName` - Section identifier (e.g., "header", "content", "footer")
- `nHeight` - 0 = flexible (auto-expand), >0 = fixed pixels
- `lBorder` - .T. to show debug border (optional)
- `cAlign` - Vertical: "TOP", "CENTER", "BOTTOM" (default: "TOP")
- `cJustify` - Distribution: "START", "END", "CENTER", "SPACE-BETWEEN", "SPACE-AROUND" (default: "START")

**AddColumn Parameters:**
- `cName` - Section identifier (e.g., "sidebar", "main", "panel")
- `nWidth` - 0 = flexible (auto-expand), >0 = fixed pixels
- `lBorder` - .T. to show debug border (optional)
- `cAlign` - Horizontal: "LEFT", "CENTER", "RIGHT" (default: "LEFT")
- `cJustify` - Distribution: "START", "END", "CENTER", "SPACE-BETWEEN", "SPACE-AROUND" (default: "START")

**Example 1: Simple Row Layout**
```harbour
FUNCTION Main()
   LOCAL oWnd, oLayout

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 1200, 800, "Row Layout App")
   oWnd:lPixel := .T.

   // Create row-based layout
   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
   oLayout:AddRow("header", 80, .F., "CENTER", "SPACE-BETWEEN")
   oLayout:AddRow("content", 0, .F., "TOP", "START")  // Flexible
   oLayout:AddRow("footer", 60, .F., "CENTER", "CENTER")
   oLayout:lBorders := .T.  // Show borders during development

   // Add controls to sections
   @ 20, 50 SAY "App Title" TO oLayout:GetSection("header")
   @ 50, 50 SAY "Main Content" TO oLayout:GetSection("content")
   @ 20, 50 SAY "© 2025" TO oLayout:GetSection("footer")

   oWnd:Activate()
RETURN NIL
```

**Example 2: Column Layout**
```harbour
oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "COLUMN")
oLayout:AddColumn("sidebar", 250, .F., "LEFT", "START")
oLayout:AddColumn("main", 0, .F., "CENTER", "START")  // Flexible
oLayout:AddColumn("panel", 300, .F., "RIGHT", "START")
```

**Example 3: Nested Layouts**
```harbour
// First level: Row layout
oLayout1 := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
oLayout1:AddRow("header", 80)
oLayout1:AddRow("main", 0)    // Will contain nested layout
oLayout1:AddRow("footer", 60)

// Second level: Column layout INSIDE main section
oLayout2 := TLayout():New(oLayout1:GetSection("main"), 0, 0, 0, 0, "COLUMN")
oLayout2:AddColumn("sidebar", 250)
oLayout2:AddColumn("content", 0)  // Flexible

// Add controls to nested sections
@ 20, 20 SAY "Sidebar" TO oLayout2:GetSection("sidebar")
@ 50, 50 SAY "Content" TO oLayout2:GetSection("content")
```

**CSS Implementation:**
- Uses Flexbox for responsive layouts
- `flex: 0 0 Npx` for fixed-size sections
- `flex: 1` for flexible sections
- `position: relative` on sections for child positioning
- `align-items` and `justify-content` for alignment

**Designer Integration:**
The visual designer at [tools/designer_tlayout.html](../../tools/designer_tlayout.html) generates TLayout code with smart TODOs for AI enhancement.

---

### TSay - Static Label/Text

**Purpose:** Display non-editable text or labels.

**Signature:**
```harbour
CLASS TSay FROM TControl
   METHOD New(nRow, nCol, bText, oWnd, nWidth, nHeight, cPicture,
              lPixel, bColor, oFont, lCenter, lRight, lBorder,
              lUpdate, bWhen, lShaded, lBox, lRaised) CONSTRUCTOR
ENDCLASS
```

**Essential Parameters:**
- `nRow, nCol` - Position (top, left)
- `bText` - Text string OR codeblock that returns text
- `oWnd` - Parent (TWindow or TLayoutSection)
- `nWidth, nHeight` - Size in pixels

**Common Usage:**
```harbour
@ 100, 50 SAY "Welcome to WebX!" TO oWnd SIZE 300, 30
```

**With Variable:**
```harbour
LOCAL cName := "User"
@ 100, 50 SAY {|| "Hello, " + cName } TO oWnd SIZE 300, 30
```

**Generated Output:**
```html
<div style="position: absolute; top: 100px; left: 50px; width: 300px; height: 30px;">
   Welcome to WebX!
</div>
```

---

### TButton - Clickable Button

**Purpose:** Interactive button with click action.

**Signature:**
```harbour
CLASS TButton FROM TControl
   METHOD New(nRow, nCol, nWidth, nHeight, cCaption, bAction, oWnd,
              lPixel, oFont, lDefault, lFlat, nClrFore, nClrBack) CONSTRUCTOR
ENDCLASS
```

**Essential Parameters:**
- `nRow, nCol` - Position
- `nWidth, nHeight` - Size
- `cCaption` - Button text
- `bAction` - Codeblock executed on click
- `oWnd` - Parent

**Common Usage:**
```harbour
@ 200, 50 BUTTON "Save" TO oWnd SIZE 100, 40 ACTION SaveData()

FUNCTION SaveData()
   Alert("Data saved!")
RETURN NIL
```

**With Inline Codeblock:**
```harbour
@ 200, 50 BUTTON "Click Me" TO oWnd SIZE 100, 40 ;
   ACTION {|| MsgInfo("Button clicked!") }
```

---

### TGet - Text Input Field

**Purpose:** Editable text input control.

**Signature:**
```harbour
CLASS TGet FROM TControl
   METHOD New(nRow, nCol, bVarGet, cVarName, cPicture, oWnd,
              nWidth, nHeight, oFont, bValid, nClrFore, nClrBack) CONSTRUCTOR
ENDCLASS
```

**Essential Parameters:**
- `nRow, nCol` - Position
- `bVarGet` - Codeblock that gets/sets variable
- `cVarName` - Variable name (for reference)
- `oWnd` - Parent
- `nWidth, nHeight` - Size

**Common Usage:**
```harbour
LOCAL cName := Space(50)

@ 150, 50 GET cName TO oWnd SIZE 300, 30

// Later access: cName contains user input
```

**With Picture Clause:**
```harbour
LOCAL nAge := 0
@ 150, 50 GET nAge PICTURE "999" TO oWnd SIZE 100, 30
```

---

### TComboBox - Dropdown Selection

**Purpose:** Dropdown list for selecting from options.

**Signature:**
```harbour
CLASS TComboBox FROM TControl
   METHOD New(nRow, nCol, bSetGet, aItems, nWidth, nHeight, oWnd,
              bChange, nClrFore, nClrBack, bValid, lPixel) CONSTRUCTOR
ENDCLASS
```

**Essential Parameters:**
- `nRow, nCol` - Position
- `bSetGet` - Codeblock that gets/sets selected index
- `aItems` - Array of string options
- `nWidth, nHeight` - Size
- `oWnd` - Parent
- `bChange` - Codeblock executed on selection change

**Common Usage:**
```harbour
LOCAL nChoice := 1
LOCAL aOptions := {"Option 1", "Option 2", "Option 3"}

@ 200, 50 COMBOBOX {|u| IF(u==NIL, nChoice, nChoice:=u) } ;
   ITEMS aOptions TO oWnd SIZE 200, 30
```

---

### TBrowse - Data Grid/Table

**Purpose:** Display and navigate tabular data.

**Signature:**
```harbour
CLASS TBrowse FROM TControl
   METHOD New(nRow, nCol, nWidth, nHeight, oWnd, aHeaders, aData,
              bChange, lPixel) CONSTRUCTOR
   METHOD AddColumn(cHeader, bData, nWidth)
ENDCLASS
```

**Essential Parameters:**
- `nRow, nCol` - Position
- `nWidth, nHeight` - Grid size
- `oWnd` - Parent
- `aHeaders` - Array of column header strings
- `aData` - 2D array of data OR database alias

**Common Usage:**
```harbour
LOCAL oBrw
LOCAL aHeaders := {"Name", "Age", "City"}
LOCAL aData := {;
   {"John", 30, "New York"},;
   {"Jane", 25, "London"},;
   {"Bob", 35, "Paris"};
}

@ 100, 50 BROWSE oBrw HEADERS aHeaders DATASOURCE aData ;
   TO oWnd SIZE 600, 400
```

---

## Design Patterns

### Pattern 1: Header-Content-Footer Layout

```harbour
FUNCTION Main()
   LOCAL oWnd, oLayout

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 1200, 800, "App")
   oWnd:lPixel := .T.

   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
   oLayout:AddRow("header", 80, .F., "CENTER", "SPACE-BETWEEN")
   oLayout:AddRow("content", 0)   // Flexible - takes remaining space
   oLayout:AddRow("footer", 60, .F., "CENTER", "CENTER")

   // Header: Logo left, menu right
   @ 20, 50 SAY "MyApp" TO oLayout:GetSection("header")
   @ 20, 1000 BUTTON "Logout" TO oLayout:GetSection("header") SIZE 100, 40

   // Content: Main workspace
   @ 50, 50 SAY "Welcome!" TO oLayout:GetSection("content")

   // Footer: Centered copyright
   @ 20, 500 SAY "© 2025" TO oLayout:GetSection("footer")

   oWnd:Activate()
RETURN NIL
```

### Pattern 2: Sidebar + Main Content

```harbour
oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "COLUMN")
oLayout:AddColumn("sidebar", 250, .F., "LEFT", "START")
oLayout:AddColumn("main", 0)  // Flexible

// Sidebar navigation
@ 20, 20 BUTTON "Dashboard" TO oLayout:GetSection("sidebar") SIZE 200, 40
@ 70, 20 BUTTON "Settings" TO oLayout:GetSection("sidebar") SIZE 200, 40

// Main content area
@ 50, 50 SAY "Dashboard View" TO oLayout:GetSection("main")
```

### Pattern 3: Complex Nested Layout

```harbour
// Outer: Header + Body + Footer
oLayoutMain := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
oLayoutMain:AddRow("header", 80)
oLayoutMain:AddRow("body", 0)
oLayoutMain:AddRow("footer", 60)

// Body: Sidebar + Content + Panel
oLayoutBody := TLayout():New(oLayoutMain:GetSection("body"), 0, 0, 0, 0, "COLUMN")
oLayoutBody:AddColumn("sidebar", 200)
oLayoutBody:AddColumn("content", 0)
oLayoutBody:AddColumn("panel", 300)

// Content: Toolbar + Workspace
oLayoutContent := TLayout():New(oLayoutBody:GetSection("content"), 0, 0, 0, 0, "ROW")
oLayoutContent:AddRow("toolbar", 50)
oLayoutContent:AddRow("workspace", 0)
```

---

## AI-Native Development Workflow

### Step 1: Designer Generates Layout

Use [tools/designer_tlayout.html](../../tools/designer_tlayout.html):
1. Add sections visually
2. Configure alignment and sizes
3. Download .prg file with layout

**Generated Code:**
```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd, oLayout

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   oWnd := TWindow():New(100, 100, 1200, 800, "MyApp")
   oWnd:lPixel := .T.

   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
   oLayout:AddRow("header", 80, .F., "CENTER", "SPACE-BETWEEN")
   oLayout:AddRow("content", 0, .F., "TOP", "START")
   oLayout:AddRow("footer", 60, .F., "CENTER", "CENTER")
   oLayout:lBorders := .T.

   // TODO: Add controls to "header" section
   // Example: TSay():New(10, 10, "Label", oLayout:GetSection("header"), 200, 30)
   //         TButton():New(10, 50, "Click", oLayout:GetSection("header"), 100, 30, {|| Alert("Clicked")})

   // TODO: Add controls to "content" section
   // Example: TSay():New(10, 10, "Label", oLayout:GetSection("content"), 200, 30)
   //         TButton():New(10, 50, "Click", oLayout:GetSection("content"), 100, 30, {|| Alert("Clicked")})

   // TODO: Add controls to "footer" section
   // Example: TSay():New(10, 10, "Label", oLayout:GetSection("footer"), 200, 30)
   //         TButton():New(10, 50, "Click", oLayout:GetSection("footer"), 100, 30, {|| Alert("Clicked")})

   oWnd:Activate()
RETURN NIL
```

### Step 2: AI Enhances Layout

**User Prompt:**
> "Using this layout and the WebX AI training data, create a customer management dashboard with a search form in the header, a browse grid in the content area, and pagination controls in the footer."

**AI Response:**
The AI reads:
1. The generated layout structure
2. This webx_gui_classes.md documentation
3. webx_language_rules.md for syntax
4. Replaces TODOs with functional controls

**Result:**
```harbour
// Header: Search form
LOCAL cSearch := Space(50)
@ 20, 50 SAY "Search:" TO oLayout:GetSection("header") SIZE 100, 30
@ 20, 150 GET cSearch TO oLayout:GetSection("header") SIZE 300, 30
@ 20, 460 BUTTON "Search" TO oLayout:GetSection("header") SIZE 100, 40 ;
   ACTION SearchCustomers(cSearch)

// Content: Browse grid
LOCAL oBrw
LOCAL aHeaders := {"ID", "Name", "Email", "Phone"}
LOCAL aData := GetCustomerData()
@ 20, 20 BROWSE oBrw HEADERS aHeaders DATASOURCE aData ;
   TO oLayout:GetSection("content") SIZE 1140, 600

// Footer: Pagination
@ 15, 500 BUTTON "< Prev" TO oLayout:GetSection("footer") SIZE 80, 30 ;
   ACTION PrevPage()
@ 15, 590 SAY "Page 1 of 10" TO oLayout:GetSection("footer") SIZE 100, 30
@ 15, 700 BUTTON "Next >" TO oLayout:GetSection("footer") SIZE 80, 30 ;
   ACTION NextPage()
```

---

## Responsive Behavior

### Flexible Sections Auto-Expand

```harbour
oLayout:AddRow("content", 0)  // 0 = flexible
// Section grows/shrinks to fill available space
```

### Fixed Sections Maintain Size

```harbour
oLayout:AddRow("header", 80)  // 80px always
// Header stays 80px regardless of window size
```

### Alignment Stays Consistent

```harbour
oLayout:AddRow("footer", 60, .F., "CENTER", "SPACE-BETWEEN")
// Items stay centered vertically
// Items distributed with space between (responsive)
```

---

## Common Mistakes to Avoid

### ❌ Wrong: Forgetting Designed_Resolution
```harbour
FUNCTION Main()
   LOCAL oWnd := TWindow():New(0, 0, 800, 600, "App")
   // ERROR: No Designed_Resolution set!
```

### ✅ Correct: Always Set Resolution First
```harbour
FUNCTION Main()
   PUBLIC Designed_Resolution := {1920, 1080, .T.}
   LOCAL oWnd := TWindow():New(0, 0, 800, 600, "App")
```

### ❌ Wrong: Using Dialog Units
```harbour
oWnd:lPixel := .F.  // Don't use dialog units!
```

### ✅ Correct: Always Use Pixel Mode
```harbour
oWnd:lPixel := .T.  // Always use pixels
```

### ❌ Wrong: Window Coordinates for Layout Controls
```harbour
@ 100, 50 SAY "Text" TO oLayout:GetSection("content")
// Position is relative to section, not window!
```

### ✅ Correct: Section-Relative Coordinates
```harbour
@ 20, 20 SAY "Text" TO oLayout:GetSection("content")
// Position within section (top-left corner)
```

### ❌ Wrong: Directly Editing Generated PHP
```harbour
// Never edit webxphp_classes/*.php files!
```

### ✅ Correct: Edit Source PRG, Then Retranspile
```harbour
// 1. Edit source/classes/webx_window_simple.prg
// 2. Run: retranspile_class.bat webx_window_simple
```

---

## Build and Deployment

### Local Development Build

```batch
cd C:\xampp2025\htdocs\webx\test
xBasePHPh64_web.bat myapp
myapp.exe
```

### Production CGI Build

```batch
cd C:\xampp2025\htdocs\webx\samples
xBasePHPh64_web.bat myapp
# Deploy myapp.exe to web server CGI directory
```

### Apache Configuration (.htaccess)

```apache
Options +ExecCGI
<Files "*.exe">
    SetHandler cgi-script
</Files>
```

---

## Quick Reference

### Control Syntax Summary

```harbour
// Window
oWnd := TWindow():New(nTop, nLeft, nBottom, nRight, cTitle)
oWnd:lPixel := .T.
oWnd:Activate()

// Layout (ROW)
oLayout := TLayout():New(oWnd, 0, 0, nWidth, nHeight, "ROW")
oLayout:AddRow(cName, nHeight, lBorder, cAlign, cJustify)

// Layout (COLUMN)
oLayout := TLayout():New(oWnd, 0, 0, nWidth, nHeight, "COLUMN")
oLayout:AddColumn(cName, nWidth, lBorder, cAlign, cJustify)

// Get Section
oSection := oLayout:GetSection("sectionname")

// Say (Label)
@ nRow, nCol SAY cText TO oParent SIZE nWidth, nHeight

// Button
@ nRow, nCol BUTTON cCaption TO oParent SIZE nWidth, nHeight ACTION bAction

// Get (Input)
@ nRow, nCol GET varname TO oParent SIZE nWidth, nHeight

// ComboBox
@ nRow, nCol COMBOBOX bSetGet ITEMS aOptions TO oParent SIZE nWidth, nHeight

// Browse
@ nRow, nCol BROWSE oBrw HEADERS aHeaders DATASOURCE aData TO oParent SIZE nWidth, nHeight
```

---

## See Also

- [webx_language_rules.md](webx_language_rules.md) - Harbour syntax and semantics
- [SPEC_webx_functions.md](SPEC_webx_functions.md) - Function reference
- [personal_coding_standards.md](personal_coding_standards.md) - Code style guide
- [tools/designer_tlayout.html](../../tools/designer_tlayout.html) - Visual layout designer
- [test/test_layout_nested.prg](../../test/test_layout_nested.prg) - Nested layout example

---

© 2025 - WebX GUI Classes AI Training Reference
