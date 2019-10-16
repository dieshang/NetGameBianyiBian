#include <winsock2.h>
#define _WINSOCKAPI_  
#include <Windows.h> 

#include "Tetris.h"
HWND		hWnd ;
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

CTetris *pGame = NULL;																	//定义指针pGame
HINSTANCE hInst;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Demo") ;
	
	MSG			msg ;
	WNDCLASS	wc ;

 	wc.style			= CS_HREDRAW | CS_VREDRAW ;
 	wc.lpfnWndProc		= WndProc ;
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= hInstance ;
	wc.hIcon			= LoadIcon (NULL, IDI_APPLICATION) ;
  	wc.hCursor			= LoadCursor (NULL, IDC_ARROW) ;
 	wc.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH) ;
  	wc.lpszMenuName		= NULL ;
	wc.lpszClassName	= szAppName ;
	
	if (!RegisterClass (&wc))
     {
		MessageBox (	NULL, TEXT ("This program requires Windows NT!"), 
          				szAppName, MB_ICONERROR) ;
		return 0 ;
     }
	hWnd = CreateWindow(szAppName,	// window class name
			TEXT("辨一辨"),	// window caption
			//WS_OVERLAPPEDWINDOW,	// window style
			WS_OVERLAPPEDWINDOW^WS_THICKFRAME |WS_SYSMENU|WS_CLIPCHILDREN,//| WS_VISIBLE,
			//CW_USEDEFAULT,	// initial x position
			//CW_USEDEFAULT,	// initial y position
			//CW_USEDEFAULT,	// initial x size
			//CW_USEDEFAULT,	// initial y size
			0,0,495,677,
		//0,0,480,640,
			NULL,			// parent window handle
		    NULL,	        // window menu handle
		    hInstance,	    // program instance handle
		    NULL) ; 	    // creation parameters
	
	ShowWindow (hWnd, SW_NORMAL) ;
	UpdateWindow (hWnd) ;
	hInst = hInstance;
	//HMODULE h = GetModuleHandle(NULL);
	pGame =  new CTetris(hInstance,hWnd);												//进入消息循环之前，创建CPathFinding对象
	pGame->InitGame();

	
    BOOL  bMessage;
    PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
    while(msg.message != WM_QUIT)
    {
        bMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
        if(bMessage)
        {
				TranslateMessage(&msg);
            	DispatchMessage(&msg);
        }
		pGame->GameFunc();														//更新
	} 
	if (pGame)																	//程序结束前，释放资源
	{
		delete pGame;
	}
	
	return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc ;
	PAINTSTRUCT ps ;
	RECT		rect ;
	int wmId, wmEvent;
	switch (message)
    {
	case WM_SOCKET:
		pGame->WndProc(hwnd, message, wParam, lParam);
		break;
	case WM_CREATE:
		
		break;
		case WM_KEYUP:
			if (wParam == VK_ESCAPE)
			{
				PostQuitMessage (0) ;
			}
			pGame->HandleKeyUp(wParam,lParam);
			
			return 0;
		/*case WM_COMMAND:
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

			switch (wmId)
			{
			default:
				pGame->OnCommand(wmId);
			}
			break;*/
		//case WM_KEYDOWN:												//拦截WM_KEYDWON
		//	pGame->HandleKeyDown(wParam,lParam);						//调用HandleKeyDown函数处理键盘消息
		//	return 0;
		case WM_LBUTTONUP:												//拦截WM_KEYDWON
			pGame->HandleMouseUp(wParam,lParam);						//调用HandleKeyDown函数处理键盘消息
			return 0;
		case WM_LBUTTONDOWN:
			pGame->HandleMouseDown(wParam,lParam);
			return 0;
		//case WM_RBUTTONDOWN:
		//	pGame->HandleMouseDown(wParam,lParam);
		//	return 0;
		case WM_SIZE:
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;

     }
   return DefWindowProc (hwnd, message, wParam, lParam) ;
}