# Software Bill of Materials (SBOM) - WebX Project
**Version:** 2.0.0
**Status:** BETA TESTING	
**Last Updated:** 2026-02-05
**Project Lead:** Byron @ MayaBuilders@gmail.com

---

## Executive Summary
This document provides a comprehensive inventory of all components, libraries, and dependencies 
used in the **WebX** Framework. 
WebX is a complete web framework for migrating legacy xBase desktop applications to the web, 
providing 2,000+ runtime functions and 50+ UI control classes.

**Key Statistics:**
- **Total Runtime Functions:** 2,000+
- **UI Control Classes:** 50+
- **Supported Dialects:** Clipper, Harbour, xHarbour, FiveWin, Visual FoxPro, Alaska xBase++, Xailer, HIX
- **Deployment Modes:** 7 (PHP, CGI, FastCGI, mod_apache, Server, Desktop)

---

## Layer 1: Foundation (External Infrastructure)
*The environment and third-party runtimes required to host and build WebX.*

| Component | Version | License | Origin | Description |
| :--- | :--- | :--- | :--- | :--- |
| **Apache HTTP Server** | 2.4.x (XAMPP 2025) | Apache 2.0 | Apache Foundation | The primary web server engine. |
| **PHP Runtime** | 8.2.12 | PHP License | PHP Group | Backend execution engine for transpiled code. |
| **Harbour Core** | 3.0.0 | GNU GPL v3 + Linking Exception | Harbour Project | The base xBase language engine. |
| **xHarbour** | 1.3.1 | GNU GPL v3 | xHarbour.org | Legacy xBase compatibility layer. |
| **MSVC 2022** | 17.x (Build Tools) | Proprietary | Microsoft | Compiler used for binaries (`.exe`, `.so`). |
| **XAMPP Environment** | 2025 Distribution | Mixed | Apache Friends | Unified local server stack. |
| **mod_harbour** | 2.x | MIT | Harbour Community | Apache module foundation (inspiration for mod_webx). |

---

## Layer 2: Core (WebX Proprietary Components)
*The primary drivers and binaries developed specifically for the WebX ecosystem.*

### 2.1 Transpiler & Runtime

| Component | Filename | Status | Description |
| :--- | :--- | :--- | :--- |
| **WebX Transpiler** | `webxphp.exe` | ACTIVE | Converts Harbour/xBase (.prg) to high-performance PHP code. |
| **WebX Server Module** | `mod_webx.so` | ACTIVE | Native Apache module for Direct-Harbour execution (HIX compatibility). |
| **WebX PHP Runtime** | `webx_runtime.php` | CORE | Hand-written PHP library emulating the Harbour VM and OOP system. |
| **WebX Global Header** | `WebX.ch` | CORE | Main preprocessor file standardizing commands across dialects. |
| **WebX Compat Header** | `WebXCompat.ch` | CORE | Compatibility layer for cross-dialect support. |
| **HBClass Stub** | `hbclass_stub.php` | CORE | Harbour metaclass system emulation (HBObject, HBClass). |

### 2.2 Database Layer

| Component | Filename | Status | Description |
| :--- | :--- | :--- | :--- |
| **WebX ORM** | `webx_orm.php` | ACTIVE | Unified SQL/DBF database access with PDO backend. |
| **DBF Handler** | `DBFHandler.php` | ACTIVE | Pure PHP implementation for reading/writing DBF files. |
| **TDatabase Class** | `webx_orm.php` | ACTIVE | Harbour-compatible database abstraction class. |
| **SQL System** | `vfp_sql_system.c` | ACTIVE | C-level integration for VFP-style SQL cursor handling. |

### 2.3 Support Tools

| Component | Filename | Status | Description |
| :--- | :--- | :--- | :--- |
| **Log Manager** | `webx_log_manager.php` | TOOL | Internal system for health monitoring and audit trails. |
| **Calculator** | `webx_calculator.php` | TOOL | Web-based calculator for WinExec("Calc") compatibility. |
| **ID Generator** | `webx_id_generator.php` | CORE | Unique control ID generation for HTML elements. |

---

