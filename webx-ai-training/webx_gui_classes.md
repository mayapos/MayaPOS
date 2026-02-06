# WebX GUI Classes - AI Training Reference

**Last Updated:** 2026-01-21
**WebX Version:** 1.0.0
**Total Classes:** 110+ core classes, 16+ POS classes

## Introduction

WebX is a commercial web framework that transforms desktop xBase/Harbour applications into responsive web applications. It provides **FiveWin-compatible API signatures** with 100% original implementations targeting HTML5/CSS3/JavaScript instead of Windows GUI.

### Architecture

- All WebX classes inherit from `TControl` base class
- Each class generates clean, semantic HTML5/CSS3/JavaScript
- Responsive design and mobile compatibility built-in
- Supports both CGI and mod_harbour deployment
- Virtual canvas resolution system for automatic scaling

### Mandatory Requirements

Every WebX application **MUST** include these 5 components:

```harbour
#include "WebX.ch"                              // 1. WebX header

FUNCTION Main()
   PUBLIC Designed_Resolution := {1920, 1080, .T.}  // 2. Virtual canvas resolution

   DEFINE WINDOW oWnd TITLE "My App"            // 3. Create window

   @ 100, 50 SAY "Hello" TO oWnd                // 4. Add controls

   ACTIVATE WINDOW oWnd                         // 5. Show window
RETURN NIL
```

---

## Core Foundation Classes

### TControl - Base Control Class

**Purpose:** Abstract base class for all WebX controls.

**Key Properties:**
- `nRow, nCol` - Position (top, left in pixels)
- `nWidth, nHeight` - Dimensions
- `oWnd` - Parent window/container
- `lPixel` - Always .T. (pixel mode)
- `nId` - Unique control ID
- `lVisible` - Visibility flag

**Key Methods:**
- `New()` - Constructor
- `GenerateHTML()` - Abstract method (implemented by subclasses)
- `Refresh()` - Trigger re-render
- `Hide()` - Hide control
- `Show()` - Show control

---

### TWindow - Main Application Window

**File:** `webx_window_simple.prg`

**Purpose:** Root container for WebX applications. Generates complete HTML document structure.

**Class Definition:**
```harbour
CLASS TWindow
   DATA cCaption          // Window title
   DATA nTop, nLeft, nBottom, nRight  // Position and size
   DATA lCentered INIT .F.   // Center window in viewport
   DATA lPixel INIT .T.      // Always use pixel mode
   DATA aControls INIT {}    // Child controls array
   DATA oMenu                // Menu bar object
   DATA lScaleToViewport     // Auto-scale to viewport
   DATA nClrFore, nClrBack   // Colors
   DATA cTheme INIT "light"  // Theme: light/dark/custom
   DATA lFullScreen INIT .F. // Fullscreen mode

   METHOD New(nTop, nLeft, nBottom, nRight, cTitle, ...) CONSTRUCTOR
   METHOD Activate(cShowState, bLClicked, bRClicked, ..., lCentered)
   METHOD AddControl(oControl)
   METHOD GenerateHTML()
ENDCLASS
```

**Usage Example:**
```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   // Method 1: Constructor
   oWnd := TWindow():New(100, 100, 800, 600, "My Application")
   oWnd:lPixel := .T.

   // Method 2: DEFINE WINDOW command (recommended)
   DEFINE WINDOW oWnd TITLE "My Application" SIZE 1200, 800

   // Add controls here
   @ 100, 50 SAY "Welcome to WebX!" TO oWnd SIZE 300, 30

   // Activate with centering
   ACTIVATE WINDOW oWnd CENTERED
RETURN NIL
```

**Generated Output:**
- Full HTML5 DOCTYPE
- Responsive viewport meta tags
- Embedded CSS framework (Tailwind CSS)
- Window container with titlebar
- Theme support (light/dark toggle)
- Proper CGI/mod_harbour headers

---

## Layout and Container Classes

### TLayout - Flexible Layout Container

**File:** `webx_layout.prg`

**Purpose:** Divide windows into responsive ROW or COLUMN sections using Flexbox. Supports infinite nesting.

**Class Definition:**
```harbour
CLASS TLayout FROM TControl
   DATA cType          // "ROW" or "COLUMN"
   DATA aSections INIT {}  // Array of TLayoutSection objects
   DATA lBorders INIT .F.  // Show debug borders

   METHOD New(oParent, nTop, nLeft, nWidth, nHeight, cType) CONSTRUCTOR
   METHOD AddRow(cName, nHeight, lBorder, cAlign, cJustify)
   METHOD AddColumn(cName, nWidth, lBorder, cAlign, cJustify)
   METHOD GetSection(cName) -> oSection
   METHOD GenerateHTML()
ENDCLASS
```

**Parameters:**
- `oParent` - Parent window or another TLayoutSection (for nesting)
- `nTop, nLeft` - Position within parent
- `nWidth, nHeight` - Total layout size (0 = fill parent)
- `cType` - "ROW" (vertical stack) or "COLUMN" (horizontal)

**AddRow/AddColumn:**
- `cName` - Section identifier (e.g., "header", "content")
- `nHeight/nWidth` - 0 = flexible (auto-expand), >0 = fixed pixels
- `lBorder` - .T. to show debug borders
- `cAlign` - Alignment: "TOP"/"CENTER"/"BOTTOM" (rows), "LEFT"/"CENTER"/"RIGHT" (columns)
- `cJustify` - Distribution: "START", "END", "CENTER", "SPACE-BETWEEN", "SPACE-AROUND"

