
/******************************************************************************
 ************************** Uso del ITEM API **********************************
 ******************************************************************************/

#include "hbapi.h"    	// Siempre jay que incluir para funciones en C
#include "hbapiitm.h" 	// Para uso del ITEM API
#include "hbdate.h"   	// Para el uso de alguna funcion interna de tratameinto de fechas
#include "hbapirdd.h"	// Trata RDD desde C


/*
 * Asigna valores a parametros pasados por referencia
 */

HB_FUNC( ASIGNAVARC )
{
	PHB_ITEM cVar = hb_param( 1, HB_IT_BYREF );
	PHB_ITEM nVar = hb_param( 2, HB_IT_BYREF );
	PHB_ITEM dVar = hb_param( 3, HB_IT_BYREF );
	PHB_ITEM lVar = hb_param( 4, HB_IT_BYREF );
	PHB_ITEM aVar = hb_param( 5, HB_IT_ARRAY );

	// Cadena
	if( cVar )
	{
		hb_itemPutC( cVar, "Cadena asignada en C" );
	}

	// Numerico
	if( nVar )
	{
		hb_itemPutNI( nVar, 100 );
	}

	// Fecha
	if( dVar )
	{
		hb_itemPutDS( dVar, "20210517" );
	}

	// Logico
	if( lVar )
	{
		hb_itemPutL( lVar, HB_TRUE );
	}

	// Array
	if( aVar )
	{
		hb_itemArrayPut( aVar, 1, cVar );
		hb_itemArrayPut( aVar, 2, nVar );
		hb_itemArrayPut( aVar, 3, dVar );
		hb_itemArrayPut( aVar, 4, lVar );
	}
}

/*
 * Devuelve si un año es bisiesto o no
 */
HB_FUNC( MI_ISLEAP )
{
	// Recibe el parametro 1 como un entero (HB_IT_INTEGER).
	// Si no es del tipo especificado por la mascara nYear sera NULL
	PHB_ITEM nYear = hb_param( 1, HB_IT_INTEGER );
	// Crea el ITEM y asigna .f., Normalmente se usa hb_itemNew()
	//	pero si a las funciones hb_itemPut...() se les pasa en el parametro 1 un NULL
	//crean un nuevo ITEM y le asignan el valor del parametro 2
	PHB_ITEM lRet = hb_itemPutL( NULL, HB_FALSE );

	if( nYear ) // Si no es NULL
	{
		// Obtenemos el valor del ITEM como un entero
		HB_UINT uiYear = hb_itemGetNI( nYear );

		if( uiYear > 0 )
		{
			// Asignamos en el ITEM lRet el valor logico devuelto por la expresion
			hb_itemPutL( lRet, ( ( uiYear % 4 == 0 && uiYear % 100 != 0 ) || uiYear % 400 == 0 ) );
		}
	}

	// Devuelve el ITEM lRet y lo libera para no tener perdida de memoria
	hb_itemReturnRelease( lRet );
}

/*
 * El cubo de un numero pasado por referencia
 */
HB_FUNC( MI_CUBO )
{
	// Recuperamos el parametro pasado como un ITEM para entero de cualquier longitud
	PHB_ITEM nCubo = hb_param( 1, HB_IT_NUMINT );
	// Creamos un ITEM vacio
	PHB_ITEM nRes = hb_itemNew( NULL );

	if( nCubo ) // Si se paso un entero
	{
		// Recupera el entero del ITEM
		HB_MAXINT iCubo = hb_itemGetNInt( nCubo );

		// Asigna el value con el resultado del cubo al ITEM creado
		hb_itemPutNInt( nRes, iCubo * iCubo * iCubo );
	}

	// Devuelve el ITEM con el numero del resultado
	hb_itemReturnRelease( nRes );
}

/*
 * Cuenta las ocurrencias de un caracter dentro de una cadena
 */
HB_FUNC( CHARCOUNT )
{
	// Recuperamos el parametro pasado como ITEM de tipo cadena
	PHB_ITEM cCadena = hb_param( 1, HB_IT_STRING );
	// Crea un ITEM de tipo entero de cualquier longitud
	PHB_ITEM nRes = hb_itemPutNInt( NULL, 0 );

	if( cCadena ) // Si se paso un parametro valido o sea una cadena
	{
		// Recuperamos el segundo parametro como un ITEM cadena
		PHB_ITEM cCarcter = hb_param( 2, HB_IT_STRING );

		if( cCarcter ) // Si se paso un parametro valido
		{
			// Ancho del ITEM cCadena
			HB_SIZE uiLen = hb_itemGetCLen( cCadena );
			HB_SIZE i; // Indice de incremento del for
			HB_SIZE uiContador = 0; // Contador de ocurrencias
			// Obtenemos la primera cadena del ITEM pasado
			const char *szCadena = hb_itemGetC( cCadena );
			// Obtenemos la segunda cadena del ITEM pasado
			const char *szCarcter = hb_itemGetC( cCarcter );

			// Proceso de calculo
			for( i = 0; i < uiLen; i++ )
			{
				if( szCadena[ i ] == szCarcter[ 0 ] )
				{
					++uiContador;
				}
			}

			// Asigna el contador al ITEM que vamos a devolver
			hb_itemPutNInt( nRes, uiContador );
		}
	}

	// Devuelve el ITEM con el numero del resultado
	hb_itemReturnRelease( nRes );
}

/*
 * Busca la primera aparicion de un caracter dentro de una cadena
 */
