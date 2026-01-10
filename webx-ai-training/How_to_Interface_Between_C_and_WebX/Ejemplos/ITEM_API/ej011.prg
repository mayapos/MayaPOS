//------------------------------------------------------------------------------
// Ejercicio uso de funciones C. Ejemplo de uso de la clase TWABuffer
// ej011.prg
//------------------------------------------------------------------------------

#define B_BOX ( CHR( 218 ) + CHR( 196 ) + CHR( 191 ) + CHR( 179 ) + ;
       CHR( 217 ) + CHR( 196 ) + CHR( 192 ) + CHR( 179 ) + " " )

#define ID_MODIFICA 1
#define ID_ALTA     2

#include "InKey.ch"

//----------------------------------------------------------------------------//

procedure main()

    local oBuf

    set date format to "dd-mm-yyyy"
    set deleted on
    SetMode( 24, 80 )

    cls

    USE test NEW

    if test->( Used() )
        oBuf := TWABuffer():New()   // Crea el Work Area Buffer
        GestBrw( oBuf )
        test->( DBCloseArea() )
    endif

return

//----------------------------------------------------------------------------//

static procedure GestBrw( oBuf )

    local oBrw, oCol
    local nKey := 0
    local n, nFld

    oBrw := TBrowseDb( 1, 0, MaxRow() -1, MaxCol() )

    oBrw:colorSpec := "W+/B, N/BG"
    oBrw:ColSep    := " ³ "
    oBrw:HeadSep   := "ÄÅÄ"
    oBrw:FootSep   := "ÄÁÄ"

    nFld := oBuf:getLen()

    FOR n := 1 TO nFld
        oBrw:AddColumn( TBColumnNew( ( oBuf:getArea() )->( FieldName( n ) ), GenCB( oBuf, n ) ) )
    NEXT

    cls

    @ 0, 0 SAY PadC( "Ojeando la tabla: " + upper( oBuf:getAlias() ), MaxCol() + 1, " " ) COLOR "W+/G+"

    @ MaxRow(),         0 SAY "INSERT"   COLOR "GR+/R+"
    @ MaxRow(), Col() + 1 SAY "Altas"    COLOR "W+/R+"
    @ MaxRow(), Col() + 1 SAY "ENTER"    COLOR "GR+/R+"
    @ MaxRow(), Col() + 1 SAY "Modifica" COLOR "W+/R+"
    @ MaxRow(), Col() + 1 SAY "SUPR"     COLOR "GR+/R+"
    @ MaxRow(), Col() + 1 SAY "Bajas"    COLOR "W+/R+"
    @ MaxRow(), Col() + 1 SAY "F4"       COLOR "GR+/R+"
    @ MaxRow(), Col() + 1 SAY "      "   COLOR "W+/R+"
    @ MaxRow(), Col() + 1 SAY "F5"       COLOR "GR+/R+"
    @ MaxRow(), Col() + 1 SAY "       "  COLOR "W+/R+"
    @ MaxRow(), Col() + 1 SAY "F6"       COLOR "GR+/R+"
    @ MaxRow(), Col() + 1 SAY "       "  COLOR "W+/R+"
    @ MaxRow(), Col() + 1 SAY "ESC"      COLOR "GR+/R+"
    @ MaxRow(), Col() + 1 SAY "Salir"    COLOR "W+/R+"

    while nKey != K_ESC

        oBrw:ForceStable()

        nKey = InKey( 0 )

        do case
            case nKey == K_DOWN;        oBrw:Down()             // Fila siguiente
            case nKey == K_UP;          oBrw:Up()               // Fila anterior
            case nKey == K_LEFT;        oBrw:Left()             // Va a la columna antrior
            case nKey == K_RIGHT;       oBrw:Right()            // Va a la columna siguiente
            case nKey == K_PGDN;        oBrw:pageDown()         // Va a la pagina siguiente
            case nKey == K_PGUP;        oBrw:pageUp()           // Va a la pagina antrior
            case nKey == K_CTRL_PGUP;   oBrw:goTop()            // Va al principio
            case nKey == K_CTRL_PGDN;   oBrw:goBottom()         // Va al final
            case nKey == K_HOME;        oBrw:home()             // Va a la primera columna visible
            case nKey == K_END;         oBrw:end()              // Va a la ultima columna visible
            case nKey == K_CTRL_LEFT;   oBrw:panLeft()          // Va a la primera columna
            case nKey == K_CTRL_RIGHT;  oBrw:panRight()         // Va a la ultima columna
            case nKey == K_CTRL_HOME;   oBrw:panHome()          // Va a la primera página
            case nKey == K_CTRL_END;    oBrw:panEnd()           // Va a la última página
            case nKey == K_DEL;         Borrar( oBuf, oBrw )    // Borra fila
            case nKey == K_INS;         Insertar( oBuf, oBrw )  // Inserta columna
            case nKey == K_ENTER;       Modificar( oBuf, oBrw ) // Modifica columna
        endcase

    end

