//------------------------------------------------------------------------------
// Ejemplo de uso de TFBuffer
// Prgrama ej03.prg
//------------------------------------------------------------------------------

#include "tfbuffer.prg"

//------------------------------------------------------------------------------

procedure main

	local hFile := FCreate( "prueba.log" )
	local o := TFBuffer():new( hFile )
	local i, t

	set date format to "yyyy-mm-dd"

	cls
	
    @ 09, 10 SAY "Se escribiran un millon de lineas."
    @ 10, 10 SAY "Espere, estoy procesando datos..."
	
	t := Seconds()

    // Para cadenas se puede usar el metodo ::addString() para lo demás
    o:addString( "--------------------------------------------------------------" + hb_eol() )
	for i := 1 to 1000000
		o:addValue( i )                  // Numeric
		o:addValue( ( i % 2 ) == 0 )     // Logical
		o:addString( " <> " )            // String
		o:addValue( date() )             // Date
		o:addValue( " " )                // String
		o:addString( Time() + hb_eol())  // String
	next
    o:addString( "--------------------------------------------------------------" )
	
	t := Seconds() - t
	
	o:free()

	FClose( hFile )

	// Para calcular el tamaño en kB
	i := Hb_FSize( "prueba.log" ) / 1024
	
	Alert( "Ha tardado: " + AllTrim( Str( t ) ) + " segundos con un fichero de: " + AllTrim( Str( i ) ) + " kB")
	
return

//------------------------------------------------------------------------------
