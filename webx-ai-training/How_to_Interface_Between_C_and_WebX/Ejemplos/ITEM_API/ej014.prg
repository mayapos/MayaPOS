//------------------------------------------------------------------------------
// Ejercicio uso de codeblock en C. Evalua un codeBlock sin parametros desde C,
// al estilo viejo de Clipper y al nuevo de Harbour.
// ej014.prg
//------------------------------------------------------------------------------

#include "HBClass.ch"

//------------------------------------------------------------------------------

PROCEDURE main

    local bCB0 := { || Alert( "Hola mundo" ) }
    local bCB1 := { | p1, p2 | Alert( "Los parametros pasados: " + HB_ValToStr( p1 ) + " y " + HB_ValToStr( p2 ) ) }
    local bCB2 := { | p1 | Alert( "Directo con un parametro: " + HB_ValToStr( p1 ) ) }

    evalua00( bCB0 )
    evalua01( bCB1, "Primer parametro", Date() )
    // OJO: En Harbour se pueden tratar los CodeBlocks como objetos
    // El objeto es la variable de tipo codeBlock y con el metodo ::eval() se le
    // pasan los parametros y se evalua
    bCB1:eval( "Tratar codeblock como objeto", Time() )
    // Usando el nuevo metodo de Harbour
    evalua02( bCB0 )
    evalua03( bCB1, "Parametro 1", Seconds() )

    Alert( "Funciones directas..." )
    evalua04( bCB0 )
    evalua05( bCB2, "Con parametro directamente" )
    evalua06( bCB1, "Con un parametro...", "otro pametro" )

RETURN

//------------------------------------------------------------------------------
