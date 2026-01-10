/*
 * Funciones en C para ser llamadas desde PRG
 */
 
#include "hbapi.h"

/*
 * Devuelve si un año es bisiesto o no
 */
HB_FUNC( MI_ISLEAP )
{
	HB_UINT uiYear = hb_parni( 1 ); // Recupera un entero pasado a la funcion desde PRG
	HB_BOOL lRet = HB_FALSE;

	if( uiYear > 0 )
	{
		lRet = ( ( uiYear % 4 == 0 && uiYear % 100 != 0 ) || uiYear % 400 == 0 );
	}

	hb_retl( lRet ); // Devuelve un valor logico por medio de la pila de harbour
}

/*
 * El cubo de un numero pasado por referencia
 */
HB_FUNC( MI_CUBO )
{
	HB_MAXINT iCubo = hb_parnint( 1 );

	iCubo = iCubo * iCubo * iCubo;

	hb_stornint( iCubo, 1 );
}

/*
 * Cuenta las ocurrencias de un caracter dentro de una cadena
 */
HB_FUNC( CHARCOUNT )
{
	const char *szCadena = hb_parc( 1 ); // 1 parametro como cadena
	HB_SIZE uiLen = hb_parclen( 1 ); // Tamaño de la cadena pasada en el parametro 1
	HB_UINT uiContador = 0;

	if( uiLen > 0 )
	{
		const char *cCarcter = hb_parc( 2 ); // 2 parametro como cadena
		HB_SIZE i;

		for( i = 0; i < uiLen; i++ )
		{
			if( szCadena[ i ] == cCarcter[ 0 ] )
			{
				++uiContador;
			}
		}
	}

	hb_retnint( uiContador );
}

/*
 * Busca la primera aparicion de un caracter dentro de una cadena
 */
HB_FUNC( SCANCHAR )
{
	const char *szCadena = hb_parc( 1 );
	HB_SIZE uiLen = hb_parclen( 1 );
	HB_SIZE uiPos = 0;

	if( uiLen > 0 )
	{
		const char *cCarcter = hb_parc( 2 );
		HB_SIZE i;

		for( i = 0; i < uiLen; i++ )
		{
			if( szCadena[ i ] == cCarcter[ 0 ] )
			{
				uiPos = i + 1; // Hay que sumar 1 ya que los arrays de C se basan en 0
				break;
			}
		}
	}

	hb_retnint( uiPos );
}

/*
 * Comprueba si una nota está aprobada o no y devuelve un literal con el resultado
 */
HB_FUNC( ESACTO )
{
	unsigned int uiNota = hb_parnidef( 1, 3 ); // Si no se pasa la variable pone por defecto "3", nota minima

	if( uiNota > 4 )
	{
		hb_storc( "APROBADO", 2 );
	}
	else
	{
		hb_storc( "SUSPENDIDO", 2 );
	}
}

/*
 * Dia de la semana
 * Uso de la funcion interna hb_xstrcpy() y de hb_retc_buffer()
 */

HB_FUNC( DIASEMANA )
{
	unsigned int uiDia = hb_parni( 1 ); // Recibe el numero

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

		hb_retc_buffer( szDia ); // Devuelve szDia y libera la memoria
	}
	else
	{
		hb_ret(); // Devuelve nil
	}
}

/*
 * Uso de parametros por referencia
 * Recibe 2 numeros enteros devuelve la suma, resta, producto y division de los numeros pasados
 */
HB_FUNC( CALCULA )
{
	int i1 = hb_parni( 1 );
	int i2 = hb_parni( 2 );

	// Paso por referencia:
	hb_storni( i1 + i2, 3 );
	hb_storni( i1 - i2, 4 );
	hb_storni( i1 * i2, 5 );
	hb_stornd( ( double ) i1 / i2, 6 ); // Ojo con el cast
}

/*
 * Incrementa en 100 el segundo elemento de un array pasado
 */
HB_FUNC( CAMBIAVALOR )
{
	int iVal = hb_parvni( 1, 2 );

	iVal = iVal + 100;

	hb_storvni( iVal, 1, 2 );
}

/*
 * Pasa un numero entero a numero romano
 */
 
HB_FUNC( INTTOROMAN )
{
	HB_INT  iNumInt = hb_parni( 1 );
	char *cNunRoman = ( char * ) hb_xgrab( 1024 );

	cNunRoman[ 0 ] = '\0';

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

	hb_retc( cNunRoman );
	hb_xfree( cNunRoman );
}

/*
 * Devuelve la suma de los elementos numericos de un array pasado
 */
HB_FUNC( SUMAARRAY )
{
	double uiTotal = 0.0;

	if( hb_extIsArray( 1 ) ) // Si es un array lo proceso
	{
		HB_SIZE i;
		HB_SIZE nLen = hb_parinfa( 1, 0 ); // Número de elementos

		for( i = 0; i < nLen; i++ )
		{
			switch( hb_parinfa( 1, i + 1 ) ) // Sumo 1 C se basa en 0 para el primer elemento
			{
				case HB_IT_INTEGER :
				case HB_IT_LONG :
					uiTotal += hb_parvnint( 1, i + 1 );
					break;

				case HB_IT_DOUBLE :
					uiTotal += hb_parvnd( 1, i + 1 );
					break;
					// El resto de tipos no numericos no se consideran
			}
		}
	}

	hb_retnd( uiTotal );
}