**Usage Example:**
```harbour
// Header-Content-Footer layout
oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
oLayout:AddRow("header", 80, .F., "CENTER", "SPACE-BETWEEN")  // Fixed 80px
oLayout:AddRow("content", 0, .F., "TOP", "START")             // Flexible
oLayout:AddRow("footer", 60, .F., "CENTER", "CENTER")         // Fixed 60px

// Add controls to sections
@ 20, 50 SAY "App Title" TO oLayout:GetSection("header")
@ 50, 50 SAY "Main Content" TO oLayout:GetSection("content")
@ 20, 500 SAY "© 2025" TO oLayout:GetSection("footer")
```

**Nesting Example:**
```harbour
// Outer: Row layout (header/body/footer)
oMain := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
oMain:AddRow("header", 80)
oMain:AddRow("body", 0)
oMain:AddRow("footer", 60)

// Inner: Column layout inside body (sidebar/content/panel)
oBody := TLayout():New(oMain:GetSection("body"), 0, 0, 0, 0, "COLUMN")
oBody:AddColumn("sidebar", 200)
oBody:AddColumn("content", 0)  // Flexible
oBody:AddColumn("panel", 300)

// Add controls to nested sections
@ 20, 20 SAY "Sidebar" TO oBody:GetSection("sidebar")
@ 50, 50 SAY "Content" TO oBody:GetSection("content")
```

---

### TLayoutSection - Layout Section Container

**File:** `webx_layout_section.prg`

**Purpose:** Individual section within TLayout. Acts as parent for child controls.

**Class Definition:**
```harbour
CLASS TLayoutSection FROM TControl
   DATA cName          // Section name
   DATA nSize          // Size (0=flexible, >0=fixed)
   DATA cAlign         // Alignment
   DATA cJustify       // Justification
   DATA lBorder        // Show border
   DATA aControls INIT {}  // Child controls

   METHOD New(cName, nSize, lBorder, cAlign, cJustify)
   METHOD AddControl(oControl)
   METHOD GenerateHTML()
ENDCLASS
```

**Note:** Users typically don't create TLayoutSection directly. Use `TLayout:GetSection(cName)` to get reference.

---

### TPanel - Generic Panel Container

**File:** `webx_panel.prg`

**Purpose:** Simple rectangular container with optional border and background.

**Usage:**
```harbour
@ 100, 100 PANEL oPanel OF oWnd SIZE 400, 300 BORDER RAISED
```

---

### TDialog - Modal Dialog

**File:** `webx_dialog.prg`

**Purpose:** Modal popup dialog window.

**Usage:**
```harbour
DEFINE DIALOG oDlg TITLE "Settings" SIZE 400, 300

@ 50, 50 SAY "Name:" OF oDlg
@ 50, 150 GET cName OF oDlg SIZE 200, 30

ACTIVATE DIALOG oDlg CENTERED
```

---

## Basic Controls

### TSay - Static Label/Text

**File:** `webx_say.prg`

**Purpose:** Display non-editable text or labels.

**Class Definition:**
```harbour
CLASS TSay FROM TControl
   DATA cText          // Text to display
   DATA bText          // Codeblock that returns text
   DATA cPicture       // Picture format
   DATA lCenter        // Center alignment
   DATA lRight         // Right alignment
   DATA oFont          // Font object

   METHOD New(nRow, nCol, bText, oWnd, nWidth, nHeight, ...) CONSTRUCTOR
   METHOD GenerateHTML()
ENDCLASS
```

**Usage Examples:**
```harbour
// Simple text
@ 100, 50 SAY "Welcome to WebX!" TO oWnd SIZE 300, 30

// With variable (codeblock)
LOCAL cName := "User"
@ 100, 50 SAY {|| "Hello, " + cName } TO oWnd SIZE 300, 30

// With PROMPT keyword
@ 100, 50 SAY PROMPT "Label:" TO oWnd SIZE 100, 30

// Centered text
@ 100, 50 SAY "Centered" TO oWnd SIZE 300, 30 CENTERED
```

---

### TGet - Text Input Field

**File:** `webx_get.prg`

**Purpose:** Editable text input control for data entry.

**Class Definition:**
```harbour
CLASS TGet FROM TControl
   DATA bSetGet        // Codeblock to get/set value
   DATA cVarName       // Variable name
   DATA cPicture       // Input mask
   DATA bValid         // Validation codeblock
   DATA bWhen          // When active codeblock
   DATA lReadOnly      // Read-only flag
   DATA lPassword      // Password field

   METHOD New(nRow, nCol, bSetGet, oWnd, nWidth, nHeight, ...) CONSTRUCTOR
   METHOD GenerateHTML()
ENDCLASS
```

**Usage Examples:**
```harbour
// Simple text input
LOCAL cName := Space(50)
@ 150, 50 GET cName TO oWnd SIZE 300, 30

// With picture clause
LOCAL nAge := 0
@ 150, 50 GET nAge PICTURE "999" TO oWnd SIZE 100, 30

// Password field
LOCAL cPassword := Space(20)
@ 150, 50 GET cPassword TO oWnd SIZE 200, 30 PASSWORD

// With validation
@ 150, 50 GET cEmail TO oWnd SIZE 300, 30 ;
   VALID {|| "@" $ cEmail }
```

