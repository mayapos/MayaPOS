/*
 * Uso de funciones en de C para tratar hash
 * ej010.prg
 */

procedure main

    local hBuf

    cls

    use test new

    test->( DBGoTo( 10 ) )
    hBuf := test->( hGather() ) // Lee el registro actual

    ? "------------------------------------------------------------------------"
    ? "Tipo: " + ValType( hBuf ), "  /  Num. elementos: " + HB_NToS( Len( hBuf ) )
    ? "------------------------------------------------------------------------"
    ? test->( RecNo() ), hBuf[ "Last" ], hBuf[ "age" ]
    ? "------------------------------------------------------------------------"
    ? "Cambiamos la edad con un entero aleatorio"
    hBuf[ "age" ] := HB_RandomInt( 0, 99 )
    ? "El valor en buffer es:", hBuf[ "age" ]
    test->( hScatter( hBuf ) )  // Escribe en el registro
    ? "------------------------------------------------------------------------"
    ? "La edad en la DBF es ahora", test->( FieldGet( FieldPos( "age" ) ) )
    ? "------------------------------------------------------------------------"
    Inkey( 100 )

return
	