## Layer 3: Harbour Runtime Library Stubs
*PHP implementations of Harbour RTL functions (~2,000+ functions total).*

### 3.1 Core RTL Functions (792 functions)

| Component | Filename | Functions | Description |
| :--- | :--- | :--- | :--- |
| **Harbour RTL Stubs** | `harbour_rtl_stubs.php` | 792 | Core Harbour runtime functions: strings, arrays, math, I/O, dates. |
| **Harbour Functions Addon** | `harbour_functions_addon.php` | 50+ | Additional RTL functions for edge cases. |

**Key Function Categories:**
- String functions: ALLTRIM, SUBSTR, LEFT, RIGHT, UPPER, LOWER, PADR, PADL, PADC, AT, RAT, STRTRAN, STUFF, REPLICATE, SPACE, TRANSFORM, etc.
- Array functions: AADD, ASIZE, ADEL, AINS, AFILL, ACLONE, ACOPY, ASCAN, ASORT, AEVAL, ATAIL, etc.
- Math functions: ABS, INT, ROUND, SQRT, EXP, LOG, MOD, MIN, MAX, etc.
- Date functions: DATE, CTOD, DTOC, DTOS, DOW, DOM, DOY, CDOW, CMONTH, YEAR, MONTH, DAY, etc.
- I/O functions: QOUT, QQOUT, OUTSTD, OUTERR, INKEY, CHR, ASC, etc.
- Type functions: VALTYPE, TYPE, EMPTY, LEN, NIL, etc.

### 3.2 Clipper Tools Library (200+ functions)

| Component | Filename | Functions | Description |
| :--- | :--- | :--- | :--- |
| **Clipper Tools Stubs** | `harbour_ct_stubs.php` | 200+ | hbct contrib library - advanced string, date, math functions. |

**Key Function Categories:**
- String functions: ADDASCII, ATNUM, CHARREM, WORDTOCHAR, PADLEFT, PADRIGHT, CHARSWAP, CHARONE, CHARONLY, CHARADD, CHARSUB, CHARMIX, etc.
- Date functions: BOM, EOM, BOQ, EOQ, BOY, EOY, ADDMONTH, CTODOW, DOW, WOM, ISLEAP, DAYSINMONTH, QUARTER, WEEK, etc.
- Math functions: CEILING, FLOOR, SIGN, FACT, MANTISSA, EXPONENT, etc.
- Bit functions: NUMAND, NUMOR, NUMXOR, NUMNOT, NUMROL, NUMMIR, etc.

### 3.3 NanForum Library (100+ functions)

| Component | Filename | Functions | Description |
| :--- | :--- | :--- | :--- |
| **NanForum Stubs** | `harbour_nf_stubs.php` | 100+ | hbnf contrib library - array, conversion, utility functions. |

**Key Function Categories:**
- Array functions: FT_ASUM, FT_AAVG, FT_AMIN, FT_AMAX, FT_AMEDIAN, FT_AREVERSE, FT_ASHUFFLE, etc.
- Conversion functions: FT_NTOW (number to words), FT_D2E (decimal to other bases), FT_E2D (other bases to decimal).
- Bit functions: FT_BITSET, FT_BITCLR, FT_BITTOG, FT_ISBIT.
- String functions: FT_PROPER (proper case), FT_BYTEAND, FT_BYTEOR, FT_BYTEXOR, FT_BYTENOT.

### 3.4 PCRE Regex Library (40+ functions)

| Component | Filename | Functions | Description |
| :--- | :--- | :--- | :--- |
| **Regex Stubs** | `harbour_regex_stubs.php` | 40+ | hbpcre contrib library - Perl-compatible regular expressions. |