---

### TButton - Clickable Button

**File:** `webx_button.prg`

**Purpose:** Interactive button with click action.

**Class Definition:**
```harbour
CLASS TButton FROM TControl
   DATA cCaption       // Button text
   DATA bAction        // Click action codeblock
   DATA lDefault       // Default button
   DATA lFlat          // Flat style
   DATA nClrFore, nClrBack  // Colors

   METHOD New(nRow, nCol, nWidth, nHeight, cCaption, bAction, ...) CONSTRUCTOR
   METHOD GenerateHTML()
ENDCLASS
```

**Usage Examples:**
```harbour
// Simple button
@ 200, 50 BUTTON "Save" TO oWnd SIZE 100, 40 ACTION SaveData()

// With inline codeblock
@ 200, 50 BUTTON "Click Me" TO oWnd SIZE 100, 40 ;
   ACTION {|| MsgInfo("Button clicked!") }

// Flat style
@ 200, 50 BUTTON "Cancel" TO oWnd SIZE 100, 40 FLAT

// OF syntax (FiveWin compatible)
@ 200, 50 BUTTON "OK" OF oWnd SIZE 100, 40 ACTION oDlg:End()
```

---

### TCheckBox - Checkbox Control

**File:** `webx_checkbox.prg`

**Purpose:** Toggle checkbox for boolean values.

**Usage:**
```harbour
LOCAL lAccept := .F.

@ 200, 50 CHECKBOX oCheck VAR lAccept ;
   PROMPT "I accept the terms" OF oWnd ;
   ON CHANGE {|| ValidateForm() }
```

---

### TComboBox - Dropdown Selection

**File:** `webx_combobox.prg`

**Purpose:** Dropdown list for selecting from predefined options.

**Usage:**
```harbour
LOCAL nChoice := 1
LOCAL aOptions := {"Option 1", "Option 2", "Option 3"}

@ 200, 50 COMBOBOX oCombo VAR nChoice ;
   ITEMS aOptions OF oWnd SIZE 200, 30 ;
   ON CHANGE {|| ProcessChoice(nChoice) }
```

---

### TListBox - List Box

**File:** `webx_listbox.prg`

**Purpose:** Scrollable list with single or multiple selection.

**Usage:**
```harbour
LOCAL nSelected := 1
LOCAL aItems := {"Item 1", "Item 2", "Item 3"}

@ 200, 50 LISTBOX oList VAR nSelected ;
   ITEMS aItems OF oWnd SIZE 200, 150 MULTIPLE
```

---

### TRadio - Radio Button Group

**File:** `webx_radio.prg`

**Purpose:** Mutually exclusive options (radio buttons).

**Usage:**
```harbour
LOCAL nOption := 1

@ 200, 50 RADIO oRadio VAR nOption ;
   ITEMS "Option 1", "Option 2", "Option 3" ;
   OF oWnd SIZE 200, 100 VERTICAL
```

---

## Advanced Input Controls

### TDatePicker - Date Picker

**File:** `webx_datepicker.prg`

**Purpose:** Calendar-based date selection.

**Usage:**
```harbour
LOCAL dDate := Date()

@ 200, 50 DATEPICKER oDate VAR dDate OF oWnd SIZE 200, 30 ;
   ON CHANGE {|| ValidateDate(dDate) }
```

---

### TMultiGet - Multi-line Text Editor

**File:** `webx_multiget.prg`

**Purpose:** Multi-line text area for large text input.

**Usage:**
```harbour
LOCAL cNotes := Space(500)

@ 200, 50 GET cNotes OF oWnd SIZE 400, 200 MULTILINE
```

---

### TRichEdit - Rich Text Editor

**File:** `webx_richedit.prg`

**Purpose:** WYSIWYG rich text editor with formatting.

**Usage:**
```harbour
@ 200, 50 RICHEDIT oEdit OF oWnd SIZE 600, 400
```

---

### TCodeEditor - Code Editor

**File:** `webx_codeeditor.prg`

**Purpose:** Syntax-highlighted code editor (Monaco/Ace editor).

**Usage:**
```harbour
@ 200, 50 CODEEDITOR oCode OF oWnd SIZE 800, 600 LANGUAGE "harbour"
```

---

## Data Display Controls

### TBrowse - Data Grid/Table

**File:** `webx_browse.prg`

**Purpose:** Display and navigate tabular data (basic grid).

**Usage:**
```harbour
LOCAL oBrw
LOCAL aHeaders := {"Name", "Age", "City"}
LOCAL aData := {;
   {"John", 30, "New York"},;
   {"Jane", 25, "London"};
}

@ 100, 50 BROWSE oBrw HEADERS aHeaders ;
   DATASOURCE aData TO oWnd SIZE 600, 400
```

---

### TXBrowse - Enhanced Browse

**File:** `webx_xbrowse.prg`

**Purpose:** Advanced data grid with sorting, filtering, editing.

