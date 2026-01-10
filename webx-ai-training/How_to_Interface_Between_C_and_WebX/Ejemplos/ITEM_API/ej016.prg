//------------------------------------------------------------------------------
// Ejercicio uso de gestion de errores en C.
// ej016.prg
//------------------------------------------------------------------------------

#include "error.ch"

PROCEDURE main

	cls
	
	? "Genera un error en el sistema desde C:"

	autoErr( ES_WARNING, 2 )
	autoErr( ES_ERROR, 1 )
	autoErr( ES_WHOCARES, 3 )
	
RETURN

//------------------------------------------------------------------------------

procedure autoErr( nNivel, nCodErr )

	local aErr := { "Este es el error 1", ;
                    "Este es el error 2", ;
                    "Este es el error 3"  }
	
	if nCodErr >= 1 .and. nCodErr <= 3
		miThowError( nNivel, nCodErr, aErr[ nCodErr ] )
	endif
	
return