HB_FUNC( SCANCHAR )
{
	// Recuperamos el parametro pasado como ITEM de tipo cadena
	PHB_ITEM cCadena = hb_param( 1, HB_IT_STRING );
	// Crea un ITEM de tipo entero de cualquier longitud
	PHB_ITEM nRes = hb_itemPutNInt( NULL, 0 );

	if( cCadena ) // Si se paso un parametro valido o sea una cadena
	{
		// Recuperamos el segundo parametro como un ITEM cadena
		PHB_ITEM cCarcter = hb_param( 2, HB_IT_STRING );

		if( cCarcter ) // Si se paso un parametro valido
		{
			// Ancho del ITEM cCadena
			HB_SIZE uiLen = hb_itemGetCLen( cCadena );
			HB_SIZE i; // Indice de incremento del for
			// Obtenemos la primera cadena del ITEM pasado
			const char *szCadena = hb_itemGetC( cCadena );
			// Obtenemos la segunda cadena del ITEM pasado
			const char *szCarcter = hb_itemGetC( cCarcter );

			// Proceso de calculo
			for( i = 0; i < uiLen; i++ )
			{
				if( szCadena[ i ] == szCarcter[ 0 ] )
				{
					// Asigna el contador al ITEM que vamos a devolver
					hb_itemPutNInt( nRes, i + 1 );
					break;
				}
			}
		}
	}

	// Devuelve el ITEM con el numero del resultado
	hb_itemReturnRelease( nRes );

}

/*
 * Uso de parametros por referencia
 * Recibe 2 numeros enteros devuelve la suma, resta, producto y division de los numeros pasados
 */
HB_FUNC( CALCULA )
{
	// Recupera los dos primeros parametros como numeros enteros
	PHB_ITEM nI1 = hb_param( 1, HB_IT_INTEGER );
	PHB_ITEM nI2 = hb_param( 2, HB_IT_INTEGER );

	// Comprueba los datos pasados
	if( nI1 && nI2 )
	{
		// Se recupera el valor de tipo C desde el ITEM
		int i1 = hb_itemGetNI( nI1 );
		int i2 = hb_itemGetNI( nI2 );
		// Recupera el resto de parametros por referencia
		PHB_ITEM nI3 = hb_param( 3, HB_IT_BYREF );
		PHB_ITEM nI4 = hb_param( 4, HB_IT_BYREF );
		PHB_ITEM nI5 = hb_param( 5, HB_IT_BYREF );
		PHB_ITEM nI6 = hb_param( 6, HB_IT_BYREF );
		// Asigna valores a los parametros
		hb_itemPutNInt( nI3, i1 + i2 );
		hb_itemPutNInt( nI4, i1 - i2 );
		hb_itemPutNInt( nI5, i1 * i2 );
		hb_itemPutND( nI6, ( double ) i1 / i2 );
	}
}

/*
 * Comprueba si una nota está aprobada o no y devuelve un literal con el resultado
 * por referencia
 */
HB_FUNC( ESACTO )
{
	PHB_ITEM nNota = hb_param( 1, HB_IT_NUMERIC );
	PHB_ITEM cRes = hb_param( 2, HB_IT_BYREF );

	if( nNota )
	{
		if( hb_itemGetNInt( nNota ) > 4 )
		{
			hb_itemPutC( cRes, "APROBADO" );
		}
		else
		{
			hb_itemPutC( cRes, "SUSPENDIDO" );
		}
	}
	else
	{
		hb_itemPutC( cRes, "NO SE HA PASADO UN DATO CORRECTO" );
	}
}

/*
 * Incrementa en 100 el segundo elemento de un array pasado
 */
HB_FUNC( CAMBIAVALOR )
{
	PHB_ITEM aArray = hb_param( 1, HB_IT_ARRAY );
	PHB_ITEM nVal = hb_itemPutND( NULL, 0.0 );

	if( aArray )
	{
		double dNum = hb_itemGetND( hb_itemArrayGet( aArray, 2 ) );

		hb_itemPutND( nVal, dNum + 100 );
	}

	hb_itemArrayPut( aArray, 2, nVal );
}

/*
 * Pasa un numero entero a numero romano
 */

HB_FUNC( INTTOROMAN )
{
	PHB_ITEM nNum = hb_param( 1, HB_IT_INTEGER ); // Recupera numero entero

	if( nNum ) // Comprobamos si se paso el numero entero
	{
		HB_INT iNumInt = hb_itemGetNI( nNum ); // Recuperamos el valor del item
		char *cNunRoman = ( char * ) hb_xgrab( 1024 ); // Reserva Memoria para el n. romano
		PHB_ITEM cRes = hb_itemNew( NULL );

		cNunRoman[ 0 ] = '\0'; // Pone el fin de cadena al principio. Ahora es una cadena vacia.

		// Procesamos el numero

		while( iNumInt >= 1000 )
		{
			hb_xstrcat( cNunRoman, "M", NULL );
			iNumInt -= 1000;
		}

		if( iNumInt >= 900 )
		{
			hb_xstrcat( cNunRoman, "CM", NULL );
			iNumInt -= 900;
		}

		while( iNumInt >= 500 )
		{
			hb_xstrcat( cNunRoman, "D", NULL );
			iNumInt -= 500;
		}

		if( iNumInt >= 400 )
		{
			hb_xstrcat( cNunRoman, "CD", NULL );
			iNumInt -= 400;
		}

		while( iNumInt >= 100 )
		{
			hb_xstrcat( cNunRoman, "C", NULL );
			iNumInt -= 100;
		}

		if( iNumInt >= 90 )
		{
			hb_xstrcat( cNunRoman, "XC", NULL );
			iNumInt -= 90;
		}

		while( iNumInt >= 50 )
		{
			hb_xstrcat( cNunRoman, "L", NULL );
			iNumInt -= 50;
		}

		if( iNumInt >= 40 )
		{
			hb_xstrcat( cNunRoman, "XL", NULL );
			iNumInt -= 40;
		}

		while( iNumInt >= 10 )
		{
			hb_xstrcat( cNunRoman, "X", NULL );
			iNumInt -= 10;
		}

		if( iNumInt >= 9 )
		{
			hb_xstrcat( cNunRoman, "IX", NULL );
			iNumInt -= 9;
		}

		while( iNumInt >= 5 )
		{
			hb_xstrcat( cNunRoman, "V", NULL );
			iNumInt -= 5;
		}

		if( iNumInt >= 4 )
		{
			hb_xstrcat( cNunRoman, "IV", NULL );
			iNumInt -= 4;
		}

		while( iNumInt > 0 )
		{
			hb_xstrcat( cNunRoman, "I", NULL );
			iNumInt--;
		}

		hb_itemPutC( cRes, cNunRoman ); // Asigna la cadena al item creado
		hb_xfree( cNunRoman ); // Libera la memoria reservada

		hb_itemReturnRelease( cRes ); // Devuelve el n. romano y libera memoria
	}
}