**Usage:**
```harbour
@ 100, 50 XBROWSE oXBrw OF oWnd SIZE 800, 500 EDITABLE MULTISELECT

oXBrw:AddColumn("Name", {|| CUSTOMERS->NAME}, 200)
oXBrw:AddColumn("Email", {|| CUSTOMERS->EMAIL}, 250)
```

---

### TDataRow - Data Row Display

**File:** `webx_datarow.prg`

**Purpose:** Display single data record in form layout.

---

## Modern UI Components

### TAccordion - Collapsible Panels

**File:** `webx_accordion.prg` (basic), `webx_accordion_enhanced.prg` (enhanced)

**Purpose:** Collapsible accordion panels for organizing content.

**Usage:**
```harbour
@ 100, 50 ACCORDION oAcc OF oWnd SIZE 400, 500

oAcc:AddPanel("Section 1", "Content for section 1", .T.)
oAcc:AddPanel("Section 2", "Content for section 2", .F.)
oAcc:AddPanel("Section 3", "Content for section 3", .F.)
```

---

### TCard - Card Container

**File:** `webx_card.prg`

**Purpose:** Material Design card with header, body, footer.

**Usage:**
```harbour
@ 100, 100 CARD oCard OF oWnd SIZE 300, 400 ;
   TITLE "My Card" ;
   SHADOW MEDIUM ;
   COLOR BLUE_LIGHT
```

---

### TCarousel - Image Carousel

**File:** `webx_carousel.prg`

**Purpose:** Image slider/carousel with navigation.

**Usage:**
```harbour
@ 100, 50 CAROUSEL oCarousel OF oWnd SIZE 800, 400

oCarousel:AddSlide("images/slide1.jpg", "Slide 1")
oCarousel:AddSlide("images/slide2.jpg", "Slide 2")
```

---

### TChart - Charts/Graphs

**File:** `webx_chart.prg`

**Purpose:** Charts using Chart.js (bar, line, pie, doughnut).

**Usage:**
```harbour
@ 100, 50 CHART oChart OF oWnd SIZE 600, 400 ;
   TYPE "bar" ;
   TITLE "Sales Data"

oChart:SetData({"Jan", "Feb", "Mar"}, {100, 200, 150})
```

---

### TModal - Modal Dialog

**File:** `webx_modal.prg`

**Purpose:** Bootstrap-style modal popup.

**Usage:**
```harbour
@ 0, 0 MODAL oModal OF oWnd SIZE 500, 300 ;
   TITLE "Confirm Action"

@ 50, 50 SAY "Are you sure?" OF oModal
@ 150, 150 BUTTON "Yes" OF oModal ACTION oModal:Close()
```

---

### TToast - Toast Notification

**File:** `webx_toast.prg`

**Purpose:** Temporary notification message.

**Usage:**
```harbour
ShowToast("Success!", "Data saved successfully", "success", 3000)
// Types: success, error, warning, info
```

---

### TAlert - Alert Box

**File:** `webx_alert.prg`

**Purpose:** Colored alert/notification box.

**Usage:**
```harbour
@ 50, 50 ALERT oAlert OF oWnd SIZE 400, 100 ;
   TYPE "warning" ;
   MESSAGE "Warning: Please review your input"
```

---

### TNotification - Desktop Notification

**File:** `webx_notification.prg`

**Purpose:** Browser desktop notification API wrapper.

---

### TBreadcrumb - Breadcrumb Navigation

**File:** `webx_breadcrumb.prg`

**Purpose:** Hierarchical navigation breadcrumbs.

**Usage:**
```harbour
@ 20, 50 BREADCRUMB oBread OF oWnd

oBread:AddItem("Home", {|| GoHome() })
oBread:AddItem("Products", {|| ShowProducts() })
oBread:AddItem("Details")
```

---

### TPagination - Pagination Control

**File:** `webx_pagination.prg`

**Purpose:** Page navigation for large datasets.

**Usage:**
```harbour
@ 600, 300 PAGINATION oPage OF oWnd ;
   TOTAL 100 ;
   CURRENT 1 ;
   PAGESIZE 10 ;
   ON CHANGE {|nPage| LoadPage(nPage) }
```

---

### TProgress - Progress Bar

**File:** `webx_progress.prg`

**Purpose:** Progress indicator (horizontal/vertical).

**Usage:**
```harbour
LOCAL nProgress := 0

@ 200, 50 PROGRESS oBar VAR nProgress ;
   TOTAL 100 OF oWnd SIZE 400, 30
```

---

### TSpinner - Loading Spinner

**File:** `webx_spinner.prg`

**Purpose:** Loading spinner/indicator.

**Usage:**
```harbour
@ 300, 400 SPINNER oSpin OF oWnd SIZE "lg" COLOR "blue"
```

---

### TCountdown - Countdown Timer

**File:** `webx_countdown.prg`

**Purpose:** Visual countdown timer.

**Usage:**
```harbour
@ 100, 100 COUNTDOWN oTimer OF oWnd ;
   SECONDS 60 ;
   ON COMPLETE {|| TimeExpired() }
```

---

## Navigation and Menu Components

### TMenu - Menu Bar

**File:** `webx_menu.prg`, `webx_menu_enhanced.prg`

**Purpose:** Application menu bar with dropdown menus.

