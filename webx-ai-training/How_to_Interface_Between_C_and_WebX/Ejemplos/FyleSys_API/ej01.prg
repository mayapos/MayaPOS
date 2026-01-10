//------------------------------------------------------------------------------
// Ejemplo de uso del sistema log manager
// Prgrama ej01.prg
//------------------------------------------------------------------------------

procedure main

    local n := 0
    local cFNane := "miArchivo.log"

    cls

    // Reiniciamos si existe el fichero
    // Simula errores
    writeLog( cFNane, .t., hb_TToC( hb_DateTime() ) + " - Se ha producido el error numero: " + HB_NToS( n ) )
    // Añade
    for n := 1 to 20
        writeLog( cFNane, .f., hb_TToC( hb_DateTime() )  + " - Se ha producido el error numero: " + HB_NToS( n ) )
    next

    ? loadLog( cFNane )

    ? "Ahora creamos y leemos otro con el mismo nombre"
    ? "escribiendo diferentes tipos de datos:"

    Inkey( 100 )

    ?

    // Escribe en el fichero. Si existe lo destruye y lo crea denuevo (.t.)
    writeLog( cFNane, .t., "------------------------------------------------------------------------" )
    // Ecribe las siguientes lineas en el fichero existente
    writeLog( cFNane,, "Esta es la priemra linea..." )
    writeLog( cFNane,, Date() )
    writeLog( cFNane,, Time() )
    writeLog( cFNane,, 1367.89 )
    writeLog( cFNane,, .t. )
    writeLog( cFNane,, "" )
    writeLog( cFNane,, "Esto es todo..." )

    ? loadLog( cFNane )

    Inkey( 100 )

return

//------------------------------------------------------------------------------
