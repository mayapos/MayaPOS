/*
 * Uso de funciones en de C para tratar arrays
 * ej007.prg
 */

procedure main

    local aDesdeC
    local aArray := { 12.30, 11, 20, 3, 23, 89, 5, 15, 33.75, 1.98 }
    local nLen := Len( aArray )
    local nSuma := 100.55       // Prueba cambiar el numero

    set date format to "dd-mm-yyyy"

    cls

    // Esta funcion en C suma a lo elementos del array el valor del 2 parametro
    tramita( aArray, nSuma )

    ? "------------------------------------------------------------------------"
    ? "El valor de sumando:", nSuma
    ? "------------------------------------------------------------------------"
    ? "Valores anteriores", "Valores nuevos"
    ? "------------------------------------------------------------------------"

    for i := 1 to nLen
        ? aArray[ i ] - nSuma, aArray[ i ]
    next

    ?
    ? "Presiona una tecla para seguir..."
    Inkey( 100 )

    cls

    ?
    ? "------------------------------------------------------------------------"
    ? "Array creado desde C:"
    ? "------------------------------------------------------------------------"
    ?

    aDesdeC := creaArray()
    nLen := Len( aDesdeC )

    for i := 1 to nLen
        ? "Elemento " + HB_NToS( i ), aDesdeC[ i ]
    next

    ? "------------------------------------------------------------------------"
    ?
    Inkey( 100 )

return
	