**Key Functions:**
- Pattern matching: HB_REGEXCOMP, HB_REGEXMATCH, HB_REGEXLIKE, HB_REGEXHAS, HB_REGEX.
- Find/Extract: HB_REGEXFIND, HB_REGEXFINDALL, HB_REGEXALL, HB_REGEXATX.
- Replace/Split: HB_REGEXSUB, HB_REGEXREPLACE, HB_REGEXSPLIT.
- Utilities: HB_REGEXESCAPE, HB_REGEXCOUNT, HB_REGEXTEST.
- Character classes: HB_ISALPHA, HB_ISDIGIT, HB_ISALNUM, HB_ISUPPER, HB_ISLOWER, HB_ISSPACE, HB_ISPRINT, HB_ISGRAPH, HB_ISPUNCT, HB_ISCNTRL, HB_ISXDIGIT.

### 3.5 TIP Internet Protocol Library (50+ functions/methods)

| Component | Filename | Classes/Functions | Description |
| :--- | :--- | :--- | :--- |
| **TIP Stubs** | `harbour_tip_stubs.php` | 50+ | hbtip contrib library - HTTP, SMTP, FTP protocol clients. |

**Classes:**
- `TIPClientHTTP` - Full HTTP client with GET, POST, PUT, DELETE, HEAD, download support.
- `TIPClientSMTP` - Email sending with MIME support, attachments, HTML body.
- `TIPClientFTP` - FTP operations: upload, download, directory listing, rename, delete.

**Factory Functions:**
- TIP_HTTP(), TIP_SMTP(), TIP_FTP() - Create protocol client instances.
- TIP_GET(), TIP_POST(), TIP_PUT(), TIP_DELETE() - Quick HTTP operations.
- TIP_DOWNLOAD(), TIP_MAIL() - High-level operations.
- TIP_URLENCODE(), TIP_URLDECODE(), TIP_HTMLENCODE(), TIP_HTMLDECODE() - Encoding helpers.
- TIP_BASE64ENCODE(), TIP_BASE64DECODE(), TIP_JSON(), TIP_JSONPARSE() - Format conversion.

---

## Layer 4: Compatibility Adapters (Bridges)They may behave diferently, 
##          since they are compatible only, and they return what we believe their original frameworks return...
*Stubs and interfaces that allow legacy code to run unmodified on WebX.*

### 4.1 FiveWin Compatibility (300+ functions/classes) 

| Component | Filename | Functions/Classes | Description |
| :--- | :--- | :--- | :--- |
| **FiveWin Stubs** | `fivewin_stubs.php` | 300+ | FiveWin API compatibility layer. |
| **FiveWin Compat** | `webx_fivewin_compat.php` | 50+ | Additional FiveWin UI mappings. |

**Classes Provided:**
- UI Controls: TTimer, TSplitter, TIcon, TCursor, TPrinter, TBar.
- Window: TWindow, TDialog, TMDIWindow, TMDIClient, TMDIChild.
- Data: TDataBase, TDbfServer, TRecordSet.

**Function Categories:** 
- Version: FWVERSION(), FWDESCRIPTION(), FWCOPYRIGHT().
- Color: NRGB(), GETRED(), GETGREEN(), GETBLUE(), COLORTORGB(), COLORTOHEX(), CLR_*.
- Message boxes: MSGINFO(), MSGSTOP(), MSGALERT(), MSGYESNO(), MSGRETRYCANCEL(), MSGWAIT().
- Input dialogs: MSGGET(), MSGMULTIGET(), MSGSELECT(), MSGDATE(), MSGRADIO(), MSGLIST().
- File operations: CGETFILE(), CGETDIR(), CPUTFILE(), CSAVEFILE(), CGETCOLOR(), CGETFONT().
- System: SYSREFRESH(), CURSORWAIT(), CURSORARROW(), WINEXEC(), SHELLEXECUTE(), WAITRUN(), GETENV(), SETENV().
- Date: CTOD(), DTOC(), DTOS(), STOD(), DATE(), TIME(), YEAR(), MONTH(), DAY(), CDOW(), CMONTH(), SECONDS(), ELAPTIME().
- Array: AADD(), ASIZE(), AFILL(), ACLONE(), ASCAN(), ATAIL(), AINS(), ADEL().
- String: STUFF(), STRTRAN(), MEMOREAD(), MEMOWRIT(), VAL(), STR(), TRANSFORM().
- Web: WEBX_REDIRECT(), WEBX_REFRESH(), WEBX_PRINT(), WEBX_DOWNLOAD().

