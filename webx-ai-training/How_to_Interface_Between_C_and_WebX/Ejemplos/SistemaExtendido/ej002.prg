//------------------------------------------------------------------------------
// Ejercicio sobre estructura con el sistema extendido
// En PRG es un array con los mismo elementos que la estructura
// ej002.prg
//------------------------------------------------------------------------------

procedure main

    local aPersona := damePersona( 1 );

    set date format to "dd-mm-yyyy"

    cls

    ? "Datos de la persona 1 con su tipo de dato:"
    for n := 1 to Len( aPersona )
        ? aPersona[ n ], " -> ", ValType( aPersona[ n ] )
    next
    ?
    ? "Presiona ENTER..."
    Inkey( 100 )

    aPersona := damePersona( 2 );

    ? "Datos de la persona 2:"
    for n := 1 to Len( aPersona )
        ? aPersona[ n ]
    next
    ?
    ? "Presiona ENTER..."
    Inkey( 100 )

return