/*
 * Devuelve la suma de los elementos numericos de un array pasado
 */
HB_FUNC( SUMAARRAY )
{

	PHB_ITEM aArray = hb_param( 1, HB_IT_ARRAY );
	double dTotal = 0.0;

	if( aArray )
	{
		HB_SIZE i;
		HB_SIZE nLen = hb_itemSize( aArray ); // Número de elementos
		PHB_ITEM elemento = NULL;

		for( i = 1; i <= nLen; i++ )
		{
			elemento = hb_itemArrayGet( aArray, i );

			switch( hb_itemType( elemento ) )
			{
				case HB_IT_INTEGER :
				case HB_IT_LONG :
					dTotal += hb_itemGetNInt( elemento );
					break;

				case HB_IT_DOUBLE :
					dTotal += hb_itemGetND( elemento );
					break;
					// El resto de tipos no numericos no se consideran
			}
		}
	}

	hb_itemReturnRelease( hb_itemPutND( NULL, dTotal ) );
}

/*
 * Tabla de multiplicar del numero entero pasado
 */
HB_FUNC( TABLA )
{
	PHB_ITEM nNum = hb_param( 1, HB_IT_INTEGER );

	if( nNum )
	{
		HB_UINT i;
		HB_UINT n = 10;
		HB_UINT iNum = hb_itemGetNI( nNum );
		PHB_ITEM aTabla = hb_itemArrayNew( 10 );
		PHB_ITEM nMul = hb_itemNew( NULL );

		for( i = 1; i <= n; i++ )
		{
			hb_itemPutNInt( nMul, iNum * i );

			hb_itemArrayPut( aTabla, i, nMul );
		}

		hb_itemReturnRelease( aTabla );
	}
	else
	{
		hb_ret();
	}
}

/*
 * Dia de la semana
 * Uso de la funcion interna hb_xstrcpy() y de hb_retc_buffer()
 */

HB_FUNC( DIASEMANA )
{
	PHB_ITEM nDia = hb_param( 1, HB_IT_INTEGER );
	PHB_ITEM cRes = hb_itemNew( NULL );

	if( nDia )
	{
		unsigned int uiDia = hb_itemGetNI( nDia ); // Obtiene el entero del ITEM

		if( uiDia >= 1 && uiDia <= 7 ) // Comprueba los topes
		{
			// Aquí se guarda el literal del dia de la semana
			// es una buena prctica iniciar los puntero a NULL
			char *szDia = NULL;

			// La funcion interna hb_xstrcpy reserva memoria si el primer parametro es NULL
			switch( uiDia )
			{
				case 1 :
					szDia = hb_xstrcpy( NULL, "Lunes", NULL );
					break;

				case 2 :
					szDia = hb_xstrcpy( NULL, "Martes", NULL );
					break;

				case 3 :
					szDia = hb_xstrcpy( NULL, "Miercoles", NULL );
					break;

				case 4 :
					szDia = hb_xstrcpy( NULL, "Jueves", NULL );
					break;

				case 5 :
					szDia = hb_xstrcpy( NULL, "Viernes", NULL );
					break;

				case 6 :
					szDia = hb_xstrcpy( NULL, "Sabado", NULL );
					break;

				case 7 :
					szDia = hb_xstrcpy( NULL, "Domingo", NULL );
			}

			hb_itemPutC( cRes, szDia ); // Asigna literal al item para devolverlo
		}
	}

	// Devuelve y libera
	hb_itemReturnRelease( cRes );
}

/*
 * Definicion de Persona como estructura.
 */
typedef struct
{
	char szNIF[ 10 ];
	char szNombre[ 20 ];
	HB_UINT uiCodigo;
	float nSalrio;
	char szFecha[ 9 ];
	HB_BOOL bSoltero;
} TPersona;

/*
 * Funcion que devuelve una estructura como un array
 */
HB_FUNC( DAMEPERSONA )
{
	PHB_ITEM nPersona = hb_param( 1, HB_IT_INTEGER ); // Parametro pasado
	PHB_ITEM aPersona = hb_itemArrayNew( 6 ); // Array que se va a devolver
	PHB_ITEM wItem = hb_itemNew( NULL ); // Iten de trabajo
	TPersona *persona = hb_xgrab( sizeof( TPersona ) ); //Reserva memoria para TPersona

	// Rellena todos los miembros de TPersona según su tipo
	if( hb_itemGetNI( nPersona ) == 1 )
	{
		hb_xstrcpy( persona->szNIF, "53320105T", NULL );
		hb_xstrcpy( persona->szNombre, "Viruete", ", ", "Paco", NULL );
		persona->uiCodigo = 26212;
		persona->nSalrio = 3500.97;
		hb_xstrcpy( persona->szFecha, "19561225", NULL );
		persona->bSoltero = HB_FALSE;
	}
	else
	{
		hb_xstrcpy( persona->szNIF, "43310009H", NULL );
		hb_xstrcpy( persona->szNombre, "Grande", ", ", "Felix", NULL );
		persona->uiCodigo = 13101;
		persona->nSalrio = 2750.75;
		hb_xstrcpy( persona->szFecha, "19660213", NULL );
		persona->bSoltero = HB_TRUE;
	}

	// Rellena el array creado
	hb_itemPutC( wItem, persona->szNIF ); // Cadena
	hb_itemArrayPut( aPersona, 1, wItem );
	hb_itemPutC( wItem, persona->szNombre ); // Cadena
	hb_itemArrayPut( aPersona, 2, wItem );
	hb_itemPutNI( wItem, persona->uiCodigo ); // Entero
	hb_itemArrayPut( aPersona, 3, wItem );
	hb_itemPutND( wItem, persona->nSalrio ); // Real
	hb_itemArrayPut( aPersona, 4, wItem );
	hb_itemPutDS( wItem, persona->szFecha ); // Fecha como cadena
	hb_itemArrayPut( aPersona, 5, wItem );
	hb_itemPutL( wItem, persona->bSoltero ); // Booleano
	hb_itemArrayPut( aPersona, 6, wItem );

	// ATENCION: toda la memoria que hayamos reservado la tenemos que liberar
	hb_xfree( persona );
	hb_itemRelease( wItem );
	// Devuelve el array y lo libera
	hb_itemReturnRelease( aPersona );
}

