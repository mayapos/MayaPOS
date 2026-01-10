/*
 * Uso de funciones en de C para tratar array
 * ej008.prg
 */

procedure main

    local aBuf

    cls

    use test new

    test->( DBGoTo( 10 ) )
    aBuf := test->( aGather() ) // Lee el registro actual

    ? "------------------------------------------------------------------------"
    ? "Tipo: " + ValType( aBuf ), "  /  Num. elementos: " + HB_NToS( Len( aBuf ) )
    ? "------------------------------------------------------------------------"
    ? test->( RecNo() ), aBuf[ 2 ], aBuf[ 9 ]
    ? "------------------------------------------------------------------------"
    ? "Cambiamos la edad con un entero aleatorio"
    aBuf[ 9 ] := HB_RandomInt( 0, 99 )
    ? "El valor en buffer es:", aBuf[ 9 ]
    test->( aScatter( aBuf ) )  // Escribe en el registro
    ? "------------------------------------------------------------------------"
    ? "La edad en la DBF es ahora", test->( FieldGet( 9 ) )
    ? "------------------------------------------------------------------------"
    Inkey( 100 )

return