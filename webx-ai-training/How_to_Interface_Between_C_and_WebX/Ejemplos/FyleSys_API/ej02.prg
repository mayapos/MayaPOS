//------------------------------------------------------------------------------
// Ejemplo de uso del sistema log manager
// Prgrama ej02.prg
//------------------------------------------------------------------------------

#include "Box.ch"

procedure main

    local n := 0
    local cFNane := "miArchivo.log"

    // Reiniciamos si existe el fichero
    // Simula errores
    writeLog( cFNane, .t., hb_TToC( hb_DateTime() ) + " - Se ha producido el error numero: " + HB_NToS( n ) )
    // Añade
    for n := 1 to 20
        writeLog( cFNane, .f., hb_TToC( hb_DateTime() )  + " - Se ha producido el error numero: " + HB_NToS( n ) )
    next

    verLog( cFNane )

    cls

    ? "Ahora creamos y leemos otro con el mismo nombre"
    ? "escribiendo diferentes tipos de datos:"

    Inkey( 100 )

    // Escribe en el fichero. Si existe lo destruye y lo crea denuevo (.t.)
    writeLog( cFNane, .t., "-------------------------------------------------------------" )
    // Ecribe las siguientes lineas en el fichero existente
    writeLog( cFNane,, "Esta es la priemra linea..." )
    writeLog( cFNane,, Date() )
    writeLog( cFNane,, Time() )
    writeLog( cFNane,, 1367.89 )
    writeLog( cFNane,, .t. )
    writeLog( cFNane,, "" )
    writeLog( cFNane,, "Esto es todo..." )

    verLog( cFNane )

    cls
    ? "Ahora vamos a leer cuaquier archivo, por ejemplo el código fuente ej01.prg"

    Inkey( 100 )

    verLog( "ej02.prg" )

return

//------------------------------------------------------------------------------
// Muestra el contenido del archivo pasa usan el sistema log

static procedure verLog( cFileName )

    cls

    @ 01, 25 SAY "Contenido de: " + cFileName COLOR "GR+/R+"
    @ 02, 09, 21, 71 BOX B_DOUBLE_SINGLE + Space(1)

    MemoEdit( loadLog( cFileName ), 03, 10, 20, 70, .f. )

return

//------------------------------------------------------------------------------
