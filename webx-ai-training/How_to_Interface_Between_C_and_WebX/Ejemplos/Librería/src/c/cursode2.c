/******************************************************************************
 ************************** Uso del FileSys API *******************************
 ******************************************************************************/

#include "hbapi.h"    	// Siempre hay que incluir para funciones en C
#include "hbapifs.h"	// Para el Syetm API
#include "hbapiitm.h"	// Para ITEM API

/***
 * Log manager desde C
 * IMPORTANTE: el ultimo argumento tiene que ser NULL
 * Ejemplo: writeLog( "miFic.log, HB_FALSE, "Prueba ", "de ", "LOGMANAGER", NULL );
 * Escribe las cadenas en el fichero miFic.log, si existe lo escribe al final y si no
 * lo crea y escribe.
 */

static const char *nfln;
static int iNflnLen;

/*
 * Para escribir el fichero LOG
 */

void writeLog( const char *szFileName, HB_BOOL bCreate, const char *zStr, ... )
{
	if( szFileName && zStr )	// Si se pasan los parametros
	{
		HB_FHANDLE hFile;
		HB_BOOL bExist = hb_fsFileExists( szFileName );	// Comprueba si existe el archivo

		if( bCreate == HB_TRUE || bExist == HB_FALSE )
		{
			hFile = hb_fsCreate( szFileName, FC_NORMAL ); // Crea el archivo
		}
		else
		{
			hFile = hb_fsOpen( szFileName, FO_READWRITE ); // Abre el archivo
		}

		if( hFile != FS_ERROR )	// Si no hay errores
		{
			va_list vl;
			
			nfln = hb_conNewLine();
			iNflnLen = strlen( nfln );
			
			hb_fsSeekLarge( hFile, 0, FS_END );
			va_start( vl, zStr );

			do	// Recorre los parametros y los escribe en el LOG
			{
				hb_fsWriteLarge( hFile, zStr, strlen( zStr ) ); // Escribe uso esta funcion por si es un bloque mayor de 64K
				hb_fsWrite( hFile, nfln, iNflnLen ); // Escribe fin de linea
			}
			while( ( zStr = va_arg( vl, char * ) ) != NULL );

			va_end( vl );

			hb_fsClose( hFile );	// Cierra archivo. El close hae el commit por lo que no hace falta usar hb_fsCommit()
		}
	}
}

/*
 * writeLog para uso en PRG
 * Solo admite un parametro para escribir pero puede ser de cualquier tipo no solo
 * una cadena
 */

HB_FUNC( WRITELOG )
{
	const char *szFileName = hb_parc( 1 ); // Nombre del archivo
	HB_BOOL bCreate = hb_parldef( 2, HB_FALSE ); // Fuerza la creacion del archivo

	if( szFileName && hb_pcount() > 2 )
	{
		HB_SIZE nLen;
		HB_BOOL bFreeReq;
		char *szStr = hb_itemString( hb_param( 3, HB_IT_ANY ), &nLen, &bFreeReq ); // Convierte la variable pasada a cadena

		writeLog( szFileName, bCreate, szStr, NULL ); // Llama a la funcion en C de escribir al LOG

		if( bFreeReq )
		{
			hb_xfree( szStr );	// Si la funcion hb_itemString() que es necesario liberar memoria se hace
		}
	}
}

/*
 * Para cargar el fichero en una variable
 */

char *loadLog( const char *szFileName, HB_SIZE *nSize )
{
	HB_FHANDLE hFile = hb_fsOpen( szFileName, FO_READ ); // Abre el archivo solo para leer
	char *szValue = NULL;

	if( hFile != FS_ERROR )
	{
		*nSize = hb_fsGetSize( hFile ); 			// Devuelve el tamaño del archivo

		// Crea el bufer con el tamaño del archivo + el salto de linea
		szValue = ( char * ) hb_xgrab( *nSize + iNflnLen );

		hb_fsSeekLarge( hFile, 0, FS_SET );			// Se pone al principio del archivo y
		hb_fsReadLarge( hFile, szValue, *nSize ); 	// Lee todo y lo mete en el bufer
		hb_fsClose( hFile ); 						// Cierra el archivo LOG
	}

	return szValue; // Devuelve el contenido del LOG depositado en esta variable
}

/*
 * Para cargar el fichero en una variable desde PRG
 */

HB_FUNC( LOADLOG )
{
	const char *szFileName = hb_parc( 1 ); // Nombre del archivo LOG

	if( szFileName ) // Nombre del archivo LOG
	{
		HB_SIZE nSize = 0;
		char *szValue = loadLog( szFileName, &nSize );

		hb_retclen_buffer( szValue, nSize ); // Devuelve el contenido del archivo LOG
	}
	else
	{
		hb_retc_null(); // Si no se le pasa archivo LOG devuelve cadena nula
	}
}