**Usage:**
```harbour
DEFINE MENU oMenu

MENUITEM "File" OF oMenu SUBMENU {;
   TMenuItem():New("New", {|| NewFile() }),;
   TMenuItem():New("Open", {|| OpenFile() }),;
   TMenuItem():New("Save", {|| SaveFile() }),;
   TMenuItem():New("-"),;
   TMenuItem():New("Exit", {|| Close() });
}

MENUITEM "Edit" OF oMenu SUBMENU {;
   TMenuItem():New("Cut", {|| Cut() }),;
   TMenuItem():New("Copy", {|| Copy() }),;
   TMenuItem():New("Paste", {|| Paste() });
}

DEFINE WINDOW oWnd TITLE "App" MENU oMenu
```

---

### TButtonBar - Toolbar

**File:** `webx_buttonbar.prg`, `webx_buttonbar_enhanced.prg`

**Purpose:** Icon toolbar with buttons.

**Usage:**
```harbour
DEFINE BUTTONBAR oBar OF oWnd SIZE 32, 32

DEFINE BUTTON OF oBar RESOURCE "new.png" ;
   PROMPT "New" ACTION {|| NewDocument() }

DEFINE BUTTON OF oBar RESOURCE "save.png" ;
   PROMPT "Save" ACTION {|| SaveDocument() }
```

---

### TRibbon - Ribbon Bar

**File:** `webx_ribbon.prg`

**Purpose:** Microsoft Office-style ribbon interface.

**Usage:**
```harbour
DEFINE RIBBONBAR oRibbon OF oWnd

ADD TAB "Home" TO oRibbon
ADD GROUP "File" TO oRibbon TAB "Home"
ADD BUTTON "New" TO oRibbon GROUP "File"
```

---

### TNavBar - Navigation Bar

**File:** `webx_navbar.prg`

**Purpose:** Bootstrap-style navigation bar.

**Usage:**
```harbour
@ 0, 0 NAVBAR oNav OF oWnd BRAND "MyApp"

oNav:AddItem("Home", {|| GoHome() })
oNav:AddItem("About", {|| ShowAbout() })
```

---

### TSidebar - Sidebar Navigation

**File:** `webx_sidebar.prg`

**Purpose:** Collapsible side navigation panel.

**Usage:**
```harbour
@ 0, 0 SIDEBAR oSide OF oWnd SIZE 250, 800

oSide:AddItem("Dashboard", "icon-home", {|| ShowDashboard() })
oSide:AddItem("Settings", "icon-gear", {|| ShowSettings() })
```

---

### TTabs - Tab Control

**File:** `webx_tabs.prg`

**Purpose:** Tabbed interface for multiple views.

**Usage:**
```harbour
DEFINE FOLDERTABS oTabs OF oWnd HEIGHT 500

ADD TAB "General" TO oTabs
ADD TAB "Advanced" TO oTabs
```

---

### TFolder - Folder Tabs (FiveWin compatible)

**File:** `webx_folder.prg`

**Purpose:** Folder-style tabs with dialog pages.

---

### TFolderTabs - Standalone Folder Tabs

**File:** `webx_foldertabs.prg`

**Purpose:** Standalone folder tabs (no dialogs).

---

### TTreeView - Tree View

**File:** `webx_treeview.prg`

**Purpose:** Hierarchical tree navigation.

**Usage:**
```harbour
@ 100, 50 TREE oTree OF oWnd SIZE 300, 500

TREEITEM oRoot PROMPT "Root" OF oTree
TREEITEM oChild1 PROMPT "Child 1" OF oTree PARENT oRoot
TREEITEM oChild2 PROMPT "Child 2" OF oTree PARENT oRoot
```

---

### TMacDock - Mac-style Dock

**File:** `webx_macdock.prg`, `macdock.prg`

**Purpose:** Mac OS X-style application dock.

---

## Display and Media Controls

### TImage - Image Display

**File:** `webx_image.prg`

**Purpose:** Display images with optional scaling.

**Usage:**
```harbour
@ 100, 100 IMAGE oImg FILE "logo.png" ;
   OF oWnd SIZE 200, 150 STRETCH
```

---

### TLightbox - Image Lightbox

**File:** `webx_lightbox.prg`

**Purpose:** Image gallery with lightbox viewer.

---

### TVideo - Video Player

**File:** `webx_media.prg`

**Purpose:** HTML5 video player.

**Usage:**
```harbour
@ 100, 100 VIDEO oVid FILE "demo.mp4" ;
   OF oWnd SIZE 640, 480 CONTROLS AUTOPLAY
```

---

### TQRCode - QR Code Generator

**File:** `webx_qrcode.prg`

**Purpose:** Generate QR codes.

**Usage:**
```harbour
@ 100, 100 QRCODE oQR DATA "https://example.com" ;
   OF oWnd SIZE 200, 200
```

---

### TMap - Interactive Map

**File:** `webx_map.prg`

**Purpose:** Google Maps / Leaflet integration.

---

## Status and Information Controls

### TStatusBar - Status Bar

**File:** `webx_statusbar.prg`

**Purpose:** Application status bar (bottom of window).

**Usage:**
```harbour
DEFINE STATUSBAR oBar OF oWnd PROMPT "Ready"

MSGITEM oItem1 OF oBar PROMPT "Status" SIZE 200
MSGITEM oItem2 OF oBar PROMPT Time() SIZE 100
```

---