**Constants Provided:**
- Window styles: WS_OVERLAPPED, WS_POPUP, WS_CHILD, WS_VISIBLE, WS_BORDER, etc.
- Message box: MB_OK, MB_YESNO, MB_OKCANCEL, MB_ICONERROR, MB_ICONQUESTION, etc.
- Virtual keys: VK_RETURN, VK_ESCAPE, VK_TAB, VK_F1-VK_F12, etc.
- Colors: CLR_BLACK, CLR_WHITE, CLR_RED, CLR_GREEN, CLR_BLUE, CLR_YELLOW, etc.
- File attributes: FA_NORMAL, FA_READONLY, FA_HIDDEN, FA_SYSTEM, FA_DIRECTORY, etc.

### 4.2 Other Dialect Support

| Ecosystem | Component | Type | Responsibility |
| :--- | :--- | :--- | :--- |
| **Visual FoxPro** | `WebXVFP/` | Transpiler Layer | Support for REPLACE, SCAN, SQL Cursor commands. |
| **Xbase++** | `webx_xbase.php` | Emulation | Alaska Software style OOP and data handling. |
| **Xailer** | `source/include/xailer.ch` | Preprocessor | Command mapping for Xailer UI definitions. |
| **HIX** | `HIX/`, `compat.php` | Server Layer | High-speed Harbour Interface for Microservices. |

---

## Layer 5: WebX UI Control Classes (50+ classes)
*PHP implementations of WebX UI controls that generate HTML/CSS/JavaScript.*

### 5.1 Core Window Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TWindow | `webx_window_simple.php` | Main application window container. |
| TDialog | `webx_dialog.php` | Modal dialog windows. |
| TMDI | `webx_mdi.php` | Multi-document interface support. |
| TControl | `webx_control.php` | Base class for all controls. |
| TFont | `webx_font.php` | Font management. |

### 5.2 Input Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TGet | `webx_get.php` | Text input fields. |
| TMultiGet | `webx_multiget.php` | Multi-line text areas. |
| TCheckBox | `webx_checkbox.php` | Checkbox controls. |
| TRadio | `webx_radio.php` | Radio button groups. |
| TComboBox | `webx_combobox.php` | Dropdown selection. |
| TListBox | `webx_listbox.php` | List selection. |
| TDatePicker | `webx_datepicker.php` | Date selection. |
| TCodeEditor | `webx_codeeditor.php` | Syntax-highlighted code editor. |
| TUpload | `webx_upload.php` | File upload control. |

### 5.3 Display Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TSay | `webx_say.php` | Static text labels. |
| TImage | `webx_image.php` | Image display. |
| TProgress | `webx_progress.php` | Progress bars. |
| TSpinner | `webx_spinner.php` | Loading spinners. |
| TChart | `webx_chart.php` | Data visualization (Chart.js). |
| TQRCode | `webx_qrcode.php` | QR code generation. |

### 5.4 Data Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TBrowse | `webx_browse.php` | Standard data browser. |
| TXBrowse | `webx_xbrowse.php` | Enhanced grid (ag-Grid). |
| TTreeView | `webx_treeview.php` | Hierarchical tree display. |

### 5.5 Container Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TGroup | `webx_group.php` | Control grouping. |
| TFolder | `webx_folder.php` | Tab containers. |
| TFolderTabs | `webx_foldertabs.php` | Tab bar component. |
| TTabs | `webx_tabs.php` | Tab navigation. |
| TAccordion | `webx_accordion.php` | Collapsible sections. |
| TCard | `webx_card.php` | Card containers. |
| TLayout | `webx_layout.php` | Responsive layout system. |
| TLayoutSection | `webx_layout_section.php` | Layout sections. |

### 5.6 Navigation Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TMenu | `webx_menu.php` | Menu bar. |
| TRibbon | `webx_ribbon.php` | Office-style ribbon. |
| TButtonBar | `webx_buttonbar.php` | Toolbar buttons. |
| TNavBar | `webx_navbar.php` | Navigation bar. |
| TBreadcrumb | `webx_breadcrumb.php` | Breadcrumb navigation. |
| TSidebar | `webx_sidebar.php` | Sidebar navigation. |
| TMacDock | `webx_macdock.php` | macOS-style dock. |
| TPagination | `webx_pagination.php` | Page navigation. |

