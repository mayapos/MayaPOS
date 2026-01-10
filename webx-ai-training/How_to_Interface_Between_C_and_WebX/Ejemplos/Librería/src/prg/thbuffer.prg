//------------------------------------------------------------------------------
// Clase para el manejo de un buffer de tipo hash asociado a un WA de DBF
// Cusrso de C
//------------------------------------------------------------------------------

#include "HBClass.ch"

CREATE CLASS TWABuffer

    DATA iData PROTECTED  // Uso interno. Puntero a la estructura en C

    CONSTRUCTOR new()
    METHOD load()
    METHOD save()
    METHOD blank()
    METHOD getBuffer()
    METHOD set( cFieldName, xValue )
    METHOD get( cFieldName )
    METHOD getAlias()
    METHOD getArea()
    METHOD getLen()

   PROTECTED:
    DESTRUCTOR free() // Uso interno. El destructor es invocado automaticamente

END CLASS

// Implementacion de los metodos en C

#pragma BEGINDUMP

#define _IDATA      1   // Posicion de la data iData

#include "hbapi.h"
#include "hbapiitm.h"
#include "hbapirdd.h"
#include "hbstack.h"

/*
 * Estructura contenedora de variables de instancia internas
 */
typedef struct
{
    AREAP pArea;
    PHB_ITEM hBuffer;
    HB_USHORT uiFields;
} DATA, *PDATA;

/*
 * Constructor de la clase
 */
HB_FUNC_STATIC( TWABUFFER_NEW )
{
    PHB_ITEM pSelf = hb_stackSelfItem(); // Recupera el objeto desde el stack
    AREAP pArea = ( AREAP ) hb_rddGetCurrentWorkAreaPointer(); // Puntero al WA actual

    if( pArea ) // Hay WA?
    {
        PDATA pData = ( PDATA ) hb_xgrab( sizeof( DATA ) ); // Reserva memoria para la estructura DATA
        PHB_ITEM hBuffer = hb_hashNew( NULL ); // Crea el hBuffer de los campos
        PHB_ITEM pKey = hb_itemNew( NULL ); // Item para el relleno de las keys con el nombre de los campos
        HB_USHORT uiFields, i;
        char *szFldName = ( char * ) hb_xgrab( pArea->uiMaxFieldNameLength + 1 );  // Reserva memoria para los nombres de los campos

        SELF_FIELDCOUNT( pArea, &uiFields ); // Utilizamos la funcion del rdd para averiguar el numero de campos

        hb_hashPreallocate( hBuffer, uiFields ); // Asignamos la capacidad del hBuffer con el numero de campos

        // Quita sensibilidad a mayusculas/minusculas
        hb_hashClearFlags( hBuffer, HB_HASH_BINARY );
        hb_hashSetFlags( hBuffer, HB_HASH_IGNORECASE | HB_HASH_RESORT );

        // Inicializa el hBuffer, crea pares con la key con el nombre del campo y el value a NULL
        for( i = 1; i <= uiFields; i++ )
        {
            // Obtiene el nombre del campo para asignarlo a la key
            SELF_FIELDNAME( pArea, i, szFldName );
            hb_itemPutC( pKey, szFldName );
            hb_hashAdd( hBuffer, pKey, NULL );
        }

        // Asigna los valores a los dos miembros de la estructura
        pData->pArea = pArea;
        pData->hBuffer = hBuffer;
        pData->uiFields = uiFields;

        // Asigna el puntero del PDATA a IDATA definido en la clase
        hb_arraySetPtr( pSelf, _IDATA, ( void * ) pData );
        // Libera todo lo creado en el método
        hb_itemRelease( pKey );
        hb_xfree( szFldName );
    }

    // El constructor devuelve Self siempre
    hb_itemReturnForward( pSelf );
}

/*
 * Carga el registro en el hBuffer
 */
HB_FUNC_STATIC( TWABUFFER_LOAD )
{
    PHB_ITEM pSelf = hb_stackSelfItem(); // Recupera el objeto desde el stack
    PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto
	PHB_ITEM pValue = hb_itemNew( NULL ); // Crea Item para el valor
	HB_USHORT i;

    // Carga el hBuffer a partir del registro actual
    for( i = 1; i <= pData->uiFields; i++ )
	{
        // Obtiene el valor del campo para asignarlo al value
		SELF_GETVALUE( pData->pArea, i, pValue );
		hb_hashAdd( pData->hBuffer, hb_hashGetKeyAt( pData->hBuffer, i ), pValue );
	}

	hb_itemRelease( pValue ); // Libera todo lo creado en el método

    // Devuelve el buffer
    hb_itemReturn( pData->hBuffer );
}

/*
 * Salva el hBuffer en el registro
 */
HB_FUNC_STATIC( TWABUFFER_SAVE )
{
    PHB_ITEM pSelf = hb_stackSelfItem(); // Recupera el objeto desde el stack
    PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto
	HB_USHORT i;

    // Salva el hBuffer al registro actual
    for( i = 1; i <= pData->uiFields; i++ )
	{
		SELF_PUTVALUE( pData->pArea, i, hb_hashGetValueAt( pData->hBuffer, i ) );
	}
}

/*
 * Limpia el buffer asignando valores vacios del tipo que sea el campo relacionado
 * Para hacer eso se usa el registro fantasma
 */
