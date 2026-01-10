/*
 * Uso de Interface de la funcion de C
 */

procedure main

    local getlist := {}
    local cFrase := Space( 60 )
    local cSep := Space( 2 )
    local cToken, n := 0
    local nNum := 0.0

    set decimal to 6

    cls

    @ 01, 01 SAY "Interfaces..."
    @ 02, 01 SAY "Dame una frase:" GET cFrase PICTURE "@k!"
    @ 03, 01 SAY "Separador.....:" GET cSep   PICTURE "@k!"
    @ 04, 01 SAY "Entre numero..:" GET nNum   PICTURE "@k"
    read

    cFrase := AllTrim( cFrase ) // Quito espacios sobrantes
    cSep := AllTrim( cSep )

    if Empty( cFrase )
        cFrase := " " // Por defecto es un espacio
    endif

    if Empty( cSep )
        cSep := " " // Por defecto es un espacio
    endif

    cls
    ? "Frase....:", cFrase
    ? "Al reves.:", reverse( cFrase )
    ?

    /* El primer token */
    cToken := strtok( cFrase, cSep )

    /* Bucle mientras haya token */
    while( !Empty( cToken ) )
        ? ++n, "token ->", cToken
        cToken := strtok( nil, cSep )
    end

    ?
    ? "Funciones trigonometricas de", nNum, "experesada en radianes:"
    ? "Coseno.....:", c_Cos( nNum )
    ? "Seno.......:", c_Sin( nNum )
    ? "Tangente...:", c_Tan( nNum )

    ?
    ? "Presione ENTER para seguir..."
    Inkey( 100 )

return
	