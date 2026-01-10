/*
 * Uso de funciones en de C para tratar hash
 * ej009.prg
 */

procedure main

    local hTabla, xClave, xValor, xPar
    local nLen, i

    cls

    ?
    ? "------------------------------------------------------------------------"
    ? "Hash creado desde C:"
    ? "------------------------------------------------------------------------"
    ?

    hTabla := creaHash()
    nLen := Len( hTabla )

    hb_HCaseMatch( hTabla, .f. )  // Le da igual mayuscula o minusculas

    ?
    ? "El hash tiene " + HB_NToS( nLen ) + " pares ( clave, valor )"
    ?
    ? "------------------------------------------------------------------------"
    ? "Lo mostramos usando un for next:"
    ? "------------------------------------------------------------------------"
    for i := 1 to nLen
        xClave := hb_HKeyAt( hTabla, i )
        ? "Clave: ", xClave, " -> Valor: ", hb_HGet( hTabla, xClave )
    next
    ?
    ? "------------------------------------------------------------------------"
    ? "Recomendado: usando un for each:"
    ? "------------------------------------------------------------------------"

    for each xPar in hTabla
        ? "Clave: ", xPar:__enumKey(), " -> Valor: ", xPar:__enumValue()
    next

    ? "------------------------------------------------------------------------"
    ?
    Inkey( 100 )

return