/*
 * Lo mismo que la anterior pero usando un objeto en vez de un array
 */

HB_FUNC( DAMEOBJPERSONA )
{
	PHB_ITEM oPersona = hb_param( 1, HB_IT_OBJECT ); // Parametro pasado
	PHB_ITEM nPersona = hb_param( 2, HB_IT_INTEGER ); // Parametro pasado
	PHB_ITEM wItem = hb_itemNew( NULL ); // Iten de trabajo
	TPersona *persona = hb_xgrab( sizeof( TPersona ) ); //Reserva memoria para TPersona

	// Rellena todos los miembros de TPersona según su tipo
	if( hb_itemGetNI( nPersona ) == 1 )
	{
		hb_xstrcpy( persona->szNIF, "53320105T", NULL );
		hb_xstrcpy( persona->szNombre, "Viruete", ", ", "Paco", NULL );
		persona->uiCodigo = 26212;
		persona->nSalrio = 3500.97;
		hb_xstrcpy( persona->szFecha, "19561225", NULL );
		persona->bSoltero = HB_FALSE;
	}
	else
	{
		hb_xstrcpy( persona->szNIF, "43310009H", NULL );
		hb_xstrcpy( persona->szNombre, "Grande", ", ", "Felix", NULL );
		persona->uiCodigo = 13101;
		persona->nSalrio = 2750.75;
		hb_xstrcpy( persona->szFecha, "19660213", NULL );
		persona->bSoltero = HB_TRUE;
	}

	// Rellena el array creado
	hb_itemPutC( wItem, persona->szNIF ); // Cadena
	hb_itemArrayPut( oPersona, 1, wItem );
	hb_itemPutC( wItem, persona->szNombre ); // Cadena
	hb_itemArrayPut( oPersona, 2, wItem );
	hb_itemPutNI( wItem, persona->uiCodigo ); // Entero
	hb_itemArrayPut( oPersona, 3, wItem );
	hb_itemPutND( wItem, persona->nSalrio ); // Real
	hb_itemArrayPut( oPersona, 4, wItem );
	hb_itemPutDS( wItem, persona->szFecha ); // Fecha como cadena
	hb_itemArrayPut( oPersona, 5, wItem );
	hb_itemPutL( wItem, persona->bSoltero ); // Booleano
	hb_itemArrayPut( oPersona, 6, wItem );

	// ATENCION: toda la memoria que hayamos reservado la tenemos que liberar
	hb_xfree( persona );
	hb_itemRelease( wItem );
}


/*
 * Da la vuenta a una cadena pasada
 */

HB_FUNC( REVERSE )
{
	PHB_ITEM cInString = hb_param( 1, HB_IT_STRING );
	PHB_ITEM cRes = hb_itemNew( NULL );

	if( cInString )
	{
		const char *szInString = hb_itemGetC( cInString );
		int iLen = hb_itemSize( cInString );
		char *szRetStr = hb_xgrab( iLen );
		int i;

		for( i = 0; i < iLen; i++ )
		{
			szRetStr[ i ] = szInString[ iLen - i - 1 ];
		}

		hb_itemPutCL( cRes, szRetStr, iLen );
	}

	hb_itemReturnRelease( cRes );

}
/*
 * Usando interfaces a funciones de C hechas por nosotros mismos
 */

char *cstrtran( const char *cString, HB_SIZE nLenStr, const char *cFind, HB_SIZE nLenFind,
				const char *cReplace, HB_SIZE nLenRep )
{
	HB_SIZE i, n, w = 0;
	HB_BOOL fFind = HB_FALSE;
	char *cRet = ( char * ) hb_xgrab( nLenStr + 1 );

	for( i = 0; i < nLenStr; i++ )
	{
		for( n = 0; n < nLenFind; n++ )
		{
			fFind = cFind[ n ] == cString[ i ];

			if( fFind )
			{
				if( n < nLenRep )
				{
					cRet[ w ] = cReplace[ n ];
					w++;
				}

				break;
			}
		}

		if( !fFind )
		{
			cRet[ w ] = cString[ i ];
			w++;
		}
	}

	cRet[ w ] = '\0';

	return( cRet );
}

/*
 * Esta es la funcion interfaz entre cstrtran() en C puro y el PRG
 */
HB_FUNC( CSTRTRAN )
{
	PHB_ITEM cString = hb_param( 1, HB_IT_STRING );
	PHB_ITEM cFind = hb_param( 2, HB_IT_STRING );
	PHB_ITEM cReplace = hb_param( 3, HB_IT_STRING );

	PHB_ITEM cRes = hb_itemPutC( NULL, "" );

	if( cString && cFind && cReplace )
	{
		hb_itemPutC( cRes, cstrtran( hb_itemGetC( cString ), hb_itemGetCLen( cString ),
									 hb_itemGetC( cFind ), hb_itemGetCLen( cFind ),
									 hb_itemGetC( cReplace ), hb_itemGetCLen( cReplace ) ) );
	}

	hb_itemReturnRelease( cRes );
}

/*
 * Usando interfaces a funciones de C
 */

HB_FUNC( STRTOK )
{
	PHB_ITEM p = hb_param( 1, HB_IT_STRING );
	PHB_ITEM s = hb_param( 2, HB_IT_STRING );
	PHB_ITEM cRes = hb_itemNew( NULL );

	if( s ) // Si hay separador
	{
		hb_itemPutC( cRes, strtok( hb_itemGetC( p ), hb_itemGetC( s ) ) );
	}

	hb_itemReturnRelease( cRes );
}

/*
 * Interfaces con funciones matematicas de C
 */
