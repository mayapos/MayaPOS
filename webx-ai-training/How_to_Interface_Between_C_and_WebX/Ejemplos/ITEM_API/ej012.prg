//------------------------------------------------------------------------------
// Ejercicio uso de funciones C. Ejecutar funciones PRG desde C
// ej012.prg
//------------------------------------------------------------------------------

procedure main

    local n

    cls

    // Muestra una cadena desde C en un Alert, no recibe parametros
    ejAlertDesdeC00()

    // Muestra una cadena desde C en un Alert, recibe un parametro de tipo cadena "C"
    ejAlertDesdeC01( "ALERT desde C pasando esta cadena" )
    // Mensaje de aviso al comprobar que no se le ha pasado una cadena
    ejAlertDesdeC01( Date() )

    // Muestra una cadena desde C en un Alert, recibe un parametro de cualquier
    // tipo y lo pasa a cadena "C"
    ejAlertDesdeC02( "Hola soy una cadenita" ) // Cadena
    ejAlertDesdeC02( Time() ) // Cadena con formato de tiempo
    ejAlertDesdeC02( Date() ) // Fecha
    ejAlertDesdeC02( 1200 ) // Entero
    ejAlertDesdeC02( 390.25 ) // Numero real
    ejAlertDesdeC02( 1200 + 390.25 ) // Suma de entero y real
    ejAlertDesdeC02( .t. )  // Lógico
    ejAlertDesdeC02() // Sin parametro, sale el mensaje con un aviso

    // Ejecuta una funcion hecha por nosotros mismos o de terceros
    n := ejSumaEnC()
    ? "Valor devuelto por ejSumaEnC", n
    n := ejSumaEnCPar( 10, 34.79)
    ? "Valor devuelto por ejSumaEnCPar -> 10 + 34.79 =", n
    n := ejSumaEnCParPro( 10, 34.79)
    ? "Valor devuelto por ejSumaEnCParPro -> ( 10 + 34.79 ) * 100 =", n
    ? "------------------------------------------------------------------------"
    Inkey( 100 )

return

//------------------------------------------------------------------------------
// Suma dos numeros
//------------------------------------------------------------------------------

function suma( n1, n2 )

    if ValType( n1 ) != 'N'
        n1 := 0
    endif
    if ValType( n2 ) != 'N'
        n2 := 0
    endif

return n1 + n2

//------------------------------------------------------------------------------
