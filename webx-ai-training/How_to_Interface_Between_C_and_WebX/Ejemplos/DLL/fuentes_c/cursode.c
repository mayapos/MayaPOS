
/******************************************************************************
 ********************** Uso de funciones en DLL *******************************
 ******************************************************************************/

#include <Windows.h>		// Para Windows
#include <hbapi.h>			// Para Harbour

/*
	UINT WinExec( LPCSTR lpCmdLine, UINT uCmdShow );
*/

HB_FUNC( WINEXEC )
{
	LPCSTR lpCmdLine = NULL;
	UINT uCmdShow = 0;

	UINT uiRet;

	lpCmdLine = hb_parc( 1 );
	uCmdShow = hb_parni( 2 );

	uiRet = WinExec( lpCmdLine, uCmdShow );

	hb_retni( uiRet );
}

/*
	UINT FindWindow( LPCSTR lpClassName, LPCSTR lpWindowName );
*/

HB_FUNC( FINDWINDOW )
{
	LPCSTR lpClassName = NULL;
	LPCSTR lpWindowName = NULL;

	HWND hRet;

	lpClassName = hb_parc( 1 );
	lpWindowName = hb_parc( 2 );

	hRet = FindWindow( lpClassName, lpWindowName );

	hb_retptr( hRet );
}

/*
	BOOL SetWindowText( HWND hWnd, LPCWSTR lpString );
*/

HB_FUNC( SETWINDOWTEXT )
{
	HWND hWnd = NULL;
	LPCSTR lpString = NULL;

	HB_BOOL lRet;

	hWnd = hb_parptr( 1 );
	lpString = hb_parc( 2 );

	lRet = SetWindowText( hWnd, lpString );

	hb_retl( lRet );
}

/*
	int MessageBox( HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType );
*/

HB_FUNC( MESSAGEBOX )
{
	HWND hWnd = NULL;
	LPCTSTR lpText = NULL;
	LPCTSTR lpCaption = NULL;
	UINT uType = MB_OK;

	HB_INT iRet;

	hWnd = hb_parptr( 1 );
	lpText = hb_parc( 2 );
	lpCaption = hb_parc( 3 );
	uType = hb_parnidef( 4, MB_OK );

	iRet = MessageBox( hWnd, lpText, lpCaption, uType );

	hb_retni( iRet );
}