#include <math.h>
/* coseno */
HB_FUNC( C_COS )
{
	PHB_ITEM nRes = hb_itemNew( NULL );
	PHB_ITEM nPar = hb_param( 1, HB_IT_NUMERIC );

	if( nPar )
	{
		hb_itemPutND( nRes, cos( hb_itemGetND( nPar ) ) );
	}

	hb_itemReturnRelease( nRes );
}
/* seno */
HB_FUNC( C_SIN )
{
	PHB_ITEM nRes = hb_itemNew( NULL );
	PHB_ITEM nPar = hb_param( 1, HB_IT_NUMERIC );

	if( nPar )
	{
		hb_itemPutND( nRes, sin( hb_itemGetND( nPar ) ) );
	}

	hb_itemReturnRelease( nRes );
}
/* tangente */
HB_FUNC( C_TAN )
{
	PHB_ITEM nRes = hb_itemNew( NULL );
	PHB_ITEM nPar = hb_param( 1, HB_IT_NUMERIC );

	if( nPar )
	{
		hb_itemPutND( nRes, tan( hb_itemGetND( nPar ) ) );
	}

	hb_itemReturnRelease( nRes );
}

/***
 * Funciones con el nuevo API de tratamiento de arrays de Harbour
 ***/

/*
 * Funcion que recibe un array de numeros y los incrementa con
 * el valor numerico pasado como segundo parametro.
 */

HB_FUNC( TRAMITA )
{
	PHB_ITEM aDatos = hb_param( 1, HB_IT_ARRAY );

	if( aDatos )
	{
		PHB_ITEM nMod = hb_param( 2, HB_IT_NUMERIC );

		if( nMod )
		{
			HB_SIZE nLen = hb_arrayLen( aDatos );
			HB_SIZE i;
			double dMod = hb_itemGetND( nMod );

			for( i = 1; i <= nLen; i++ )
			{
				hb_arraySetND( aDatos, i, hb_arrayGetND( aDatos, i ) + dMod );
			}
		}
	}
}

/*
 * Crea un array
 */

HB_FUNC( CREAARRAY )
{
	PHB_ITEM aArray = hb_itemNew( NULL ); //Crea un ITEM vacio
	PHB_ITEM xItem = hb_itemNew( NULL );

	// Convertimo el ITEM creado como un array de 10 elementos. Se podia haber
	// usado aArray = hb_itemArrayNew( 10 ) que hace los dos pasos a la vez
	hb_arrayNew( aArray, 10 );

	hb_arraySetDS( aArray, 1, "20211231" );
	// La funcion hb_arraySetDL necesita la fecha juliana. Para convertir la como
	// cadena a juliana usamos la función interna hb_dateEncStr
	hb_arraySetDL( aArray, 2, hb_dateEncStr( "20211231" ) );
	hb_arraySetL( aArray, 3, HB_FALSE );
	hb_arraySetNI( aArray, 4, 35789 );
	hb_arraySetNL( aArray, 5, 15578952 );
	hb_arraySetNInt( aArray, 6, 95415545541 );
	hb_arraySetND( aArray, 7, 34954155455.41 );
	hb_arraySetC( aArray, 8, "Esto es una prueba de cadena" );
	hb_arraySet( aArray, 9, xItem ); // xItem sin asignar
	// Asignamos un valor al item creado xItem y lo metemos en el array
	hb_itemPutC( xItem, "Asignacion del item con valor tipo cadena" );
	hb_arraySet( aArray, 10, xItem );

	hb_itemRelease( xItem ); 			// Destruye el item creado

	hb_itemReturnRelease( aArray ); 	// Devuelve el array y destruye el item
}

/*
 * Funciones Gather y Scatter para array
 */

/*
 * Crea el array y lo devuelve relleno con el registro actual
 */
HB_FUNC( AGATHER )
{
	PHB_ITEM aBuffer = hb_itemNew( NULL );
	PHB_ITEM pValue = hb_itemNew( NULL );
	AREAP pArea = ( AREAP ) hb_rddGetCurrentWorkAreaPointer();
	HB_USHORT uiFields, i;

	// Cuenta el numero de campos de la dbf
	SELF_FIELDCOUNT( pArea, &uiFields );

	hb_arrayNew( aBuffer, uiFields );

	// Relleno el aBuffer con los datos del registro
	for( i = 1; i <= uiFields; i++ )
	{
		SELF_GETVALUE( pArea, i, pValue );
		hb_arraySet( aBuffer, i, pValue );
	}

	// Libero todo lo que he creado
	hb_itemRelease( pValue );

	// Devuelvo y libero el aBuffer relleno
	hb_itemReturnRelease( aBuffer );
}

/*
 * Salva el array en el registro actual
 */
HB_FUNC( ASCATTER )
{
	PHB_ITEM aBuffer = hb_param( 1, HB_IT_ARRAY );

	if( aBuffer )
	{
		AREAP pArea = ( AREAP ) hb_rddGetCurrentWorkAreaPointer();
		HB_USHORT uiFields, i;
		PHB_ITEM pValue = hb_itemNew( NULL );

		SELF_FIELDCOUNT( pArea, &uiFields );

		for( i = 1; i <= uiFields; i++ )
		{
			hb_arrayGet( aBuffer, i, pValue );
			SELF_PUTVALUE( pArea, i, pValue );
		}

		// Libero todo lo que he creado
		hb_itemRelease( pValue );
	}
}

/*
 * Crea un hash en C
 */

