
#include "resource.h"
#include "TCPServer.h"
#include "Game.h"
#include "Common.h"
#include "MsgDefine.h" //包含消息头文件
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

HWND hwndEdit;
const int IDB_EDIT=11;       //定义文本框

HWND hWnd;
HWND hwndChatEdit;  //只读文本框显示

HINSTANCE hInst;
CGame MyGame;  //创建一个猜数字游戏对象


//void ShowText(char *p); //自定义只读显示文本框内容显示函数定义


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS wndcls;
	wndcls.cbClsExtra		= 0;             //类结构后附加的额外的byte数
	wndcls.cbWndExtra		= 0;  
	wndcls.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);     //窗口刷新的画笔句柄
	wndcls.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndcls.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndcls.hInstance=hInstance; 
	wndcls.lpfnWndProc=WndProc;      //指定消息回调函数
	wndcls.lpszClassName=TEXT("GameWindow");  //标题栏显示标题
	wndcls.lpszMenuName=LPCWSTR(IDR_MENU1);          //菜单
	wndcls.style=CS_HREDRAW | CS_VREDRAW;  //水平重画和竖直重画
	RegisterClass(&wndcls);

	hInst = hInstance; // Store instance handle in our global variable

	//设置窗口风格：
	DWORD dwStyle;
	dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	//取得去掉windows系统菜单栏后的工作区
	RECT rcArea;
	SystemParametersInfo( SPI_GETWORKAREA, NULL, &rcArea, NULL );
	//取得客户区大小为*600 对应的窗口大小
	RECT rect;
	rect.left=rect.top=0;
	rect.right=640;
	rect.bottom=480;
	::AdjustWindowRectEx( &rect, dwStyle, TRUE, 0);
	// 将视窗的位置设定在屏幕（工作范围）的中央
	int w = rect.right-rect.left;
	int h = rect.bottom-rect.top;
	int x0 = rcArea.left + ( rcArea.right-rcArea.left - w ) / 2;
	int y0 = rcArea.top + ( rcArea.bottom-rcArea.top - h ) / 2;
	srand((unsigned)time(NULL));
	// 创建窗口
	hWnd = CreateWindow(TEXT("GameWindow"),TEXT("服务器"), dwStyle,
	x0, y0, w, h, NULL,NULL, hInstance, NULL);

	hInst=hInstance;

	if (!hWnd)  return FALSE;
	ShowWindow(hWnd,SW_SHOWNORMAL);   //显示窗口
	UpdateWindow(hWnd);  //更新窗口
	
	
	MSG msg;
	while	(GetMessage (&msg, NULL, 0, 0))//从消息队列中取出消息
	{
		TranslateMessage (&msg) ; //实现键盘消息翻译,将其翻译成Windows字符集.
		DispatchMessage (&msg) ;// 将消息发送到窗口处理.
	}
	return 0;
}


LRESULT CALLBACK WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
	PAINTSTRUCT ps;


	switch(uMsg)
	{
	case WM_SOCKET:
		MyGame.WndProc(hwnd,uMsg,wParam,lParam);
		break;
	//case WM_TIMER:
	//	MyGame.TimeFun(wParam);
		break;
	case WM_CREATE:
		//创建文本框子窗口
		hwndChatEdit=CreateWindow(TEXT("EDIT"),NULL,	WS_CHILD | WS_VISIBLE |WS_BORDER|WS_TABSTOP
			| ES_MULTILINE | ES_LEFT | ES_READONLY|ES_AUTOVSCROLL|WS_VSCROLL,
			10,10,630,450,hwnd,(HMENU)IDB_EDIT,hInst,NULL);
		MyGame.InitSocket(hwnd);
		MyGame.InitGame(hwndChatEdit);
		if (MyGame.StartServer(8000))
		{
			MyGame.ShowText(TEXT("服务器开始在8000端口监听"));
		}
		else
		{
			MyGame.ShowText(TEXT("服务器启动失败"));
		}
		

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);	
		break;
	case WM_CLOSE:
		if(IDYES==MessageBoxW(hwnd,TEXT("是否真的结束？"),TEXT("GameWindow"),MB_YESNO))
		{
			MyGame.Release();
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
	}
	return 0;
}