return

//----------------------------------------------------------------------------//
// Crea los codeblock SETGET de las columnas del browse

static function GenCB( oBuf, n ); return( {|| ( oBuf:getArea() )->( FieldGet( n ) ) } )

//----------------------------------------------------------------------------//
// Pantalla de datos de la tabla

static function PantMuestra( oBuf, nTipo )

    local GetList := {}
    local cTipo, cId, hBuffer

    SET CURSOR ON

    if nTipo == ID_ALTA
        cTipo := "Insertando"
        cId := "nuevo"
        hBuffer := oBuf:Blank()
    else // nTipo == ID_MODIFICA
        cTipo := "Modificando"
        cId := HB_NToS( ( oBuf:getArea() )->( RecNo() ) )
        hBuffer := oBuf:Load()
    endif

    DispBox( 3, 2, 18, 74, B_BOX )

    @ 04, 03 SAY cTipo + " registro en tabla " + oBuf:getAlias() + " - Numero: " + cId

    @ 06, 03 SAY "First....:" GET hBuffer[ "First"    ] PICTURE "@K"
    @ 07, 03 SAY "Last.....:" GET hBuffer[ "Last"     ] PICTURE "@K"
    @ 08, 03 SAY "Street...:" GET hBuffer[ "Street"   ] PICTURE "@K"
    @ 09, 03 SAY "City.....:" GET hBuffer[ "City"     ] PICTURE "@K"
    @ 10, 03 SAY "State....:" GET hBuffer[ "State"    ] PICTURE "@K"
    @ 11, 03 SAY "Zip......:" GET hBuffer[ "Zip"      ] PICTURE "@K"
    @ 12, 03 SAY "Hiredate.:" GET hBuffer[ "Hiredate" ] PICTURE "@K"
    @ 13, 03 SAY "Married..:" GET hBuffer[ "Married"  ] PICTURE "@K"
    @ 14, 03 SAY "Age......:" GET hBuffer[ "Age"      ] PICTURE "@K"
    @ 15, 03 SAY "Salary...:" GET hBuffer[ "Salary"   ] PICTURE "@K"
    @ 16, 03 SAY "Notes:"
    @ 17, 03                  GET hBuffer[ "Notes"    ] PICTURE "@K"

return( GetList )

//----------------------------------------------------------------------------//
// Inserta una fila

static procedure Insertar( oBuf, oBrw )

    local cPant := SaveScreen( 3, 2, 18, 74 )
    local GetList := PantMuestra( oBuf, ID_ALTA )

    READ

    set cursor off

    RestScreen( 3, 2, 18, 74, cPant )

    if LastKey() != K_ESC .and. Updated()
        DBAppend()
        oBuf:save()
        Alert( "Tupla insertada" )
        oBrw:RefreshAll()
    endif

return

//----------------------------------------------------------------------------//
// Modifica la fila actual

static procedure Modificar( oBuf, oBrw )

    local cPant := SaveScreen( 3, 2, 18, 74 )
    local GetList :=  PantMuestra( oBuf, ID_MODIFICA )

    READ

    set cursor off

    RestScreen( 3, 2, 18, 74, cPant )

    if LastKey() != K_ESC .and. Updated()
        oBuf:save()
        Alert( "Tupla Modificada" )
        oBrw:RefreshCurrent()
    endif

return

//----------------------------------------------------------------------------//
// Borra la fila actual

static procedure Borrar( oBuf, oBrw )

    local nRec := ( oBuf:getArea() )->( RecNo() )

    if Alert( "Realmente quieres borrar el registro?", { "Si", "No" } ) == 1
        ( oBuf:getArea() )->( DBDelete() )
        if ( oBuf:getArea() )->( Deleted() )
            Alert( "Borrado..." )
            oBrw:RefreshAll()
        else
            Alert( "No se pudo borrar el registro;" + ;
               "El reistro está bloqueado por otro" )
        endif
    else
        Alert( "No se ha borrado..." )
    endif

return

//----------------------------------------------------------------------------//
// Incluye el fuente donde se define e implementa la clase, esto puede estra en
// una LIB que podemos enlazar con los programas que la usan

#include "thbuffer.prg"

//----------------------------------------------------------------------------//
