# Developing MayaPOS with WebX

**Version 1.1** (Feb 18, 2026)

## 1. Environment Setup
To build or modify MayaPOS, ensure your WebX environment is configured:
1.  **WebX Framework**: Install in `../webx` relative to `mayapos`.
2.  **Include Path**: Ensure your transpiler points to `../webx/WebXPHP/include`.
3.  **Classes**: The runtime relies on `../webx/webxphp_classes`.

## 2. Using Updated Commands
MayaPOS leverages the newly standardized WebX commands.

### 2.1 POS Buttons
Instead of complex object creation, use the declarative syntax:
```xbase
@ 10, 10 POS CATEGORY oBtn PROMPT "Drinks" ;
   BITMAP "drinks.png" ;
   ACTION ShowDrinks() ;
   OF oWnd
```

### 2.2 Modern Dialogs
Use standard FiveWin syntax for flawless dialogs:
```xbase
DEFINE DIALOG oDlg RESOURCE "LOGIN" ;
   TITLE "Access Control" ;
   TRANSPARENT
   
   REDEFINE GET oGet ID 101 OF oDlg
   REDEFINE BUTTON ID 102 OF oDlg ACTION Verify()
ACTIVATE DIALOG oDlg CENTERED
```

### 2.3 Printing Receipts
Direct PDF generation replaces legacy printing:
```xbase
PRINT TO PDF oPdf FILE "ticket.pdf" SIZE 80
   oPdf:Text( 10, 10, "MAYA POS TICKET" )
   // ... content ...
oPdf:End()
```

## 3. Best Practices
*   **Keep Logic Pure**: Avoid mixing HTML/PHP directly in PRG. Use WebX commands.
*   **Use Resources**: `.rc` files are fully supported for dialog layouts.
*   **Separation of Concerns**: Keep business logic in `.prg` functions, UI in `DEFINE` commands.

## 4. Troubleshooting
If you encounter syntax errors:
1.  Verify `include/WebX.ch` is the latest version.
2.  Check `tools/compare_ch.py` output for discrepancies.
3.  Ensure your class library (`webxphp_classes`) matches the include files.