HB_FUNC_STATIC( TWABUFFER_BLANK )
{
    PHB_ITEM pSelf = hb_stackSelfItem(); // Recupera el objeto desde el stack
    PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto
    PHB_ITEM pRecNo = hb_itemNew( NULL ); // Para guardar el registro actual
    PHB_ITEM pRec0 = hb_itemPutNL( NULL, 0 ); // Para ir al registro fantasma. Recno 0

    SELF_RECID( pData->pArea, pRecNo ); // Guarda el registro actual
    SELF_GOTOID( pData->pArea, pRec0 ); // Va al registro fantasma
    HB_FUNC_EXEC( TWABUFFER_LOAD ); // Ejecuta el metodo load()
    SELF_GOTOID( pData->pArea, pRecNo ); // Vuelve al registro actual

    // Libera todo lo creado en el método
    hb_itemRelease( pRec0 );
    hb_itemRelease( pRecNo );

    // Devuelve el buffer
    hb_itemReturn( pData->hBuffer );
}

/*
 * Devuelve el hBuffer
 */
HB_FUNC_STATIC( TWABUFFER_GETBUFFER )
{
    PHB_ITEM pSelf = hb_stackSelfItem(); // Recupera el objeto desde el stack

    // Obtiene el hBuffer y lo devuelve al prg
    hb_itemReturn( ( ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ) )->hBuffer );
}

/*
 * Devuelve el valor actual del campo especificado en el hBuffer
 */
HB_FUNC_STATIC( TWABUFFER_GET )
{
    PHB_ITEM cKey = hb_param( 1, HB_IT_STRING );
    PHB_ITEM pRes = NULL;

    if( cKey )
    {
        PHB_ITEM pSelf = hb_stackSelfItem(); // Recupera el objeto desde el stack
        PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto

        pRes = hb_hashGetItemPtr( pData->hBuffer, cKey, HB_HASH_AUTOADD_ACCESS ); // Asigna el value de la key pasada
    }

    hb_itemReturn( pRes );
}

/*
 * Asigna el valor del campo especificado en el buffer
 */
HB_FUNC_STATIC( TWABUFFER_SET )
{
    PHB_ITEM pKey = hb_param( 1, HB_IT_STRING ); // Recoge la key
    PHB_ITEM pValue = hb_param( 2, HB_IT_ANY ); // Recoge el value
    HB_BOOL fRes = HB_FALSE;

    if( pKey && pValue ) // Si se hanpasado los dos valores del par key / value
    {
        PHB_ITEM pSelf = hb_stackSelfItem(); // Recupera el objeto desde el stack
        PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto

        fRes = hb_hashScan( pData->hBuffer, pKey, NULL );  // Comprueba que la key es un nombre de campo de la dbf

        if( fRes )
        {
            hb_hashAdd( pData->hBuffer, pKey, pValue ); // Asigna el valor a l value del para con esa key
        }
    }

    // Devuelve valor logico de fRes. Uso para ello el item creado por harbour para la devolución de valores.
    // Mirad el tema del Stack en el libro del alumno
    hb_itemPutL( hb_stackReturnItem(), fRes );
}

/*
 * Obtiene el numero de pares del hBuffer
 */
HB_FUNC_STATIC( TWABUFFER_GETLEN )
{
    PHB_ITEM pSelf = hb_stackSelfItem();  // Recupera el objeto desde el stack
    PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto

    // Devuelve WA. Uso para ello el item creado por harbour para la devolución de valores.
    // Mirad el tema del Stack en el libro del alumno
    hb_itemPutNI( hb_stackReturnItem(), pData->uiFields );
}

/*
 * Obtiene el alias asociado al hBuffer
 */
HB_FUNC_STATIC( TWABUFFER_GETALIAS )
{
    PHB_ITEM pSelf = hb_stackSelfItem();  // Recupera el objeto desde el stack
    PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto
    char *szAlias = ( char * ) hb_xgrab( HB_RDD_MAX_ALIAS_LEN + 1 );

    SELF_ALIAS( pData->pArea, szAlias ); // Obtiene el alias del area del Buffer

    // Devuelve el alias. Uso para ello el item creado por harbour para la devolución de valores.
    // Mirad el tema del Stack en el libro del alumno
    hb_itemPutC( hb_stackReturnItem(), szAlias );

    // Libera todo lo creado en el método
    hb_xfree( szAlias );
}

/*
 * Obtiene el wa asociado al hBuffer
 */
HB_FUNC_STATIC( TWABUFFER_GETAREA )
{
    PHB_ITEM pSelf = hb_stackSelfItem();  // Recupera el objeto desde el stack
    PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto

    // Devuelve WA. Uso para ello el item creado por harbour para la devolución de valores.
    // Mirad el tema del Stack en el libro del alumno
    hb_itemPutNI( hb_stackReturnItem(), pData->pArea->uiArea );
}

/*
 * Destructor de la clase, es llamado automaticamente
 */
HB_FUNC_STATIC( TWABUFFER_FREE )
{
    PHB_ITEM pSelf = hb_stackSelfItem();  // Recupera el objeto desde el stack
    PDATA pData = ( PDATA ) hb_arrayGetPtr( pSelf, _IDATA ); // Recupera la estructura interna desde el objeto

    if( pData )
    {
        // Libera los miembros de la estructura interna creada
        hb_itemRelease( pData->hBuffer );
        hb_xfree( pData );
        hb_arraySetPtr( pSelf, _IDATA, NULL );
    }
}

#pragma ENDDUMP