HB_FUNC( CREAHASH )
{
	PHB_ITEM hHash = hb_hashNew( NULL ); //Crea un ITEM vacio como hash
	PHB_ITEM pKey = hb_itemNew( NULL ); // Como cargo para usarlo como key
	PHB_ITEM pValue = hb_itemNew( NULL ); // Como cargo para usarlo como value

	// Fechas
	hb_itemPutC( pKey, "fechaDS" );	// Fecha como cadena. Esta es la key
	hb_itemPutDS( pValue, "20211231" );
	hb_hashAdd( hHash, pKey, pValue ); // Añadimo el par al hash
	//---
	hb_itemPutC( pKey, "fechaDL" );	// Fecha como cadena. Esta es la key
	hb_itemPutDL( pValue, hb_dateEncStr( "20211231" ) );
	hb_hashAdd( hHash, pKey, pValue ); // Añadimo el par al hash
	// Logicos
	hb_itemPutC( pKey, "logico" );
	hb_itemPutL( pValue, HB_TRUE );
	hb_hashAdd( hHash, pKey, pValue );
	// Enteros
	hb_itemPutC( pKey, "entero" );
	hb_itemPutNI( pValue, 35789 );	// Entero
	hb_hashAdd( hHash, pKey, pValue );
	//---
	hb_itemPutC( pKey, "largo" );
	hb_itemPutNL( pValue, 15578952 );	// Entero largo
	hb_hashAdd( hHash, pKey, pValue );
	// Real
	hb_itemPutC( pKey, "real" );
	hb_itemPutND( pValue, 34954155455.41 );	// Doble o real
	hb_hashAdd( hHash, pKey, pValue );

	hb_itemRelease( pKey ); 			// Destruye el item creado para la key
	hb_itemRelease( pValue ); 			// Destruye el item creado para el value

	hb_itemReturnRelease( hHash ); 	// Devuelve el hash y destruye el item
}

/*
 * Funciones Gather y Scatter para Hash
 */

/*
 * Crea el Hash y lo devuelve relleno con el registro actual
 */
HB_FUNC( HGATHER )
{
	PHB_ITEM hBuffer = hb_hashNew( NULL );
	PHB_ITEM pKey = hb_itemNew( NULL );
	PHB_ITEM pValue = hb_itemNew( NULL );
	AREAP pArea = ( AREAP ) hb_rddGetCurrentWorkAreaPointer();
	char *szFldName = ( char * ) hb_xgrab( pArea->uiMaxFieldNameLength + 1 );
	HB_USHORT uiFields, i;

	// Quita sensibilidad a mayusculas/minusculas
	hb_hashClearFlags( hBuffer, HB_HASH_BINARY );
	hb_hashSetFlags( hBuffer, HB_HASH_IGNORECASE | HB_HASH_RESORT );

	// Cuenta el numero de campos de la dbf
	SELF_FIELDCOUNT( pArea, &uiFields );

	// Reservo la capacidad del hBuffer
	hb_hashPreallocate( hBuffer, uiFields );

	// Relleno el hBuffer con los datos del registro
	for( i = 1; i <= uiFields; i++ )
	{
		SELF_FIELDNAME( pArea, i, szFldName );
		hb_itemPutC( pKey, szFldName );
		SELF_GETVALUE( pArea, i, pValue );
		hb_hashAdd( hBuffer, pKey, pValue );
	}

	// Libero todo lo que he creado
	hb_itemRelease( pKey );
	hb_itemRelease( pValue );
	hb_xfree( szFldName );

	// Devuelvo y libero el hBuffer relleno
	hb_itemReturnRelease( hBuffer );
}

/*
 * Salva el Hash en el registro actual
 */
HB_FUNC( HSCATTER )
{
	PHB_ITEM hBuffer = hb_param( 1, HB_IT_HASH );

	if( hBuffer )
	{
		AREAP pArea = ( AREAP ) hb_rddGetCurrentWorkAreaPointer();
		HB_USHORT uiFields, i;

		SELF_FIELDCOUNT( pArea, &uiFields );

		for( i = 1; i <= uiFields; i++ )
		{
			SELF_PUTVALUE( pArea, i, hb_hashGetValueAt( hBuffer, i ) );
		}
	}
}

/*
 * Ejecutar funciones PRG desde C
 */

#include "hbvm.h" // Necesario para invocar a la maquina virtual y usar sus funciones
#include "hbstack.h" // Para el manejo de la pila

/*
 * Llama a la funcion ALERT desde C.
 * Asignamos una cadena también desde C
 */
HB_FUNC( EJALERTDESDEC00 )
{
	// Busca el simbolo ALERT en la tabla dinamica de simbolos
	// La funcion hb_dynsymFind busca el simbolo a partir del nombre teniendo
	// en cuenta mayusculas y ninusculas, si no lo encuenta devuelve NULL por lo
	// que habría que controlar eso. En este caso no lo hago porque se trata de
	// una funcion de Harbour que siempre va a existir.
	PHB_DYNS pExecSym = hb_dynsymFind( "ALERT" );

	hb_vmPushDynSym( pExecSym ); // Pone el simbolo de la función en la pila
	// IMPORTANTE. La primera posicion en la pila despues del simbolo de la funcion
	// siempre será un NULL para las funciones y procedimeintos o SELF para los
	// metodos de los clases
	hb_vmPushNil(); // Pone NULL
	// Pone una cadena como cadena de C. Hay que pasar el tamaño de la cadena
	hb_vmPushString( "Hola, esto es un ALERT desde C", 30 );
	// Esta funcion invoca a la Maquina Virtual de Harbour (VM) para ejecutar
	// la funcion. Hay que indicar el numero de parametros.
	hb_vmDo( 1 );
}

/*
 * Llama a la funcion ALERT desde C.
 * Pasmos una cadena desde PRG y controla que sea una cadena
 */
HB_FUNC( EJALERTDESDEC01 )
{
	PHB_DYNS pExecSym = hb_dynsymFind( "ALERT" );
	PHB_ITEM cItem = hb_param( 1, HB_IT_STRING );

	hb_vmPushDynSym( pExecSym );
	hb_vmPushNil();

	// Controla que sea del tipo esperado en hb_param() o sea una cadena
	// HB_IT_STRING (Item Tipe String)
	if( cItem )
	{
		hb_vmPush( cItem ); // Pone el parametro como un ITEM
	}
	else // Si no se ha pasado un Item de tipo "C"
	{
		// Pone una cadena como cadena de C. Hay que pasar el tamaño de la cadena
		hb_vmPushString( "ATENCION;No se ha pasado una cadena", 35 );
	}

	// Invoca a la MV para ejecutar lo que hay en la pila
	// Se puede usar una de las dos funciones
	//hb_vmDo( 1 );
	hb_vmProc( 1 );
}

/*
 * Llama a la funcion ALERT desde C.
 * Pasmos cualquier valor y tipo desde PRG y controla que se ha pasado algo
 */
