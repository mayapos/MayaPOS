//------------------------------------------------------------------------------
// Clase que gestiona un bufer de fichero
// Hecha casi toda en Lenguaje C

#include "hbclass.ch"

#define FB_MAX_SIZE  			65535

CLASS TFBuffer
	
	DATA hFB  // Uso interno
	
	METHOD new( hFile, nSizeBuffer ) CONSTRUCTOR
	METHOD free() // Libera memoria
	METHOD creaBuffer( hFile, nSizeBuffer )  // Uso interno
	METHOD addString( cString ) // añade cadena al buffer, hace el ::flush() automaticamente
	METHOD addValue( value ) // convierte el valor en cadena y lo añade al buffer
	METHOD flush() // Por si se quiere salvar a disco manualmente
	
END CLASS

//------------------------------------------------------------------------------

METHOD new( xFile, nSizeBuffer ) CLASS TFBuffer

    local hFile
    local nType := ValType( xFile )

	if nType == 'N'	
        hFile := xFile
    elseif nType == 'C'
        hFile := FCreate( xFile )
	else
		Alert( "Falta el nombre o el manejador del fichero" )
	endif		
	
    if hFile > 0
        if ValType( nSizeBuffer ) != 'N' .or. nSizeBuffer < 0
            nSizeBuffer := FB_MAX_SIZE
        endif

        ::creaBuffer( hFile, nSizeBuffer )
    else
        Alert( "No se ha podido usar fichero " )
    endif

return self

//------------------------------------------------------------------------------

#pragma BEGINDUMP

#include "hbapifs.h"
#include "hbapiitm.h"
#include "hbstack.h"

/* Estructura del bufer */
typedef struct
{
	unsigned char *pBuffer;
	unsigned int uiLen;
	unsigned int uiPos;
	HB_FHANDLE hFile;
} FBUFFER, *PFBUFFER;

static void __flushFB( PFBUFFER pFB );

//------------------------------------------------------------------------------
// Metodo para crear la estructura  buffer

HB_FUNC_STATIC( TFBUFFER_CREABUFFER )
{
	PHB_ITEM Self = hb_stackSelfItem();
	PFBUFFER pFB = ( PFBUFFER ) hb_xgrab( sizeof( FBUFFER ) );

	pFB->uiLen = hb_parnint( 2 );
	pFB->pBuffer = ( unsigned char * ) hb_xgrab( pFB->uiLen );
	pFB->uiPos = 0;
	pFB->hFile = ( HB_FHANDLE ) hb_parnint( 1 );

	hb_arraySetPtr( Self, 1, pFB );
}

//------------------------------------------------------------------------------
// Metodo para liberar el buffer

HB_FUNC_STATIC( TFBUFFER_FREE )
{
	PHB_ITEM Self = hb_stackSelfItem();
	PFBUFFER pFB = hb_arrayGetPtr( Self, 1 );

	if( pFB )	
	{
		HB_BOOL fCloseFile = hb_parldef( 1, HB_FALSE );

		__flushFB( pFB );

		if( pFB->pBuffer )
		{
			hb_xfree( pFB->pBuffer );
		}

		if( fCloseFile && pFB->hFile )
		{
			hb_fsClose( pFB->hFile );
		}

		hb_xfree( pFB );
	}
}

//------------------------------------------------------------------------------
// Metodo para añadir cadenas al buffer

HB_FUNC_STATIC( TFBUFFER_ADDSTRING )
{
	PHB_ITEM Self = hb_stackSelfItem();
	PFBUFFER pFB = hb_arrayGetPtr( Self, 1 );
	PHB_ITEM pString = hb_param( 1, HB_IT_STRING  );
	
	if( pString )
	{
		unsigned int uiPos = 0;
		const char *szString = hb_itemGetCPtr( pString );
		unsigned int uiLen = hb_itemGetCLen( pString );

		while( uiPos < uiLen )
		{
			if( pFB->uiPos == pFB->uiLen )
			{
				__flushFB( pFB );
			}
			
			pFB->pBuffer[ pFB->uiPos++ ] = ( unsigned char ) szString[ uiPos++ ];
		}
	}
}

//------------------------------------------------------------------------------
// Metodo para añadir cadenas al buffer

HB_FUNC_STATIC( TFBUFFER_ADDVALUE )
{
	PHB_ITEM Self = hb_stackSelfItem();
	PFBUFFER pFB = hb_arrayGetPtr( Self, 1 );
	PHB_ITEM pValue = hb_param( 1, HB_IT_ANY  );
	
	if( pValue )
	{
		unsigned int uiPos = 0;
		HB_SIZE uiLen;
		HB_BOOL fFree;
		char *szString = hb_itemString( pValue, &uiLen, &fFree );

		while( uiPos < uiLen )
		{
			if( pFB->uiPos == pFB->uiLen )
			{
				__flushFB( pFB );
			}
			
			pFB->pBuffer[ pFB->uiPos++ ] = ( unsigned char ) szString[ uiPos++ ];
		}
		
		if( fFree )
		{
			hb_xfree( szString );
		}
	}
}

//------------------------------------------------------------------------------
// Metodo para forzar escritura en disco del buffer e inicia la posicion

HB_FUNC_STATIC( TFBUFFER_FLUSH )
{
	PHB_ITEM Self = hb_stackSelfItem();
	PFBUFFER pFB = hb_arrayGetPtr( Self, 1 );

	__flushFB( pFB );
}

//------------------------------------------------------------------------------
// Funcion de uso interno. Escribe en disco el buffer e inicia la posicion

static void __flushFB( PFBUFFER pFB )
{
	if( pFB->uiPos > 0 )
	{
		hb_fsWriteLarge( pFB->hFile, pFB->pBuffer, pFB->uiPos );
		pFB->uiPos = 0;
	}
}

//------------------------------------------------------------------------------

#pragma ENDDUMP