### 5.7 Action Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TButton | `webx_button.php` | Standard buttons. |
| TStatusBar | `webx_statusbar.php` | Status bar. |

### 5.8 Feedback Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TAlert | `webx_alert.php` | Alert messages. |
| TToast | `webx_toast.php` | Toast notifications. |
| TModal | `webx_modal.php` | Modal dialogs. |
| TPopover | `webx_popover.php` | Popovers. |
| TTooltip | `webx_tooltip.php` | Tooltips. |

### 5.9 Specialty Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TCarousel | `webx_carousel.php` | Image carousels. |
| TTVAdvertisement | `webx_tv_advertisement.php` | TV-style advertisements. |
| TLogin | `webx_login.php` | Login form. |

### 5.10 Report Controls

| Class | Filename | Description |
| :--- | :--- | :--- |
| TEasyReport | `webx_easyreport.php` | Simple reporting. |
| TReportJSON | `webx_report_json.php` | JSON-based reports. |

### 5.11 POS System Components

| Class | Filename | Description |
| :--- | :--- | :--- |
| TPOSDatabase | `webx_pos_database.php` | POS data access. |
| TPOSAdmin | `webx_pos_admin.php` | POS administration. |
| TPOSButtonStyle | `webx_pos_buttonstyle.php` | POS button styling. |
| TPOSCategoryButton | `webx_pos_buttons.php` | Category buttons. |
| TPOSProductButton | `webx_pos_buttons.php` | Product buttons. |
| TPOSCart | `webx_pos_cart.php` | Shopping cart. |
| TPOSCategoryGrid | `webx_pos_categorygrid.php` | Category grid. |
| TPOSProductGrid | `webx_pos_productgrid.php` | Product grid. |
| TPOSNumpad | `webx_pos_numpad.php` | Numeric keypad. |
| TPOSScreen | `webx_pos_screen.php` | POS main screen. |
| TPOSScreen2 | `webx_pos_screen2.php` | Alternative POS screen. |
| TPOSActionButtons | `webx_pos_actionbuttons.php` | POS action buttons. |
| TPOSTitleBar | `webx_pos_titlebar.php` | POS title bar. |
| TKitchenScreen | `webx_kitchen_screen.php` | Kitchen display. |

---

## Layer 6: Frontend & External Dependencies
*Third-party UI libraries and assets integrated into the WebX components.*

| Library | Version | Delivery | License | Description |
| :--- | :--- | :--- | :--- | :--- |
| **Bootstrap** | 5.3.2 | CDN (jsDelivr) | MIT | CSS Framework for core UI components. |
| **Bootstrap Icons** | 1.11.2 | CDN (jsDelivr) | MIT | Vector icon set for toolbars and menus. |
| **FontAwesome** | 6.5.1 | CDN (cdnjs) | CC BY 4.0 | Enhanced icon library for advanced UI. |
| **ag-Grid Community** | 32.0.2 | CDN (jsDelivr) | MIT | High-performance data grid for XBrowse. |
| **Chart.js** | 4.4.1 | CDN (jsDelivr) | MIT | Data visualization and charting engine. |
| **Tailwind CSS** | 3.x | CDN/Build | MIT | Utility-first CSS for POS/Card components. |
| **Mac Dock Assets** | Custom | Local (`/assets/`) | Proprietary | Animated dock component for Apple-style UI. |

---

## Layer 7: AJAX & Communication

| Component | Filename | Description |
| :--- | :--- | :--- |
| **WebX AJAX Bridge** | `webx_ajax.php` | Server-side AJAX handler for WEBX_CALL(). |
| **WebX AJAX Client** | `webx-ajax.js` | Client-side JavaScript for AJAX requests. |
| **WebX Professional CSS** | `webx-professional.css` | Professional styling for WebX controls. |

---

## Security & Compliance Notes