HB_FUNC( EJALERTDESDEC02 )
{
	PHB_DYNS pExecSym = hb_dynsymFind( "ALERT" );
	PHB_ITEM xItem = hb_param( 1, HB_IT_ANY );

	hb_vmPushDynSym( pExecSym );
	hb_vmPushNil();

	if( xItem )
	{
		// La funcion hb_itemValToStr() crea un nuevo item de tipo caracter
		// a partir del item de cualquier tipo que le hayamos pasado, por lo 
		// que hay que destruirlo una vez usado.
		PHB_ITEM cItem = hb_itemValToStr( xItem );
		
		hb_vmPush( cItem );
		hb_itemRelease( cItem );
	}
	else
	{
		hb_vmPushString( "ATENCION;No se ha pasado ningun valor", 37 );
	}
	// Se puede usar una de las dos funciones
	//hb_vmDo( 1 );
	hb_vmProc( 1 );
}

/*
 * Llama a la funcion Suma hecha en PRG desde C.
 * Los numero los metemos desde C
 */
HB_FUNC( EJSUMAENC )
{
	// hb_dynsymFind() es case sensitive, Harbour pone todos los símbolos creados
	// desde PRG en mayúscula pero respeta mayúsculas y minúsculas, pero si el nombre
	// que le vamos a pasar parámetro no se sabe si está en mayúscula o minúscula se
	// puede usar hb_dynsymFindName() que lo pasa a mayúsculas antes de buscar.
	PHB_DYNS pExecSym = hb_dynsymFind( "SUMA" );
	
	// Cuando no hay una seguridad de que exista el simbolo hay que comprobarlo
	if( pExecSym )
	{
		hb_vmPushDynSym( pExecSym );
		hb_vmPushNil();
		hb_vmPushInteger( 1500 );
		hb_vmPushDouble( 250.35, 2 );		
		// Se puede usar una de las dos funciones
		//hb_vmDo( 2 ); 
		hb_vmProc( 2 );
	}
}

/*
 * Llama a la funcion Suma hecha en PRG desde C.
 * Los numero los pasamos desde PRG
 */
HB_FUNC( EJSUMAENCPAR )
{
	PHB_DYNS pExecSym = hb_dynsymFind( "SUMA" );
	
	// Cuando no hay una seguridad de que exista el simbolo hay que comprobarlo
	if( pExecSym )
	{
		// Los dos parametros
		PHB_ITEM n1 = hb_param( 1, HB_IT_NUMERIC );
		PHB_ITEM n2 = hb_param( 2, HB_IT_NUMERIC );
		
		hb_vmPushDynSym( pExecSym );
		hb_vmPushNil();
		hb_vmPush( n1 );
		hb_vmPush( n2 );		
		//hb_vmDo( 2 ); // Se puede usar una de las dos funciones
		hb_vmProc( 2 );
	}
}

/*
 * Llama a la funcion Suma hecha en PRG desde C y procesa el resultado en C. En
 * este caso multiplicamos por 100 y devuelve el resultado
 * Los 2 numero los pasamos desde PRG
 */
HB_FUNC( EJSUMAENCPARPRO )
{
	PHB_DYNS pExecSym = hb_dynsymFind( "SUMA" );
	
	// Cuando no hay una seguridad de que exista el simbolo hay que comprobarlo
	if( pExecSym )
	{
		double dNum, dRes;
		// Los dos parametros
		PHB_ITEM n1 = hb_param( 1, HB_IT_NUMERIC );
		PHB_ITEM n2 = hb_param( 2, HB_IT_NUMERIC );
		
		hb_vmPushDynSym( pExecSym );
		hb_vmPushNil();
		hb_vmPush( n1 );
		hb_vmPush( n2 );		
		//hb_vmDo( 2 ); 
		hb_vmProc( 2 ); // El resultado lo pone en la pila en el item de devolucion
		
		// El item de devolucion se rescata con la funcion hb_stackReturnItem()
		// Saca el numero como tipo en C double para procesarlo
		dNum = hb_itemGetND( hb_stackReturnItem() ); // Saca el numero como tipo en C
		// Hace el procesamiento, en este caso multiplica por 100
		dRes = dNum * 100;
		// Resultado se pone en la pila en el item de devolucion
		hb_itemPutND( hb_stackReturnItem(), dRes ); 
	}
}

/*
 * Ejemplo de ejacucion de metodos desde C
 * Toma los datos directamente desde C con variables de tipo C
 */
 
HB_FUNC( CAMBIADATOSENC )
{
	PHB_ITEM pObj = hb_param( 1, HB_IT_OBJECT );
	
	if( pObj )
	{                   
		PHB_DYNS pMsgSym = hb_dynsymGetCase( "CAMBIADATOS" );		
		
		hb_vmPushDynSym( pMsgSym ); // Pone el metodo en la pila
		hb_vmPush( pObj ); // Esto es super importante, poner el objeto en primer lugar
		hb_vmPushString( "Isabel", 6 );
		hb_vmPushString( "Guerrero", 8 );
		hb_vmPushInteger( 52 );
		hb_vmPushDouble( 2500.75, 2 );
		hb_vmSend( 4 );
	}
}

/*
 * Ejemplo de ejacucion de metodos desde C
 * Toma los datos pasados desde PRG con Item
 */
 
HB_FUNC( CAMBIADATOSENCPAR )
{
	PHB_ITEM pObj = hb_param( 1, HB_IT_OBJECT );
	
	if( pObj )
	{                
		PHB_ITEM cNombre = hb_param( 2, HB_IT_STRING );
		PHB_ITEM cApellido = hb_param( 3, HB_IT_STRING );
		PHB_ITEM nEdad = hb_param( 4, HB_IT_NUMINT );
		PHB_ITEM nSueldo = hb_param( 5, HB_IT_DOUBLE );
		PHB_DYNS pMsgSym = hb_dynsymGetCase( "CAMBIADATOS" );		
		
		hb_vmPushDynSym( pMsgSym ); // Pone el metodo en la pila
		hb_vmPush( pObj ); // Esto es super importante, poner el objeto en primer lugar
		hb_vmPush( cNombre );
		hb_vmPush( cApellido );
		hb_vmPush( nEdad );
		hb_vmPush( nSueldo );
		hb_vmSend( 4 );
	}
}

