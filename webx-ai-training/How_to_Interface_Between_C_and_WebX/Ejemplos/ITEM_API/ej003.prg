//------------------------------------------------------------------------------
// Ejercicio sobre estructura con el sistema extendido
// Trucos...
// En PRG es un objeto con las mismas datas que miembros de la estructura
// ej003.prg
//------------------------------------------------------------------------------

#include "hbclass.ch"

procedure main

    local persona := TPersona():new( 1 )

    set date format to "dd-mm-yyyy"

    cls

    persona:muestra()
    ?
    ? "Presiona ENTER..."
    Inkey( 100 )

    cls

    persona := TPersona():new( 2 )
    persona:muestra()
    ?
    ? "Presiona ENTER..."
    Inkey( 100 )

    cls

    // En Harbour todas las clases se comportan como las clases estaticas de Java
    // por lo que podriamos hacer esto:
    TPersona():new( 1 ):muestra()
    ?
    ? "Presiona ENTER..."
    Inkey( 100 )

return

//------------------------------------------------------------------------------
// Clase TPersona contenedora de una estructura en C
//------------------------------------------------------------------------------

CREATE CLASS TPersona

    DATA cNIF
	DATA cNombre
	DATA nCodigo
	DATA nSalrio
	DATA dFecha
	DATA lSoltero

    METHOD new( nPersona ) CONSTRUCTOR
    METHOD muestra()

END CLASS

//------------------------------------------------------------------------------
// Constructor

METHOD new( nPersona ) CLASS TPersona

    // Funcion en C que carga las datas desde la estructura de C
    // Deben coincidir las datas y los miembros de la estructura

    dameObjPersona( self, nPersona )

return self

//------------------------------------------------------------------------------
// Muestra por pantalla el contenido del Objeto/Estructura

PROCEDURE muestra() CLASS TPersona

    ? "Datos de la persona del objeto:"
    ? ::cNIF
	? ::cNombre
	? ::nCodigo
	? ::nSalrio
	? ::dFecha
	? ::lSoltero

return