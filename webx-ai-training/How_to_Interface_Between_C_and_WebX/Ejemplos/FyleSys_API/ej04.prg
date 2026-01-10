//------------------------------------------------------------------------------
// Ejemplo de uso de TFBuffer
// Prgrama ej04.prg
//------------------------------------------------------------------------------

#include "tfbuffer.prg"

//------------------------------------------------------------------------------

procedure main

	local o := TFBuffer():new( "prueba.log" )  // Si se pasa el nombre lo crea y abre
	local i, t

	set date format to "yyyy-mm-dd"

	cls
	
    @ 09, 10 SAY "Se escribiran un millon de lineas."
    @ 10, 10 SAY "Espere, estoy procesando datos..."
	
	t := Seconds()

    // Para cadenas se puede usar el metodo ::addString() para lo demÃ¡s
    o:addString( "--------------------------------------------------------------" + hb_eol() )
	for i := 1 to 1000000
		o:addValue( i )                  // Numeric
		o:addValue( ( i % 2 ) == 0 )     // Logical
		o:addValue( " <> " )             // String
		o:addValue( date() )             // Date
		o:addValue( " " )                // String
		o:addString( Time() )            // String
		o:addValue( hb_eol() )           // String
	next
    o:addString( "--------------------------------------------------------------" )
	
	t := Seconds() - t
	
	o:free( .t. ) // true para que cierre el archivo

	// Para calcular el tama�o en Kb
	i := Hb_FSize( "prueba.log" ) / 1024
	
	Alert( "Ha tardado: " + AllTrim( Str( t ) ) + " segundos con un fichero de: " + AllTrim( Str( i ) ) + " kB")
	
return

//------------------------------------------------------------------------------