/*
 * Evalua un codeBlock pasado desde C.
 * Es la manera de hacerlo con la vieja propuesta de Clipper.
 * Sin parametros
 */
HB_FUNC( EVALUA00 )
{
	PHB_ITEM pCB = hb_param( 1, HB_IT_BLOCK ); // El codeblock pasado
	
	if( pCB ) // Si se paso un CB
	{
		HB_EVALINFO EvalInfo; // Estructura HB_EVALINFO 
		
		// Inicializa la estructura HB_EVALINFO (es un puntero (&))
		if( hb_evalNew( &EvalInfo, pCB ) )
		{
			hb_evalLaunch( &EvalInfo ); // Evalua el CB
		}
		
		hb_evalRelease( &EvalInfo ); // Libera la memoria interna de la estructura
	}
}

/*
 * Evalua un codeBlock pasado desde C.
 * Es la manera de hacerlo con la vieja propuesta de Clipper.
 * Con parametros
 */
HB_FUNC( EVALUA01 )
{
	PHB_ITEM pCB = hb_param( 1, HB_IT_BLOCK ); // El codeblock pasado
	
	if( pCB ) // Si se paso un CB
	{		
		HB_EVALINFO EvalInfo; // Estructura HB_EVALINFO
		
		// Inicializa la estructura HB_EVALINFO
		if( hb_evalNew( &EvalInfo, pCB ) )
		{
			// Ojo usar hb_itemParam() que es una copia del parametro pasado. 
			// No el propio parametro ya que hb_evalRelease libera esas copias de los item pasados.
			hb_evalPutParam( &EvalInfo, hb_itemParam( 2 ) ); // Añade primer parametro. 
			hb_evalPutParam( &EvalInfo, hb_itemParam( 3 ) ); // Añade segundo parametro
			
			hb_evalLaunch( &EvalInfo ); // Evalua el CB con los parametros pasados.
		}
		
		hb_evalRelease( &EvalInfo ); // Libera la memoria interna de la estructura
	}
}

/*
 * Evalua un codeBlock pasado desde C.
 * Es la manera de hacerlo con la nueva propuesta de Harbour.
 * Funciona exactamente como hemos visto con los metodos de los objetos
 * Este es el mismo ejemplo que el de la funcion EVALUA00 visto anteriormente
 */
HB_FUNC( EVALUA02 )
{
	PHB_ITEM pCB = hb_param( 1, HB_IT_BLOCK ); // El codeblock pasado

	if( pCB )
	{
		hb_vmPushEvalSym();	// Pone el simbolo de la funcion eval() en la pila
		hb_vmPush( pCB ); 	// Pone el codeblock en la pila similar al objeto
		hb_vmSend( 0 ); 	// Ejecuta sin parametros. Como si fuera un objeto
	}
}

/*
 * Evalua un codeBlock pasado desde C.
 * Es la manera de hacerlo con la nueva propuesta de Harbour.
 * Funciona exactamente como hemos visto con los metodos de los objetos
 * Este es el mismo ejemplo que el de la funcion EVALUA00 visto anteriormente
 */
HB_FUNC( EVALUA03 )
{
	PHB_ITEM pCB = hb_param( 1, HB_IT_BLOCK ); // El codeblock pasado

	if( pCB )
	{
		hb_vmPushEvalSym();	// Pone el simbolo de la funcion eval() en la pila
		hb_vmPush( pCB ); 	// Pone el codeblock en la pila similar al objeto
		hb_vmPush( hb_param( 2, HB_IT_ANY ) );
		hb_vmPush( hb_param( 3, HB_IT_ANY ) );
		hb_vmSend( 2 ); 	// Ejecuta con dos parametros. Como si fuera un objeto
	}
}

/*
 * Evalua un codeBlock pasado desde C.
 * Funcion para evaluar un CB sin parametros directamente.
 */
HB_FUNC( EVALUA04 )
{
	PHB_ITEM pCB = hb_param( 1, HB_IT_BLOCK ); // El codeblock pasado

	if( pCB )
	{
		hb_evalBlock0( pCB ); 	
	}
}

/*
 * Evalua un codeBlock pasado desde C.
 * Funcion para evaluar un CB con un parametro directamente.
 */
HB_FUNC( EVALUA05 )
{
	PHB_ITEM pCB = hb_param( 1, HB_IT_BLOCK ); // El codeblock pasado

	if( pCB )
	{
		hb_evalBlock1( pCB, hb_param( 2, HB_IT_ANY ) ); 	
	}
}

/*
 * Evalua un codeBlock pasado desde C.
 * Funcion para evaluar un CB con parametros directamente.
 */
HB_FUNC( EVALUA06 )
{
	PHB_ITEM pCB = hb_param( 1, HB_IT_BLOCK ); // El codeblock pasado

	if( pCB )
	{
		hb_evalBlock( pCB, hb_param( 2, HB_IT_ANY ), hb_param( 3, HB_IT_ANY ), NULL ); 	
	}
}

//=============================================================================
// ErrorSystem API
//=============================================================================

#include "hbapierr.h"

HB_FUNC( MITHOWERROR ) // ( HB_USHORT uiLevel, HDO_ERRCODE errCode, const char *szDesc )
{
	PHB_ITEM pError = hb_errNew();
	HB_USHORT uiLevel = hb_parnidef( 1, ES_WARNING );
	HB_ERRCODE errCode = hb_parnidef( 2, 0 );
	const char *szMsg = hb_parc( 3 );

	hb_errPutSubSystem( pError, "Curso de C (Subsistema)" ); // Nombre de subsistema
	hb_errPutSubCode( pError, errCode ); // Código del error en nuestro sistema
	hb_errPutDescription( pError, szMsg ); // Mensage
	hb_errPutSeverity( pError, uiLevel ); // Nivel del error

	hb_errPutFlags( pError, EF_CANDEFAULT ); // Pone el botón por defecto
	hb_errPutTries( pError, 5 ); // Numero de intentos

	hb_errLaunch( pError ); // Se lanza el error relleno
	hb_errRelease( pError ); // Libera el objeto
}





