### TTooltip - Tooltip

**File:** `webx_tooltip.prg`

**Purpose:** Hover tooltip for controls.

---

### TPopover - Popover

**File:** `webx_popover.prg`

**Purpose:** Bootstrap-style popover.

---

### TMyTitle - Custom Titlebar

**File:** `webx_mytitle.prg`

**Purpose:** Custom window titlebar with buttons.

---

### TTitle - Simple Title

**File:** `webx_title.prg`

**Purpose:** Formatted title/heading.

---

## File and Utility Controls

### TUpload - File Upload

**File:** `webx_upload.prg`

**Purpose:** File upload control.

**Usage:**
```harbour
@ 200, 50 UPLOAD oUpload OF oWnd ;
   ACCEPT ".jpg,.png" ;
   MULTIPLE ;
   ON UPLOAD {|aFiles| ProcessFiles(aFiles) }
```

---

### TGroup - Group Box

**File:** `webx_group.prg`

**Purpose:** Group box container with label.

**Usage:**
```harbour
@ 100, 100 GROUP oGrp PROMPT "Settings" ;
   OF oWnd SIZE 400, 300 ROUND
```

---

### TBtnBmp - Bitmap Button

**File:** `webx_btnbmp.prg`

**Purpose:** Button with image/icon.

**Usage:**
```harbour
@ 100, 100 BTNBMP oBtn RESOURCE "icon.png" ;
   PROMPT "Click" OF oWnd SIZE 100, 40
```

---

## Point of Sale (POS) Components

**Directory:** `source/classes/POS/`

### TPOSTitleBar - POS Title Bar

**File:** `POS/webx_pos_titlebar.prg`

**Purpose:** Custom titlebar for POS systems with clock, date, user info.

**Features:**
- Live clock display
- Date display
- User/cashier info
- Store/terminal info
- Customizable colors

**Usage:**
```harbour
oTitle := TPOSTitleBar():New(0, 0, 1920, 80, oWnd)
oTitle:cStoreName := "Maya POS - Terminal 1"
oTitle:cUserName := "Cashier: John Doe"
```

---

### TPOSCategoryGrid - Category Grid

**File:** `POS/webx_pos_categorygrid.prg`

**Purpose:** Grid of product categories with icons.

**Features:**
- Responsive grid layout
- Category icons/images
- Color-coded categories
- Touch-friendly buttons
- Filterable categories

**Usage:**
```harbour
oCat := TPOSCategoryGrid():New(100, 50, 300, 600, oWnd)
oCat:AddCategory("Beverages", "icon-drink", "blue")
oCat:AddCategory("Food", "icon-food", "green")
oCat:OnClick := {|cCategory| FilterProducts(cCategory) }
```

---

### TPOSProductGrid - Product Grid

**File:** `POS/webx_pos_productgrid.prg`

**Purpose:** Grid of products with images and prices.

**Features:**
- Product tiles with images
- Price display
- Stock indicators
- Search/filter
- Touch-optimized
- Scroll/pagination

**Usage:**
```harbour
oProd := TPOSProductGrid():New(100, 400, 800, 600, oWnd)
oProd:AddProduct("Cola", 2.50, "img/cola.jpg", "BEV001")
oProd:AddProduct("Burger", 5.99, "img/burger.jpg", "FOOD001")
oProd:OnSelect := {|cProduct, nPrice| AddToCart(cProduct, nPrice) }
```

---

### TPOSCart - Shopping Cart

**File:** `POS/webx_pos_cart.prg`

**Purpose:** Shopping cart display with line items.

**Features:**
- Line item list
- Quantity adjustment
- Item removal
- Price calculation
- Subtotal/tax/total
- Discounts/promotions

**Usage:**
```harbour
oCart := TPOSCart():New(100, 1300, 600, 700, oWnd)
oCart:AddItem("Cola", 1, 2.50)
oCart:AddItem("Burger", 2, 5.99)
oCart:cTotal := oCart:CalculateTotal()
```

---

### TPOSNumPad - Numeric Keypad

**File:** `POS/webx_pos_numpad.prg`

**Purpose:** Touch-friendly numeric keypad.

**Features:**
- Large touch buttons
- 0-9, decimal, clear, backspace
- Enter/confirm
- Custom actions
- Quantity/price entry

**Usage:**
```harbour
oNumPad := TPOSNumPad():New(500, 1300, 300, 400, oWnd)
oNumPad:OnEnter := {|nValue| ProcessQuantity(nValue) }
```

---

### TPOSActionButtons - Action Buttons

**File:** `POS/webx_pos_actionbuttons.prg`

**Purpose:** Large action buttons for POS operations.

**Features:**
- Payment buttons (Cash, Card, etc.)
- Discount/void buttons
- Hold/retrieve transaction
- Print receipt
- Color-coded by action type

**Usage:**
```harbour
oActions := TPOSActionButtons():New(850, 1300, 600, 200, oWnd)
oActions:AddButton("CASH", "green", {|| ProcessCash() })
oActions:AddButton("CARD", "blue", {|| ProcessCard() })
oActions:AddButton("VOID", "red", {|| VoidTransaction() })
```

---

### TPOSScreen - Receipt Display

**File:** `POS/webx_pos_screen.prg`

**Purpose:** Console-style receipt display (retro green/black screen).

