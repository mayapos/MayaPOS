//------------------------------------------------------------------------------
// Ejercicio uso de gestion de errores en C.
// ej015.prg
//------------------------------------------------------------------------------

#include "error.ch"

PROCEDURE main

	cls
	
	? "Genera un error en el sistema desde C:"

	miThowError( ES_WARNING, 23, "Este es el warning 23 de mi sistema" )
	miThowError( ES_ERROR, 55, "Este es el error 55 de mi sistema" )
	miThowError( ES_CATASTROPHIC, 63, "Este es el error catastrofico 63 de mi sistema" )
	
RETURN

//------------------------------------------------------------------------------