/*
 * Tabla de multiplicar del numero entero pasado
 */

HB_FUNC( TABLA )
{
	if( hb_parinfo( 1 ) == HB_IT_INTEGER ) // Para esto esta la macro HB_IS_NUMINT( p ) que hace esto
	{
		HB_MAXINT iMul = hb_parnint( 1 );
		HB_UINT n = 10;
		HB_UINT i;

		hb_reta( n ); // Crea el array vacio de 100 elementos y lo pone en la zona de devolución

		for( i = 1; i <= n; i++ )
		{
			hb_storvnint( iMul * i, -1, i ); // -1 accede a la zona de devolucion
		}
	}
	else
	{
		hb_ret();
	}
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
	HB_UINT uiPersona = hb_parni( 1 );
	TPersona *persona = hb_xgrab( sizeof( TPersona ) ); //Reserva memoria para TPersona

	// Rellena todos los miembros de TPersona según su tipo
	if( uiPersona == 1 )
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

	hb_reta( 6 ); // Crea el array en el stackReturn

	// Rellena el array creado en el stackReturn con el "-1"
	hb_storvc( persona->szNIF, -1, 1 );		// Cadena
	hb_storvc( persona->szNombre, -1, 2 );	// Cadena
	hb_storvni( persona->uiCodigo, -1, 3 );	// Entero
	hb_storvnd( persona->nSalrio, -1, 4 );	// Real
	hb_storvds( persona->szFecha, -1, 5 );	// Fecha como cadena <---
	hb_storvl( persona->bSoltero, -1, 6 );	// Booleano <---

	// ATENCION: toda la memoria que hayamos reservado la tenemos que liberar
	hb_xfree( persona );
}

/*
 * Lo mismo que la anterior pero usando un objeto en vez de un array
 */

#include "hbapiitm.h"

HB_FUNC( DAMEOBJPERSONA )
{
	PHB_ITEM obj = hb_param( 1, HB_IT_OBJECT );
	HB_UINT uiPersona = hb_parni( 2 );
	TPersona *persona = hb_xgrab( sizeof( TPersona ) ); //Reserva memoria para TPersona

	// Rellena todos los miembros de TPersona según su tipo
	if( uiPersona == 1 )
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

	hb_itemReturn( obj ); // Esto mete el objeto en el stackReturn

	// Rellena el objeto por posicion de la DATA creado en el stackReturn con el "-1"
	hb_storvc( persona->szNIF, -1, 1 );		// Cadena
	hb_storvc( persona->szNombre, -1, 2 );	// Cadena
	hb_storvni( persona->uiCodigo, -1, 3 );	// Entero
	hb_storvnd( persona->nSalrio, -1, 4 );	// Real
	hb_storvds( persona->szFecha, -1, 5 );	// Fecha como cadena <---
	hb_storvl( persona->bSoltero, -1, 6 );	// Booleano <---

	// ATENCION: toda la memoria que hayamos reservado la tenemos que liberar
	hb_xfree( persona );
}

/*
 * Da la vuenta a una cadena pasada
 */

HB_FUNC( REVERSE )
{
	const char *szInString = hb_parc( 1 );
	int iLen = hb_parclen( 1 );

	if( iLen )
	{
		char *szRetStr = hb_xgrab( iLen );
		int i;

		for( i = 0; i < iLen; i++ )
		{
			szRetStr[ i ] = szInString[ iLen - i - 1 ];
		}

		hb_retclen( szRetStr, iLen );

		hb_xfree( szRetStr );
	}
	else
	{
		hb_retc_null();
	}
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
	hb_retc_buffer( cstrtran( hb_parc( 1 ), hb_parclen( 1 ), hb_parc( 2 ),
							  hb_parclen( 2 ), hb_parc( 3 ), hb_parclen( 3 ) ) );
}

/*
 * Usando interfaces a funciones de C
 */

HB_FUNC( STRTOK )
{
	int iParametros = hb_pcount();

	if( iParametros > 0 )
	{
		const char *p = hb_parc( 1 );
		const char *s = hb_parc( 2 );

		hb_retc( strtok( ( char * ) p, s ) );
	}
}

/*
 * Interfaces con funciones matematicas de C
 */
#include <math.h>
/* coseno */
HB_FUNC( C_COS )
{
	hb_retnd( cos( hb_parnd( 1 ) ) );
}
/* seno */
HB_FUNC( C_SIN )
{
	hb_retnd( sin( hb_parnd( 1 ) ) );
}
/* tangente */
HB_FUNC( C_TAN )
{
	hb_retnd( tan( hb_parnd( 1 ) ) );
}