**Features:**
- Monospace font
- Line numbers
- Scrollable list
- Running total
- Retro CRT effect (optional)

**Usage:**
```harbour
oScreen := TPOSScreen():New(100, 50, 400, 600, oWnd, oCart)
oScreen:cBgColor := "black"
oScreen:cTextColor := "green"
oScreen:lRetroStyle := .T.
```

---

### TPOSButtonStyle - Button Styling

**File:** `POS/webx_pos_buttonstyle.prg`

**Purpose:** Standardized button styles for POS.

---

### TPOSAdmin - Admin Panel

**File:** `POS/webx_pos_admin.prg`

**Purpose:** Administrative interface for POS management.

**Features:**
- User management
- Product management
- Sales reports
- Inventory control
- Settings

---

### TPOSDatabase - POS Database Handler

**File:** `POS/webx_pos_database.prg`

**Purpose:** Database operations for POS (DBF or SQL).

---

### TKitchenScreen - Kitchen Display System

**File:** `POS/webx_kitchen_screen.prg`

**Purpose:** Kitchen order display for restaurants.

**Features:**
- Order queue
- Order details
- Status updates (pending/preparing/ready)
- Timer per order
- Color-coded urgency

---

### TTVAdvertisement - TV Advertisement Display

**File:** `POS/webx_tv_advertisement.prg`

**Purpose:** Customer-facing display with ads and promotions.

**Features:**
- Fullscreen mode
- Video/image rotation
- Promotional messages
- Current order summary

---

## System and Integration Classes

### TConsole - Console Emulation

**File:** `webx_console.prg`

**Purpose:** Harbour console emulation for web (? command, @SAY, etc).

---

### TCGI - CGI Interface

**File:** `webx_cgi.prg`

**Purpose:** CGI request/response handling.

---

### TSession - Session Management

**File:** `webx_session.prg`

**Purpose:** Web session management (cookies, session variables).

---

### TAuth - Authentication

**File:** `webx_auth.prg`

**Purpose:** User authentication and authorization.

---

### TWebSocket - WebSocket Communication

**File:** `webx_websocket.prg`

**Purpose:** Real-time bidirectional communication.

---

### TAPI - REST API Handler

**File:** `webx_api.prg`

**Purpose:** RESTful API request/response handling.

---

### TAjax - AJAX Handler

**File:** `webx_ajax.prg`

**Purpose:** AJAX request processing.

---

### TDatabase - Database Interface

**File:** `webx_database.prg`

**Purpose:** Database abstraction layer (DBF, MySQL, PostgreSQL).

---

### THttpClient - HTTP Client

**File:** `webx_httpclient.prg`

**Purpose:** HTTP requests to external APIs.

---

### TEmail - Email Sender

**File:** `webx_email.prg`

**Purpose:** Send emails (SMTP).

---

### TForm - Form Handler

**File:** `webx_form.prg`

**Purpose:** Form validation and processing.

---

### TValidator - Input Validator

**File:** `webx_validator.prg`

**Purpose:** Data validation rules.

---

## Reporting and Export

### TReport - Report Generator

**File:** `webx_report.prg`

**Purpose:** HTML report generation.

---

### TReportJSON - JSON Report

**File:** `webx_report_json.prg`

**Purpose:** JSON-based report definition.

---

### TEasyReport - Easy Report Builder

**File:** `webx_easyreport.prg`

**Purpose:** Simplified report builder.

---

### TFastReport - FastReport Integration

**File:** `webx_fastreport.prg`

**Purpose:** FastReport template engine integration.

---

### TPDF - PDF Generator

**File:** `webx_pdf.prg`

**Purpose:** PDF generation (HPDF library).

---

## Utilities and Helpers

### TFont - Font Definition

**File:** `webx_font.prg`

**Purpose:** Font object for controls.

**Usage:**
```harbour
DEFINE FONT oFont NAME "Arial" SIZE 12 BOLD
```

---

### TTimer - Timer

**File:** `webx_timer.prg`

**Purpose:** Periodic timer events.

**Usage:**
```harbour
DEFINE TIMER oTimer INTERVAL 1000 ;
   ACTION {|| UpdateClock() } OF oWnd

ACTIVATE TIMER oTimer
```

---

### TIni - INI File Handler

**File:** `webx_ini.prg`

**Purpose:** Read/write INI configuration files.

---

### TMru - Most Recently Used

**File:** `webx_mru.prg`

**Purpose:** MRU file list management.

---

### TClipboard - Clipboard Access

**File:** `webx_clipboard.prg`

**Purpose:** Copy/paste to system clipboard.

---

### TLogin - Login Dialog

**File:** `webx_login.prg`

**Purpose:** User login screen.

---

## Compatibility Layers

### FiveWin Stubs

**File:** `fwh_stubs.prg`

**Purpose:** Stub classes for FiveWin compatibility (empty implementations).

---

### FiveWin Extensions

**File:** `fwh_extensions.prg`

**Purpose:** Extended FiveWin compatibility helpers.

---

### Xbase++ Compatibility

**File:** `webxxbase.prg`

**Purpose:** Xbase++ dialect compatibility (WXbp* classes).

---

### xHarbour Compatibility

**File:** `webxxharbour.prg`

**Purpose:** xHarbour-specific features.

---