1. **No Proprietary Code**: WebX does **not** include or distribute original source code from FiveWin (FWH) or Xbase++. 
                            It provides API-compatible *interfaces* only.

2. **GPL Compliance**: WebX utilizes the Harbour 3.0.0 core under the GPL v3 license with linking exception, 
                       which permits commercial applications. Modifications to the core VM are tracked in the `mod_WebX` source tree.

3. **Macro Security**: The system includes a custom PHP sandbox for evaluating macros, preventing code injection via legacy data fields.

4. **Input Validation**: All user input is sanitized through the runtime before processing.

5. **Database Security**: The WebX ORM uses PDO with prepared statements for SQL databases, preventing SQL injection.

6. **License Attribution**: All open-source components include proper license files and attribution.

7. **Desktop-to-Web Translation Limitations**: Many legacy xBase/Windows commands have no direct web equivalent
   because they are Windows API or desktop-exclusive operations. WebX addresses this through:

   - **Web Alternatives**: Commands like `WinExec("Calc")` are replaced with web-based implementations
     (e.g., `webx_calculator.php` opens a browser-based calculator).
   - **No-Op Stubs**: Commands that have no web meaning (e.g., `SetCursor()`, `ShowWindow()`) return
     sensible defaults without causing errors.
   - **Best-Effort Representations**: UI commands are translated to their closest HTML/CSS/JavaScript
     equivalents (e.g., Windows message boxes become Bootstrap modals).
   - **Documented Gaps**: Functions that cannot be reasonably translated are documented and return
     placeholder values to maintain code flow.

   **Note:** Behavior may differ from original desktop implementations. WebX provides *functional compatibility*
   rather than *exact replication* of Windows API behavior.

---

## Function Count Summary

| Component | Approximate Count |
| :--- | :--- |
| Harbour RTL (harbour_rtl_stubs.php) | 792 functions |
| Harbour Functions Addon | 50+ functions |
| Clipper Tools (harbour_ct_stubs.php) | 200+ functions |
| NanForum (harbour_nf_stubs.php) | 100+ functions |
| PCRE Regex (harbour_regex_stubs.php) | 40+ functions |
| TIP Protocol (harbour_tip_stubs.php) | 50+ functions/methods |
| FiveWin (fivewin_stubs.php) | 300+ functions |
| WebX Classes | 50+ classes with 500+ methods |
| **TOTAL** | **~2,000+ functions** |

---

## Deployment Modes

WebX supports 7 deployment modes:

1. **WebXPHP (Transpiled PHP)** - Harbour code transpiled to pure PHP
2. **CGI (.exe)** - Traditional CGI executable
3. **FastCGI** - Persistent FastCGI process
4. **mod_webx (.so)** - Native Apache module
5. **Server with HIX Compatibility** - High-speed microservice interface
6. **Docker** - Containerized deployment
7. **Hybrid** - Mix of modes for optimization

See [WEBX_DEPLOYMENT_MODES.md](../webx-ai-training/webx_deployment_options.md) for details.

---

## Maintenance Log

| Date | Change |
| :--- | :--- |
| 2026-02-05 | Initial SBOM structure defined (Layers 1, 2, and 3). |
| 2026-02-05 | Added Layer 4 (Frontend Dependencies). |
| 2026-02-05 | Updated xHarbour to 1.3.1 and PHP to 8.2.12. |
| 2026-02-05 | **MAJOR UPDATE:** Added complete Harbour extended libraries. |
| 2026-02-05 | Added Layer 5 (50+ WebX UI Control Classes). |
| 2026-02-05 | Added Layer 6 (Frontend Dependencies with versions). |
| 2026-02-05 | Added Layer 7 (AJAX & Communication). |
| 2026-02-05 | Added Function Count Summary (~2,000+ functions). |
| 2026-02-05 | Added Deployment Modes section. |
| 2026-02-05 | Updated to BETA TESTING status. |
| 2026-02-05 | Published to public repository for transparency. |

---

## Contact

**Project:** WebX Framework
**Organization:** xBasePHP
**Website:** https://xBasePHP.com
**Repository:** Private (GitHub: mayapos)
