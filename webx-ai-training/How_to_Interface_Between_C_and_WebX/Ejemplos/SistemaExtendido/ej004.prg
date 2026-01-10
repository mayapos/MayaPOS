//------------------------------------------------------------------------------
//  Uso de Interface de la funcion de C hecho por nosostros mismos
// ej004.prg
//------------------------------------------------------------------------------

REQUEST HB_CODEPAGE_ESISO

procedure main()

	local cString := "Manuel Expósito Suárez"

    hb_cdpSelect( "ESISO" )

	? "Test con la cadena............: " + cString
	? "Pone en mayuscula las vocales.:", cStrTran( cString, "aeiouáéíóú", "AEIOUÁÉÍÓÚ" )
	? "Quita las vocales.............:", cStrTran( cString, "aeiouáéíóúAEIOUÁÉÍÓÚ", "" )
	? "Quita la tilde.................", cStrTran( cString, "áéíóú", "aeiou" )

      InKey( 100 )

return
