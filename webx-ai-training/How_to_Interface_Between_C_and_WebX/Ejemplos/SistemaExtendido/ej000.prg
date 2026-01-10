//------------------------------------------------------------------------------
// Ejercicio piloto
// ej000.prg
// Simbolos
//------------------------------------------------------------------------------

procedure main()

	losSimbolos()
	
    ? "Presiona una tecla para salir..."
    Inkey( 100 )

return

// Los simbolos

static procedure losSimbolos()

    // Prueba con tabla de simbolos
    // __dynsN2Sym devuelve una referencia de la funcion en la tabla de simbolos
    __dynsN2Sym( "Alert" ):exec( "Hola mundo" )

    // Otra manera de usar las funciones de la tabla de simbolos
    ( @alert() ):exec( "Prueba de funciones por referencia;A continuación se mostrara;un listado de todos los simbolos" )

    i := __dynsCount()
	
	? "El numero de símbolos es", i
	
    for n := 1 to i
        ? n, __dynsGetName( n )
        if n % 23 == 0
            ? "Enter para seguir..."
            Inkey( 100 )
        endif
    next

return
