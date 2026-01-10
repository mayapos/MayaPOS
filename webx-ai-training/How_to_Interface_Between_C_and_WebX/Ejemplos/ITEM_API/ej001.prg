//------------------------------------------------------------------------------
// Ejercicio uso de funciones C
// ej001.prg
//------------------------------------------------------------------------------

REQUEST HB_CODEPAGE_ESISO         // Codigo de pagina en español

procedure main()

    local getlist := {}
    local nYear := Year( Date() )
    local nCubo := 0
    local cNum, i, nDia := 0, cDia
    local cCadena := Space( 60 )
    local cCaracter := " "
    local n1 := 0, n2 := 0, nS, nR, nP, nD
	local nNota := 0, cEstado
	local aNum := { 10, 20, 30 }

    hb_cdpSelect( "ESISO" )

    cls

	separa( .f. )

    @ 02, 01 SAY "Curso de C para Harbour"

    separa( .f. )

    @ 05, 01 SAY "Introduce un año para saber si es bisiesto........:" GET nYear PICTURE "@K 9999"
    @ 06, 01 SAY "Introduce un numero para calcular el cubo.........:" GET nCubo PICTURE "@K 9999"
    @ 07, 01 SAY "Introduce una cadena..............................:"
    @ 08, 10 GET cCadena PICTURE "@K"
    @ 09, 01 SAY "Introduce un caracter para contarlos en la cedena.:" GET cCaracter PICTURE "@K"
    @ 10, 01 SAY "Introduce un numero para tabla de multiplicar.....:" GET n1 PICTURE "@K 99"
    @ 11, 01 SAY "Introduce un numero para hacer calculos...........:" GET n2 PICTURE "@K 99"
    @ 12, 01 SAY "Introduce una nota de calificacion................:" GET nNota PICTURE "@K 99"
    @ 13, 01 SAY "Dame un numero del 1 - 7 para calcular dia semana.:" GET nDia PICTURE "@k 9"

	separa( .f. )

    READ

    cls
	
	separa( .f. )

    // Prueba de llamadas a funciones en C
    ? "El año " + hb_ntoc( nYear )
    if mi_isLeap( nYear )
        ?? " es bisiesto"
    else
        ?? " no es bisiesto"
    endif

    ?
    ? "El año " + HB_NToS( nYear ) + " en romano es " + intToRoman( nYear )

    separa( .f. )

    cNum := HB_NToS( nCubo ) // El numero como cadena

    // No devuelve nada sino que usa la misma variable para depositar el cubo
    mi_cubo( @nCubo )

    ? "El cubo de " + cNum + " es " + hb_ntoc( nCubo )

    separa( .f. )

    cCadena := AllTrim( cCadena )
    n := scanChar( cCadena, cCaracter )
    if n > 0
        ? [En la cadena: "] + cCadena + ["]
        ? "La priemara aparicion del caracter '" + cCaracter + "' esta en la posicion " + HB_NToS( n )
        n := charCount( cCadena, cCaracter )
        ? "y se repite " + HB_NToS( n ) + " veces"
    else
        ? "No hay '" + cCaracter + "' en la cadena: " + cCadena
    endif

    separa( .f. )

    calcula( n1, n2, @nS, @nR, @nP, @nD ) // Ojo: los 4 ultimos pasado por referencia con "@"

    // Ojo: Los parametros de calcula() se pasan por referencia
    ? "Suma.......: " + HB_NToS( n1 ) + " + " + HB_NToS( n2 ) + " = " + HB_NToS( nS )
    ? "Resta......: " + HB_NToS( n1 ) + " - " + HB_NToS( n2 ) + " = " + HB_NToS( nR )
    ? "Producto...: " + HB_NToS( n1 ) + " X " + HB_NToS( n2 ) + " = " + HB_NToS( nP )
    ? "Division...: " + HB_NToS( n1 ) + " / " + HB_NToS( n2 ) + " = " + HB_NToS( nD )
	
    separa( .f. )

	esActo( nNota, @cEstado )
	
	? "Esta usted " + cEstado
	
	separa( .t. )
	
	// Le vamos a añadir 3 elementos al array para comprobar que sumaArray() solo sumas
	// los numericos con o sin decimales
	aAdd( aNum, "Hola" )
	aAdd( aNum, 25.75 )
	aAdd( aNum, 1000 )
	
	cambiaValor( aNum )
	for i := 1 to len( aNum )
		? "Elemento", i, aNum[ i ]
	next
	
	? "La suma de los elementos del array es:", sumaArray( aNum )
	
    separa( .f. )

	? "Tabla de multiplicar del " + HB_NToS( n1 )
	
	aTabla := tabla( n1 )
	
	for i := 1 to len( aTabla )
		? HB_NToS( n1 ) + " X " + HB_NToS( i ) + " = " + HB_NToS( aTabla[ i ] )
	next
	
    separa( .t. )

    cDia := diaSemana( nDia )

    if !Empty( cDia )
        ? "El dia es: " + cDia
    else
        ? "Error en dato introducido: solo numeros del 1 al 7..."
    endif
	
    separa( .t. )

return

// Escribe un separador en la pantalla

static procedure separa( lPara )

    ? Replicate( "-", 70 )

    if ValType( lPara ) == 'L' .and. lPara
        ? "Presiona una tecla para seguir..."
        Inkey( 100 )
    endif

return
