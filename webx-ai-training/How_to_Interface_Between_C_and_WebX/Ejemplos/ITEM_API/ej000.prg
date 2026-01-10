/* 
 * ej000.prg
 * Uso de ITEM
 */

procedure main

    local cVar, nVar, dVar, lVar
    local aVar := Array( 4 )

    SET DATE FORMAT TO "dd/mm/yyyy"

    cls

    ? "Asignacion de variables desde C:"
    ? "--------------------------------"
    ?
    asignaVarC( @cVar, @nVar, @dVar, @lVar, aVar )

    ? "Cadena...:", cVar
    ? "Numero...:", nVar
    ? "Fecha....:", dVar
    ? "Logico...:", lVar
    ?
    ? "Array....:"
    for i := 1 to 4
        ? i, aVar[ i ]
    next

    ?
    ? "Presione ENTER para seguir..."
    Inkey( 100 )

return
	