### Xailer Compatibility

**File:** `webxxailer.prg`

**Purpose:** Xailer dialect compatibility.

---

### mod_harbour Compatibility

**File:** `webxmodharbour.prg`

**Purpose:** mod_harbour specific features.

---

### HIX Compatibility

**File:** `webxhix.prg`

**Purpose:** HIX (Harbour Integrated eXtension) compatibility.

---

## Design Patterns and Best Practices

### Pattern 1: Standard Application Template

```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd, oLayout

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   DEFINE WINDOW oWnd TITLE "My Application" SIZE 1200, 800

   // Create layout
   oLayout := TLayout():New(oWnd, 0, 0, 1200, 800, "ROW")
   oLayout:AddRow("header", 80)
   oLayout:AddRow("content", 0)
   oLayout:AddRow("footer", 60)

   // Add controls
   BuildHeader(oLayout:GetSection("header"))
   BuildContent(oLayout:GetSection("content"))
   BuildFooter(oLayout:GetSection("footer"))

   ACTIVATE WINDOW oWnd CENTERED
RETURN NIL
```

---

### Pattern 2: POS System

```harbour
FUNCTION BuildPOS()
   LOCAL oWnd, oLayout, oLayoutMain, oLayoutRight

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   DEFINE WINDOW oWnd TITLE "Maya POS" SIZE 1920, 1080

   // Main layout: left (products) + right (cart/keypad)
   oLayout := TLayout():New(oWnd, 0, 0, 1920, 1080, "COLUMN")
   oLayout:AddColumn("left", 1200)    // Products area
   oLayout:AddColumn("right", 720)    // Cart/keypad

   // Left: categories + products
   oLayoutLeft := TLayout():New(oLayout:GetSection("left"), 0, 0, 0, 0, "COLUMN")
   oLayoutLeft:AddColumn("categories", 300)
   oLayoutLeft:AddColumn("products", 0)

   oCat := TPOSCategoryGrid():New(0, 0, 300, 1080, oLayoutLeft:GetSection("categories"))
   oProd := TPOSProductGrid():New(0, 0, 900, 1080, oLayoutLeft:GetSection("products"))

   // Right: cart + numpad + actions
   oLayoutRight := TLayout():New(oLayout:GetSection("right"), 0, 0, 0, 0, "ROW")
   oLayoutRight:AddRow("cart", 600)
   oLayoutRight:AddRow("numpad", 300)
   oLayoutRight:AddRow("actions", 180)

   oCart := TPOSCart():New(0, 0, 720, 600, oLayoutRight:GetSection("cart"))
   oNumPad := TPOSNumPad():New(0, 0, 720, 300, oLayoutRight:GetSection("numpad"))
   oActions := TPOSActionButtons():New(0, 0, 720, 180, oLayoutRight:GetSection("actions"))

   ACTIVATE WINDOW oWnd
RETURN NIL
```

---

## Common Gotchas

### Always Set Designed_Resolution

```harbour
// WRONG - No resolution set
FUNCTION Main()
   LOCAL oWnd := TWindow():New(0, 0, 800, 600, "App")
   // ERROR!

// CORRECT
FUNCTION Main()
   PUBLIC Designed_Resolution := {1920, 1080, .T.}
   LOCAL oWnd := TWindow():New(0, 0, 800, 600, "App")
```

---

### Always Use Pixel Mode

```harbour
// WRONG
oWnd:lPixel := .F.  // Dialog units don't work in web!

// CORRECT
oWnd:lPixel := .T.  // Always pixels
```

---

### Use TO/OF for Parent Window

```harbour
// WRONG - No parent specified
@ 100, 50 SAY "Text"  // Where does this go?

// CORRECT
@ 100, 50 SAY "Text" TO oWnd
// OR
@ 100, 50 SAY "Text" OF oWnd
```

---

## Quick Reference

### Window Creation
```harbour
DEFINE WINDOW oWnd TITLE "App" SIZE 1200, 800
ACTIVATE WINDOW oWnd CENTERED
```

### Layout Creation
```harbour
oLayout := TLayout():New(oWnd, 0, 0, nWidth, nHeight, "ROW"|"COLUMN")
oLayout:AddRow(cName, nHeight)
oLayout:AddColumn(cName, nWidth)
oSection := oLayout:GetSection(cName)
```

### Basic Controls
```harbour
@ nRow, nCol SAY cText TO oWnd SIZE nWidth
@ nRow, nCol GET varname TO oWnd SIZE nWidth
@ nRow, nCol BUTTON "Text" TO oWnd SIZE nWidth ACTION {|| code }
```

### Advanced Controls
```harbour
@ nRow, nCol CHECKBOX oCheck VAR lVar OF oWnd
@ nRow, nCol COMBOBOX oCombo VAR nVar ITEMS aItems OF oWnd
@ nRow, nCol BROWSE oBrw HEADERS aHeaders DATASOURCE aData TO oWnd
```

---

## See Also

- [webx_xcommands.md](webx_xcommands.md) - Complete xcommand reference
- [webx_language_rules.md](webx_language_rules.md) - Harbour syntax guide
- [SPEC_webx_functions.md](SPEC_webx_functions.md) - Function reference

---

**© 2025 WebX Framework - AI Training Reference**
Last Updated: 2026-01-21
