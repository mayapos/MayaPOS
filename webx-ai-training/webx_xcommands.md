# WebX xCommands Reference - AI Training Guide

**Last Updated:** 2026-01-21
**WebX Version:** 1.0.0
**Total Commands:** 220+ preprocessor commands

## Introduction

WebX provides comprehensive xBase/Harbour command preprocessor (#xcommand) directives that enable FiveWin-compatible syntax while generating modern web applications. These commands are **WebX's own implementations** - they provide compatibility but are NOT copied from FiveWin.

**Important:** All commands are defined in `source/include/WebX.ch` and are automatically included when you use `#include "WebX.ch"`.

---

## Window Management Commands

### DEFINE WINDOW - Create Main Window

**Syntax:**
```harbour
DEFINE WINDOW <oWnd> ;
   [TITLE <cTitle>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [MENU <oMenu>] ;
   [PIXEL] ;
   [COLOR <nClrText>, <nClrBack>]
```

**Purpose:** Create the main application window.

**Parameters:**
- `oWnd` - Window object variable
- `cTitle` - Window title (optional)
- `nWidth, nHeight` - Window size in pixels
- `oMenu` - Menu object (optional)
- `PIXEL` - Use pixel coordinates (always recommended)
- `nClrText, nClrBack` - Foreground and background colors

**Examples:**
```harbour
// Simple window
DEFINE WINDOW oWnd TITLE "My Application" SIZE 1200, 800

// With menu
DEFINE MENU oMenu
DEFINE WINDOW oWnd TITLE "My App" SIZE 1200, 800 MENU oMenu

// With colors
DEFINE WINDOW oWnd TITLE "App" SIZE 1200, 800 ;
   COLOR CLR_BLACK, CLR_WHITE
```

**Generated Code:**
```harbour
oWnd := TWindow():New(NIL, NIL, nHeight, nWidth, cTitle, ;
   NIL, oMenu, NIL, NIL, NIL, NIL, NIL, nClrText, nClrBack, ;
   NIL, NIL, NIL, NIL, NIL, NIL, .T.)
WebX_SetActiveWindow(oWnd)
```

---

### DEFINE MDI WINDOW - Create MDI Parent Window

**Syntax:**
```harbour
DEFINE MDI WINDOW <oWnd> ;
   [TITLE <cTitle>] ;
   [MENU <oMenu>] ;
   [ICON <oIcon>] ;
   [COLOR <nClrFore>, <nClrBack>]
```

**Purpose:** Create Multiple Document Interface (MDI) parent window.

**Example:**
```harbour
DEFINE MDI WINDOW oMain TITLE "MDI Application" MENU oMenu
```

---

### DEFINE MDICHILD WINDOW - Create MDI Child Window

**Syntax:**
```harbour
DEFINE MDICHILD WINDOW <oWnd> ;
   [OF <oParent>] ;
   [TITLE <cTitle>] ;
   [MENU <oMenu>]
```

**Example:**
```harbour
DEFINE MDICHILD WINDOW oChild OF oMain TITLE "Document 1"
```

---

### ACTIVATE WINDOW - Show Window

**Syntax:**
```harbour
ACTIVATE WINDOW <oWnd> ;
   [MAXIMIZED | MAX] ;
   [MINIMIZED | MIN] ;
   [CENTERED | CENTER] ;
   [ICONIZED] ;
   [VALID <bValid>] ;
   [ON INIT <bInit>] ;
   [ON LEFT CLICK <bLClicked>] ;
   [ON RIGHT CLICK <bRClicked>] ;
   [ON MOVE <bMoved>] ;
   [ON RESIZE <bResized>] ;
   [ON PAINT <bPaint>] ;
   [ON UP <bUp>] ;
   [ON DOWN <bDown>]
```

**Purpose:** Activate and display the window.

**Parameters:**
- `MAXIMIZED` - Maximize window
- `MINIMIZED` - Minimize window
- `CENTERED` - Center window in viewport
- `VALID` - Validation codeblock before closing
- `ON INIT` - Execute on window initialization
- `ON LEFT CLICK` - Left mouse button handler
- `ON RIGHT CLICK` - Right mouse button handler
- `ON MOVE` - Window move handler
- `ON RESIZE` - Window resize handler
- `ON PAINT` - Window paint handler
- `ON UP/ON DOWN` - Scroll handlers

**Examples:**
```harbour
// Simple activation
ACTIVATE WINDOW oWnd

// Centered
ACTIVATE WINDOW oWnd CENTERED

// With initialization
ACTIVATE WINDOW oWnd ON INIT {|| LoadData() }

// With validation
ACTIVATE WINDOW oWnd VALID {|| SaveChanges() }

// Multiple event handlers
ACTIVATE WINDOW oWnd CENTERED ;
   ON INIT {|| InitApp() } ;
   ON RESIZE {|| AdjustLayout() }
```

---

## Dialog Commands

### DEFINE DIALOG - Create Dialog

**Syntax:**
```harbour
DEFINE DIALOG <oDlg> ;
   [TITLE <cTitle>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [FROM <nTop>, <nLeft>]
```

**Purpose:** Create modal dialog window.

**Example:**
```harbour
DEFINE DIALOG oDlg TITLE "Settings" SIZE 400, 300

@ 50, 50 SAY "Name:" OF oDlg
@ 50, 150 GET cName OF oDlg SIZE 200, 30

ACTIVATE DIALOG oDlg CENTERED
```

---

### ACTIVATE DIALOG - Show Dialog

**Syntax:**
```harbour
ACTIVATE DIALOG <oDlg> ;
   [CENTERED | CENTER] ;
   [VALID <bValid>] ;
   [ON INIT <bInit>] ;
   [ON PAINT <bPaint>] ;
   [NOWAIT]
```

**Purpose:** Display modal dialog.

**Examples:**
```harbour
// Simple
ACTIVATE DIALOG oDlg

// Centered with initialization
ACTIVATE DIALOG oDlg CENTERED ON INIT {|| LoadDefaults() }

// Non-blocking (modeless)
ACTIVATE DIALOG oDlg NOWAIT
```

---

## Menu Commands

### DEFINE MENU - Create Menu Bar

**Syntax:**
```harbour
DEFINE MENU <oMenu>
```

**Purpose:** Create menu bar for window.

**Example:**
```harbour
DEFINE MENU oMenu

MENUITEM "File" OF oMenu SUBMENU {;
   TMenuItem():New("New", {|| NewFile() }),;
   TMenuItem():New("Open", {|| OpenFile() }),;
   TMenuItem():New("-"),;  // Separator
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

### MENUITEM - Add Menu Item

**Syntax:**
```harbour
MENUITEM <cPrompt> ;
   [ACTION <uAction>] ;
   [RESOURCE <cRes>] ;
   [FILE <cFile>] ;
   [MESSAGE <cMsg>] ;
   [ACCELERATOR <nAccel>] ;
   [CHECK | CHECKED] ;
   [DISABLED] ;
   [WHEN <bWhen>]
```

**Examples:**
```harbour
// Simple menu item
MENUITEM "Exit" ACTION {|| Close() }

// With accelerator
MENUITEM "Save" ACTION {|| SaveFile() } ACCELERATOR VK_F2

// Checked menu item
MENUITEM "Show Toolbar" ACTION {|| ToggleToolbar() } CHECK

// Disabled
MENUITEM "Not Available" DISABLED

// With icon
MENUITEM "New" RESOURCE "new.png" ACTION {|| NewFile() }
```

---

### MENU POPUP - Create Popup Menu

**Syntax:**
```harbour
MENU [<oMenu>] POPUP

MENUITEM <cPrompt> ACTION <uAction>
...
SEPARATOR
...
ENDMENU

ACTIVATE POPUP <oMenu> [OF <oWnd>] [AT <nRow>, <nCol>]
```

**Example:**
```harbour
MENU oPopup POPUP

MENUITEM "Cut" ACTION {|| Cut() }
MENUITEM "Copy" ACTION {|| Copy() }
MENUITEM "Paste" ACTION {|| Paste() }
SEPARATOR
MENUITEM "Delete" ACTION {|| Delete() }

ENDMENU

// Show popup at mouse position
ACTIVATE POPUP oPopup AT nRow, nCol
```

---

## Control Commands - @ Commands

### @ SAY - Static Label

**Syntax:**
```harbour
@ <nRow>, <nCol> SAY <value> ;
   [TO <oWnd>] [OF <oWnd>] [WINDOW <oWnd>] [DIALOG <oDlg>] ;
   [SIZE <nWidth> [, <nHeight>]] ;
   [PROMPT <cText>] ;
   [VAR <uValue>] ;
   [COLOR <nClrFore> [, <nClrBack>]] ;
   [FONT <oFont>] ;
   [CENTERED | CENTER] ;
   [RIGHT] ;
   [PIXEL] ;
   [PICTURE <cPict>] ;
   [UPDATE] ;
   [BORDER] ;
   [RAISED] ;
   [TRANSPARENT]
```

**Examples:**
```harbour
// Simple text
@ 100, 50 SAY "Welcome!" TO oWnd SIZE 200, 30

// With PROMPT keyword
@ 100, 50 SAY PROMPT "Label:" TO oWnd

// Dynamic text with variable
LOCAL cName := "User"
@ 100, 50 SAY {|| "Hello, " + cName } TO oWnd SIZE 300, 30

// Centered
@ 100, 50 SAY "Centered Text" TO oWnd SIZE 300, 30 CENTERED

// With font and color
DEFINE FONT oFont NAME "Arial" SIZE 12 BOLD
@ 100, 50 SAY "Custom Font" TO oWnd SIZE 200, 30 ;
   FONT oFont COLOR CLR_BLUE
```

---

### @ GET - Input Field

**Syntax:**
```harbour
@ <nRow>, <nCol> GET <var> ;
   [TO <oWnd>] [OF <oWnd>] ;
   [SIZE <nWidth> [, <nHeight>]] ;
   [VAR <uVar>] ;
   [PICTURE <cPict>] ;
   [VALID <bValid>] ;
   [WHEN <bWhen>] ;
   [FONT <oFont>] ;
   [PIXEL] ;
   [COLOR <nClrFore> [, <nClrBack>]] ;
   [MESSAGE <cMsg>] ;
   [READONLY] ;
   [PASSWORD | SECRET] ;
   [ON CHANGE <bChange>] ;
   [HELPID <nHelpId>]
```

**Examples:**
```harbour
// Simple text input
LOCAL cName := Space(50)
@ 150, 50 GET cName TO oWnd SIZE 300, 30

// Numeric with picture
LOCAL nPrice := 0
@ 150, 50 GET nPrice PICTURE "@E 999,999.99" TO oWnd SIZE 120, 30

// Password field
LOCAL cPassword := Space(20)
@ 150, 50 GET cPassword TO oWnd SIZE 200, 30 PASSWORD

// With validation
LOCAL cEmail := Space(100)
@ 150, 50 GET cEmail TO oWnd SIZE 300, 30 ;
   VALID {|| "@" $ cEmail .AND. "." $ cEmail }

// Read-only
@ 150, 50 GET cTotal TO oWnd SIZE 120, 30 READONLY

// With change handler
@ 150, 50 GET nQuantity TO oWnd SIZE 100, 30 ;
   ON CHANGE {|| UpdateTotal() }
```

---

### @ BUTTON - Button Control

**Syntax:**
```harbour
@ <nRow>, <nCol> BUTTON <cCaption> ;
   [TO <oWnd>] [OF <oWnd>] ;
   [SIZE <nWidth> [, <nHeight>]] ;
   [ACTION <uAction>] ;
   [MESSAGE <cMsg>] ;
   [WHEN <bWhen>] ;
   [PIXEL] ;
   [DEFAULT] ;
   [CANCEL] ;
   [FONT <oFont>] ;
   [COLOR <nClrFore> [, <nClrBack>]] ;
   [FLAT] ;
   [NOBORDER]
```

**Examples:**
```harbour
// Simple button
@ 200, 50 BUTTON "Save" TO oWnd SIZE 100, 40 ACTION SaveData()

// Inline codeblock
@ 200, 50 BUTTON "Click Me" TO oWnd SIZE 100, 40 ;
   ACTION {|| MsgInfo("Clicked!") }

// Default button (Enter key)
@ 200, 50 BUTTON "OK" TO oWnd SIZE 100, 40 DEFAULT ;
   ACTION {|| oDlg:End() }

// Cancel button (Escape key)
@ 200, 160 BUTTON "Cancel" TO oWnd SIZE 100, 40 CANCEL ;
   ACTION {|| oDlg:End() }

// Flat style
@ 200, 50 BUTTON "Flat" TO oWnd SIZE 100, 40 FLAT

// Conditional enabling
@ 200, 50 BUTTON "Process" TO oWnd SIZE 100, 40 ;
   ACTION {|| Process() } ;
   WHEN {|| !Empty(cName) .AND. nAmount > 0 }
```

---

### @ CHECKBOX - Checkbox Control

**Syntax:**
```harbour
@ <nRow>, <nCol> CHECKBOX <oCheck> VAR <lVar> ;
   [PROMPT <cPrompt>] ;
   [OF <oWnd>] [TO <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [WHEN <bWhen>] ;
   [VALID <bValid>] ;
   [MESSAGE <cMsg>] ;
   [ON CHANGE <bChange>]
```

**Example:**
```harbour
LOCAL lAccept := .F.
LOCAL lSubscribe := .T.

@ 200, 50 CHECKBOX oCheck1 VAR lAccept ;
   PROMPT "I accept the terms and conditions" OF oWnd ;
   ON CHANGE {|| ValidateForm() }

@ 230, 50 CHECKBOX oCheck2 VAR lSubscribe ;
   PROMPT "Subscribe to newsletter" OF oWnd
```

---

### @ RADIO - Radio Button Group

**Syntax:**
```harbour
@ <nRow>, <nCol> RADIO <oRadio> VAR <nVar> ;
   ITEMS <item1> [, <item2>] [, ...] ;
   [OF <oWnd>] [TO <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [VERTICAL | HORIZONTAL] ;
   [ON CHANGE <bChange>]
```

**Example:**
```harbour
LOCAL nPayment := 1

@ 200, 50 RADIO oRadio VAR nPayment ;
   ITEMS "Cash", "Credit Card", "Debit Card", "Mobile Payment" ;
   OF oWnd SIZE 200, 120 VERTICAL ;
   ON CHANGE {|| UpdatePaymentMethod(nPayment) }
```

---

### @ COMBOBOX - Dropdown List

**Syntax:**
```harbour
@ <nRow>, <nCol> COMBOBOX <oCombo> VAR <nVar> ;
   [ITEMS <aItems>] ;
   [OF <oWnd>] [TO <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [ON CHANGE <bChange>] ;
   [SORT]
```

**Example:**
```harbour
LOCAL nCountry := 1
LOCAL aCountries := {"USA", "Canada", "Mexico", "UK", "France"}

@ 200, 50 COMBOBOX oCombo VAR nCountry ;
   ITEMS aCountries OF oWnd SIZE 200, 30 ;
   ON CHANGE {|| UpdateShipping(nCountry) }

// Sorted
@ 230, 50 COMBOBOX oCombo2 VAR nCity ;
   ITEMS aCities OF oWnd SIZE 200, 30 SORT
```

---

### @ LISTBOX - List Box Control

**Syntax:**
```harbour
@ <nRow>, <nCol> LISTBOX <oList> VAR <nVar> ;
   [ITEMS <aItems>] ;
   [OF <oWnd>] [TO <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [ON CHANGE <bChange>] ;
   [MULTIPLE | MULTI] ;
   [SORT]
```

**Example:**
```harbour
LOCAL nSelected := 1
LOCAL aProducts := {"Product A", "Product B", "Product C"}

// Single selection
@ 200, 50 LISTBOX oList VAR nSelected ;
   ITEMS aProducts OF oWnd SIZE 200, 150

// Multiple selection
LOCAL aMultiSel := {}
@ 200, 50 LISTBOX oList VAR aMultiSel ;
   ITEMS aProducts OF oWnd SIZE 200, 150 MULTIPLE
```

---

### @ DATEPICKER - Date Picker

**Syntax:**
```harbour
@ <nRow>, <nCol> DATEPICKER <oDate> VAR <dVar> ;
   [TO <oWnd>] [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [ON CHANGE <bChange>]
```

**Example:**
```harbour
LOCAL dBirth := Date()
LOCAL dStartDate := Date()

@ 200, 50 DATEPICKER oDate VAR dBirth OF oWnd SIZE 200, 30 ;
   ON CHANGE {|| CalculateAge(dBirth) }
```

---

### @ BROWSE - Data Grid

**Syntax:**
```harbour
@ <nRow>, <nCol> BROWSE <oBrw> ;
   [TO <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [FIELDS <aFields>]
```

**Example:**
```harbour
LOCAL oBrw
LOCAL aHeaders := {"ID", "Name", "Email", "Phone"}
LOCAL aData := {;
   {"001", "John Doe", "john@email.com", "555-1234"},;
   {"002", "Jane Smith", "jane@email.com", "555-5678"};
}

@ 100, 50 BROWSE oBrw HEADERS aHeaders ;
   DATASOURCE aData TO oWnd SIZE 800, 400
```

---

### @ XBROWSE - Enhanced Browse

**Syntax:**
```harbour
@ <nRow>, <nCol> XBROWSE <oXBrw> ;
   [TO <oWnd>] [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [EDITABLE] ;
   [MULTISELECT]

ADD COLUMN [<oCol>] [DATA <uData>] [HEADER <cHeader>] ;
   [TO <oXBrw>] ;
   [SIZE <nWidth>] ;
   [PICTURE <cPict>] ;
   [EDITABLE]
```

**Example:**
```harbour
@ 100, 50 XBROWSE oXBrw OF oWnd SIZE 800, 500 ;
   EDITABLE MULTISELECT

ADD COLUMN DATA CUSTOMERS->NAME HEADER "Name" TO oXBrw SIZE 200
ADD COLUMN DATA CUSTOMERS->EMAIL HEADER "Email" TO oXBrw SIZE 250
ADD COLUMN DATA CUSTOMERS->PHONE HEADER "Phone" TO oXBrw SIZE 150
ADD COLUMN DATA CUSTOMERS->BALANCE HEADER "Balance" TO oXBrw ;
   SIZE 120 PICTURE "@E 999,999.99"
```

---

### @ IMAGE - Image Display

**Syntax:**
```harbour
@ <nRow>, <nCol> IMAGE <oImg> ;
   [FILE <cFile>] ;
   [FILENAME <cFile>] ;
   [RESOURCE <cFile>] ;
   [OF <oWnd>] [TO <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [STRETCH] ;
   [CENTER] ;
   [BORDER <nBorder>]
```

**Example:**
```harbour
// Simple image
@ 100, 100 IMAGE oImg FILE "logo.png" OF oWnd SIZE 200, 150

// Stretched to fit
@ 100, 100 IMAGE oImg FILE "banner.jpg" OF oWnd ;
   SIZE 800, 200 STRETCH

// Centered with border
@ 100, 100 IMAGE oImg FILE "photo.jpg" OF oWnd ;
   SIZE 300, 300 CENTER BORDER 2
```

---

### @ GROUP - Group Box

**Syntax:**
```harbour
@ <nRow>, <nCol> GROUP <oGrp> ;
   [PROMPT <cPrompt>] ;
   [TO <oWnd>] [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [ROUND]
```

**Example:**
```harbour
@ 100, 100 GROUP oGrp PROMPT "Personal Information" ;
   OF oWnd SIZE 400, 200 ROUND

// Add controls inside group
@ 140, 120 SAY "Name:" OF oWnd
@ 140, 200 GET cName OF oWnd SIZE 250, 30
```

---

### @ PANEL - Panel Container

**Syntax:**
```harbour
@ <nRow>, <nCol> PANEL <oPanel> ;
   [TO <oWnd>] [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [BORDER] ;
   [RAISED]
```

**Example:**
```harbour
@ 100, 100 PANEL oPanel OF oWnd SIZE 400, 300 BORDER RAISED

// Add controls to panel
@ 20, 20 SAY "Panel Content" OF oPanel
```

---

### @ PROGRESS / @ METER - Progress Bar

**Syntax:**
```harbour
@ <nRow>, <nCol> PROGRESS <oMeter> VAR <nVar> ;
   [TOTAL <nTotal>] ;
   [TO <oWnd>] [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>]

@ <nRow>, <nCol> METER <oMeter> VAR <nVar> ;
   [TOTAL <nTotal>] ;
   [TO <oWnd>] [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [VERTICAL] ;
   [SHOWPCT]
```

**Example:**
```harbour
LOCAL nProgress := 0

@ 200, 50 PROGRESS oBar VAR nProgress ;
   TOTAL 100 OF oWnd SIZE 400, 30

// Vertical with percentage
@ 200, 50 METER oMeter VAR nProgress ;
   TOTAL 100 OF oWnd SIZE 40, 300 VERTICAL SHOWPCT
```

---

### @ TREE - Tree View

**Syntax:**
```harbour
@ <nRow>, <nCol> TREE [<oTree>] ;
   [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [PIXEL] ;
   [ON CHANGE <bChange>]

TREEITEM [<oItem>] [PROMPT <cPrompt>] ;
   [RESOURCE <cRes>] ;
   [OF <oTree>] ;
   [PARENT <oParent>]
```

**Example:**
```harbour
@ 100, 50 TREE oTree OF oWnd SIZE 300, 500

TREEITEM oRoot PROMPT "Root Folder" OF oTree
TREEITEM oFolder1 PROMPT "Subfolder 1" OF oTree PARENT oRoot
TREEITEM oFolder2 PROMPT "Subfolder 2" OF oTree PARENT oRoot
TREEITEM oFile1 PROMPT "File 1.txt" OF oTree PARENT oFolder1
TREEITEM oFile2 PROMPT "File 2.txt" OF oTree PARENT oFolder1
```

---

## Toolbar Commands

### DEFINE BUTTONBAR - Create Toolbar

**Syntax:**
```harbour
DEFINE BUTTONBAR <oBar> ;
   [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [VERTICAL] ;
   [TOP | BOTTOM | LEFT | RIGHT] ;
   [FLOAT] ;
   [NOBORDER] ;
   [STYLEBAR]
```

**Example:**
```harbour
DEFINE BUTTONBAR oBar OF oWnd SIZE 32, 32 TOP

DEFINE BUTTON OF oBar RESOURCE "new.png" ;
   PROMPT "New" ACTION {|| NewDocument() } TOOLTIP "New Document"

DEFINE BUTTON OF oBar RESOURCE "open.png" ;
   PROMPT "Open" ACTION {|| OpenDocument() } TOOLTIP "Open File"

DEFINE BUTTON OF oBar RESOURCE "save.png" ;
   PROMPT "Save" ACTION {|| SaveDocument() } TOOLTIP "Save File"
```

---

### DEFINE BUTTON OF - Add Toolbar Button

**Syntax:**
```harbour
DEFINE BUTTON [<oBtn>] OF <oBar> ;
   [PROMPT <cPrompt>] ;
   [RESOURCE <cBmp>] ;
   [FILE <cFile>] ;
   [FILENAME <cFile>] ;
   [ACTION <uAction>] ;
   [MESSAGE <cMsg>] ;
   [MENU <bMenu>] ;
   [TOOLTIP <cTip>] ;
   [WHEN <bWhen>] ;
   [GROUP] ;
   [ADJUST] ;
   [DISABLED]
```

---

## Status Bar Commands

### DEFINE STATUSBAR / DEFINE MSGBAR - Create Status Bar

**Syntax:**
```harbour
DEFINE STATUSBAR <oBar> ;
   [OF <oWnd>] ;
   [PROMPT <cPrompt>] ;
   [CLOCK | TIME] ;
   [DATE] ;
   [KEYBOARD | KBD] ;
   [CENTERED | CENTER] ;
   [INSET | NOINSET] ;
   [FONT <oFont>] ;
   [COLOR <nClrFore> [, <nClrBack>]]
```

**Example:**
```harbour
DEFINE STATUSBAR oBar OF oWnd PROMPT "Ready" CLOCK DATE

MSGITEM oItem1 OF oBar PROMPT "Status" SIZE 200
MSGITEM oItem2 OF oBar PROMPT "User: Admin" SIZE 150
```

---

### MSGITEM - Add Status Bar Item

**Syntax:**
```harbour
MSGITEM [<oItem>] OF <oMsgBar> ;
   [PROMPT <cPrompt>] ;
   [SIZE <nSize>] ;
   [FONT <oFont>] ;
   [ACTION <uAction>]
```

---

## Font Commands

### DEFINE FONT - Create Font Object

**Syntax:**
```harbour
DEFINE FONT <oFont> ;
   [NAME <cFaceName>] ;
   [SIZE <nWidth> [, <nHeight>]] ;
   [BOLD] ;
   [ITALIC] ;
   [UNDERLINE] ;
   [STRIKEOUT] ;
   [WEIGHT <nWeight>] ;
   [ESCAPEMENT <nEscapement>] ;
   [OF <oDevice>] ;
   [FROM USER] ;
   [NCHARSET <nCharSet>]
```

**Examples:**
```harbour
// Simple font
DEFINE FONT oFont NAME "Arial" SIZE 12

// Bold font
DEFINE FONT oFontBold NAME "Verdana" SIZE 14 BOLD

// Italic and underline
DEFINE FONT oFontTitle NAME "Times New Roman" SIZE 18 ;
   BOLD ITALIC UNDERLINE

// Custom weight
DEFINE FONT oFontLight NAME "Arial" SIZE 12 WEIGHT 300
```

---

### SET FONT OF - Assign Font to Control

**Syntax:**
```harbour
SET FONT OF <oControl> TO <oFont>
```

**Example:**
```harbour
DEFINE FONT oFont NAME "Arial" SIZE 14 BOLD
SET FONT OF oSay TO oFont
```

---

## Timer Commands

### DEFINE TIMER - Create Timer

**Syntax:**
```harbour
DEFINE TIMER <oTimer> ;
   [INTERVAL <nMs>] ;
   [ACTION <uAction>] ;
   [OF <oWnd>]
```

**Examples:**
```harbour
// Clock update every second
DEFINE TIMER oTimer INTERVAL 1000 ;
   ACTION {|| UpdateClock() } OF oWnd

ACTIVATE TIMER oTimer

// Auto-save every 5 minutes
DEFINE TIMER oAutoSave INTERVAL 300000 ;
   ACTION {|| AutoSave() } OF oWnd
```

---

### ACTIVATE/DEACTIVATE TIMER

**Syntax:**
```harbour
ACTIVATE TIMER <oTimer>
DEACTIVATE TIMER <oTimer>
RELEASE TIMER <oTimer>
```

---

## INI File Commands

### DEFINE INI - Open INI File

**Syntax:**
```harbour
DEFINE INI <oIni> [FILE <cFile>] [FILENAME <cFile>]

SET SECTION <oIni> [TO] <cSection>

GET <uVar> [SECTION <cSection>] ENTRY <cEntry> ;
   [DEFAULT <uDefault>] OF <oIni>

SET [SECTION <cSection>] ENTRY <cEntry> ;
   [TO] <uValue> OF <oIni>

RELEASE INI <oIni>
```

**Example:**
```harbour
DEFINE INI oIni FILE "config.ini"

SET SECTION oIni TO "Database"
GET cServer SECTION "Database" ENTRY "Server" ;
   DEFAULT "localhost" OF oIni
GET nPort SECTION "Database" ENTRY "Port" ;
   DEFAULT 3306 OF oIni

SET SECTION "User" ENTRY "LastLogin" TO Date() OF oIni

RELEASE INI oIni
```

---

## Folder/Tab Commands

### DEFINE FOLDER - Create Tab Control

**Syntax:**
```harbour
DEFINE FOLDER <oFolder> ;
   [PROMPT <aPrompts>...] ;
   [PROMPTS <aPrompts>...] ;
   [DIALOGS <aDlgs>...] ;
   [OF <oWnd>] ;
   [SIZE <nWidth>, <nHeight>] ;
   [AT <nRow>, <nCol>]
```

**Example:**
```harbour
DEFINE FOLDER oFolder ;
   PROMPTS "General", "Advanced", "Security" ;
   OF oWnd SIZE 600, 400 AT 100, 100
```

---

### DEFINE FOLDERTABS - Create Standalone Tabs

**Syntax:**
```harbour
DEFINE FOLDERTABS <oTabs> ;
   [WINDOW <oWnd>] [OF <oWnd>] ;
   [HEIGHT <nHeight>]

ADD TAB <cPrompt> ;
   [COLOR <cColor>] ;
   [CONTENT <oContent>] ;
   TO <oTabs>
```

**Example:**
```harbour
DEFINE FOLDERTABS oTabs OF oWnd HEIGHT 500

ADD TAB "Home" COLOR "blue" TO oTabs
ADD TAB "Products" COLOR "green" TO oTabs
ADD TAB "Settings" COLOR "gray" TO oTabs
```

---

## Console Commands

### ? and ?? - Console Output

**Syntax:**
```harbour
? [<explist,...>]
?? [<explist,...>]
```

**Example:**
```harbour
? "Hello World"
? "Name:", cName, "Age:", nAge

?? "Append text "
?? "on same line"
```

---

### CLS / CLEAR SCREEN - Clear Console

**Syntax:**
```harbour
CLS
CLEAR SCREEN
```

---

### @ row, col - Position Cursor

**Syntax:**
```harbour
@ <row>, <col>
@ <row>, <col> SAY <exp> [PICTURE <pic>] [COLOR <clr>]
@ <row>, <col> GET <var> [PICTURE <pict>] [WHEN <bWhen>] [VALID <bValid>]
```

**Example:**
```harbour
CLS
@ 5, 10 SAY "Enter name:"
@ 5, 25 GET cName
@ 7, 10 SAY "Enter age:"
@ 7, 25 GET nAge PICTURE "999"
READ
```

---

### @ TO - Draw Box

**Syntax:**
```harbour
@ <top>, <left> TO <bottom>, <right> [DOUBLE] [COLOR <color>]
@ <top>, <left>, <bottom>, <right> BOX <string> [COLOR <clr>]
```

**Example:**
```harbour
// Single-line box
@ 5, 10 TO 15, 60

// Double-line box
@ 5, 10 TO 15, 60 DOUBLE

// Custom box characters
@ 5, 10, 15, 60 BOX "┌─┐│┘─└│"
```

---

### READ - Process GET Fields

**Syntax:**
```harbour
READ
```

**Example:**
```harbour
LOCAL cName := Space(50)
LOCAL nAge := 0

CLS
@ 5, 10 SAY "Name:" GET cName
@ 7, 10 SAY "Age:" GET nAge PICTURE "999"
READ  // Wait for user input

? "You entered:", cName, nAge
```

---

### WAIT / ACCEPT / INPUT

**Syntax:**
```harbour
WAIT [<msg>]
WAIT [<msg>] TO <v>
ACCEPT [<msg>] TO <v>
INPUT [<msg>] TO <v>
```

**Example:**
```harbour
WAIT "Press any key..."

LOCAL cKey
WAIT "Press a key: " TO cKey

LOCAL cName
ACCEPT "Enter your name: " TO cName

LOCAL nValue
INPUT "Enter a number: " TO nValue
```

---

## Printer Commands

### PRINT - Start Print Job

**Syntax:**
```harbour
PRINT [<oPrint>] ;
   [NAME <cName>] ;
   [PREVIEW] ;
   [TO <cPort>] ;
   [FILE <cFile>]

PAGE
ENDPAGE
ENDPRINT
```

**Example:**
```harbour
PRINT oPrint NAME "Report" PREVIEW

PAGE
   @ 2, 10 SAY "Company Report"
   @ 4, 10 SAY "Date: " + DToC(Date())

   // Print data...
ENDPAGE

ENDPRINT
```

---

### SET PRINTER - Printer Output

**Syntax:**
```harbour
SET PRINTER TO <file>
SET PRINTER TO
SET PRINTER OFF
CLOSE PRINTER
```

---

## Database/Browse Commands

### XBROWSER - Quick Browse

**Syntax:**
```harbour
XBROWSER <aData> ;
   [TITLE <cTitle>] ;
   [SETUP <uSetup>] ;
   [FASTEDIT] ;
   [SELECT <uSelect>] ;
   [COLUMNS <aCols,...>]
```

**Example:**
```harbour
// Browse array
LOCAL aData := {{"John", 30}, {"Jane", 25}}
XBROWSER aData TITLE "Customers"

// Browse with setup
XBROWSER aCustomers TITLE "Customer List" ;
   SETUP {|oBrw| oBrw:nRowHeight := 25 }
```

---

## Miscellaneous Commands

### DEFAULT - Set Default Values

**Syntax:**
```harbour
DEFAULT <v1> TO <x1> [, <vn> TO <xn>]
DEFAULT <v1> := <x1> [, <vn> := <xn>]
```

**Example:**
```harbour
FUNCTION MyFunc(cName, nAge, cCity)
   DEFAULT cName TO "Unknown", nAge TO 0, cCity TO "N/A"

   ? "Name:", cName
   ? "Age:", nAge
   ? "City:", cCity
RETURN NIL
```

---

### TRY / CATCH / FINALLY - Exception Handling

**Syntax:**
```harbour
TRY
   // Code that might fail
CATCH oErr
   // Error handling
FINALLY
   // Always executed
END
```

**Example:**
```harbour
TRY
   USE CUSTOMERS
   // Process data
CATCH oErr
   ? "Error:", oErr:Description
FINALLY
   IF Used()
      CLOSE CUSTOMERS
   ENDIF
END
```

---

### SET COLOR - Set Console Colors

**Syntax:**
```harbour
SET COLOR TO <spec>
```

**Example:**
```harbour
SET COLOR TO "W+/B,N/W"  // White on blue, black on white
```

---

### SET CENTURY - Date Format

**Syntax:**
```harbour
SET CENTURY ON
SET CENTURY OFF
```

---

### SET CONSOLE - Console Output

**Syntax:**
```harbour
SET CONSOLE ON
SET CONSOLE OFF
```

---

## Color Constants

```harbour
// Basic colors (RGB values)
CLR_BLACK      // 0
CLR_BLUE       // 8388608
CLR_GREEN      // 32768
CLR_CYAN       // 8421376
CLR_RED        // 128
CLR_MAGENTA    // 8388736
CLR_BROWN      // 32896
CLR_HGRAY      // 12632256
CLR_GRAY       // 8421504
CLR_HBLUE      // 16711680
CLR_HGREEN     // 65280
CLR_HCYAN      // 16776960
CLR_HRED       // 255
CLR_HMAGENTA   // 16711935
CLR_YELLOW     // 65535
CLR_WHITE      // 16777215

// WebX modern colors (use with COLOR() function)
BLUE_DARK, BLUE_NAVY, BLUE_LIGHT, BLUE_SKY
SLATE_DARK, SLATE, SLATE_LIGHT
GRAY_DARK, GRAY, GRAY_LIGHT
GREEN_SUCCESS, GREEN_DARK, GREEN_LIGHT
RED_DANGER, RED_DARK, RED_LIGHT, RED_ROSE
YELLOW_WARNING, ORANGE, AMBER
PURPLE, PURPLE_DARK, VIOLET
WHITE_PURE, BLACK_PURE, TRANSPARENT

// Usage
oControl:nClrBack := COLOR(BLUE_DARK)
oControl:cBackground := RGBA(BLUE_DARK)
oControl:cGradient := GRADIENT(BLUE_LIGHT)
```

---

## Icon Constants

```harbour
// Use with ICON() function
ICON_MONEY, ICON_CARD, ICON_DOLLAR, ICON_CART
ICON_SCISSORS, ICON_TAG, ICON_PAUSE, ICON_NO_ENTRY
ICON_X_MARK, ICON_CHECK, ICON_PLUS, ICON_MINUS
ICON_SEARCH, ICON_HOME, ICON_USER, ICON_SETTINGS
ICON_REFRESH, ICON_SAVE, ICON_EDIT, ICON_PRINT
ICON_TRASH, ICON_LOCK, ICON_UNLOCK
ICON_WARNING, ICON_INFO, ICON_STAR, ICON_HEART

// Usage
oButton:cIcon := ICON(ICON_SAVE)
```

---

## Virtual Key Constants

```harbour
VK_DELETE    // 0x2E
VK_INSERT    // 0x2D
VK_F1        // 0x70
VK_F2        // 0x71
VK_F3        // 0x72
VK_F4        // 0x73
VK_F5        // 0x74
VK_F6        // 0x75
VK_F7        // 0x76
VK_F8        // 0x77
VK_F9        // 0x78
VK_F10       // 0x79
VK_F11       // 0x7A
VK_F12       // 0x7B
```

---

## RGB Color Macro

**Syntax:**
```harbour
RGB(<nRed>, <nGreen>, <nBlue>) => numeric color
```

**Example:**
```harbour
nColor := RGB(255, 0, 0)      // Red
nColor := RGB(0, 255, 0)      // Green
nColor := RGB(0, 0, 255)      // Blue
nColor := RGB(128, 128, 128)  // Gray
```

---

## Best Practices

### 1. Always Use PIXEL Mode

```harbour
// CORRECT
DEFINE WINDOW oWnd TITLE "App" SIZE 1200, 800 PIXEL
oWnd:lPixel := .T.

// WRONG
oWnd:lPixel := .F.  // Dialog units don't work on web!
```

---

### 2. Specify Parent Window

```harbour
// CORRECT
@ 100, 50 SAY "Text" TO oWnd
@ 100, 50 SAY "Text" OF oWnd

// WRONG (ambiguous)
@ 100, 50 SAY "Text"  // Where does this go?
```

---

### 3. Use Codeblocks for Actions

```harbour
// CORRECT
@ 100, 50 BUTTON "Save" TO oWnd ACTION {|| SaveData() }

// Also correct for functions
@ 100, 50 BUTTON "Save" TO oWnd ACTION SaveData()

// Inline code
@ 100, 50 BUTTON "Exit" TO oWnd ACTION {|| oWnd:End() }
```

---

### 4. Use VAR for Data Binding

```harbour
// CORRECT - Creates setget codeblock
@ 100, 50 CHECKBOX oCheck VAR lAccept OF oWnd

// Equivalent to
@ 100, 50 CHECKBOX oCheck {|u| IIF(u==NIL,lAccept,lAccept:=u)} OF oWnd
```

---

### 5. CENTER vs CENTERED

Both work - WebX accepts both spellings:
```harbour
ACTIVATE WINDOW oWnd CENTER
ACTIVATE WINDOW oWnd CENTERED  // Same thing
```

---

## Common Command Patterns

### Standard Window Creation

```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd, oMenu

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   DEFINE MENU oMenu
   MENUITEM "File" OF oMenu SUBMENU {...}

   DEFINE WINDOW oWnd TITLE "Application" SIZE 1200, 800 MENU oMenu

   // Add controls
   @ 100, 50 SAY "Hello" TO oWnd

   ACTIVATE WINDOW oWnd CENTERED
RETURN NIL
```

---

### Dialog Pattern

```harbour
FUNCTION ShowSettings()
   LOCAL oDlg, cServer := Space(50), nPort := 3306

   DEFINE DIALOG oDlg TITLE "Settings" SIZE 400, 300

   @ 50, 50 SAY "Server:" OF oDlg
   @ 50, 150 GET cServer OF oDlg SIZE 200, 30

   @ 90, 50 SAY "Port:" OF oDlg
   @ 90, 150 GET nPort PICTURE "99999" OF oDlg SIZE 100, 30

   @ 200, 100 BUTTON "OK" OF oDlg SIZE 80, 35 ACTION oDlg:End()
   @ 200, 200 BUTTON "Cancel" OF oDlg SIZE 80, 35 ACTION oDlg:End()

   ACTIVATE DIALOG oDlg CENTERED
RETURN NIL
```

---

### Browse Pattern

```harbour
FUNCTION BrowseData()
   LOCAL oWnd, oXBrw

   PUBLIC Designed_Resolution := {1920, 1080, .T.}

   USE CUSTOMERS

   DEFINE WINDOW oWnd TITLE "Customer List" SIZE 1000, 600

   @ 50, 50 XBROWSE oXBrw OF oWnd SIZE 900, 500 EDITABLE

   ADD COLUMN DATA CUSTOMERS->NAME HEADER "Name" TO oXBrw SIZE 200
   ADD COLUMN DATA CUSTOMERS->EMAIL HEADER "Email" TO oXBrw SIZE 250
   ADD COLUMN DATA CUSTOMERS->PHONE HEADER "Phone" TO oXBrw SIZE 150

   ACTIVATE WINDOW oWnd CENTERED
RETURN NIL
```

---

## See Also

- [webx_gui_classes.md](webx_gui_classes.md) - Complete class reference
- [webx_language_rules.md](webx_language_rules.md) - Harbour language guide
- [SPEC_webx_functions.md](SPEC_webx_functions.md) - Function reference

---

**© 2025 WebX Framework - xCommand Reference**
Last Updated: 2026-01-21
