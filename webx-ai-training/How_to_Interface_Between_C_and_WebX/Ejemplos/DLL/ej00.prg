/*
 * ej00.prg
 * Uso de DLL
 */

PROCEDURE main()

    local hWnd

    WinExec( "calc", 1 )

    MessageBox( 0, "Espera que se abra la calculadora y presiona una tecla para seguir...", "Atencion" )

    hWnd := FindWindow( , "Calculadora" )

    SetWindowText( hWnd, "Kalkuladora" )

RETURN
