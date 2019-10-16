
#include "resource.h"
#include "TCPServer.h"
#include "Game.h"
#include "Common.h"
#include "MsgDefine.h" //������Ϣͷ�ļ�
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

HWND hwndEdit;
const int IDB_EDIT=11;       //�����ı���

HWND hWnd;
HWND hwndChatEdit;  //ֻ���ı�����ʾ

HINSTANCE hInst;
CGame MyGame;  //����һ����������Ϸ����


//void ShowText(char *p); //�Զ���ֻ����ʾ�ı���������ʾ��������


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS wndcls;
	wndcls.cbClsExtra		= 0;             //��ṹ�󸽼ӵĶ����byte��
	wndcls.cbWndExtra		= 0;  
	wndcls.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);     //����ˢ�µĻ��ʾ��
	wndcls.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndcls.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndcls.hInstance=hInstance; 
	wndcls.lpfnWndProc=WndProc;      //ָ����Ϣ�ص�����
	wndcls.lpszClassName=TEXT("GameWindow");  //��������ʾ����
	wndcls.lpszMenuName=LPCWSTR(IDR_MENU1);          //�˵�
	wndcls.style=CS_HREDRAW | CS_VREDRAW;  //ˮƽ�ػ�����ֱ�ػ�
	RegisterClass(&wndcls);

	hInst = hInstance; // Store instance handle in our global variable

	//���ô��ڷ��
	DWORD dwStyle;
	dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	//ȡ��ȥ��windowsϵͳ�˵�����Ĺ�����
	RECT rcArea;
	SystemParametersInfo( SPI_GETWORKAREA, NULL, &rcArea, NULL );
	//ȡ�ÿͻ�����СΪ*600 ��Ӧ�Ĵ��ڴ�С
	RECT rect;
	rect.left=rect.top=0;
	rect.right=640;
	rect.bottom=480;
	::AdjustWindowRectEx( &rect, dwStyle, TRUE, 0);
	// ���Ӵ���λ���趨����Ļ��������Χ��������
	int w = rect.right-rect.left;
	int h = rect.bottom-rect.top;
	int x0 = rcArea.left + ( rcArea.right-rcArea.left - w ) / 2;
	int y0 = rcArea.top + ( rcArea.bottom-rcArea.top - h ) / 2;
	srand((unsigned)time(NULL));
	// ��������
	hWnd = CreateWindow(TEXT("GameWindow"),TEXT("������"), dwStyle,
	x0, y0, w, h, NULL,NULL, hInstance, NULL);

	hInst=hInstance;

	if (!hWnd)  return FALSE;
	ShowWindow(hWnd,SW_SHOWNORMAL);   //��ʾ����
	UpdateWindow(hWnd);  //���´���
	
	
	MSG msg;
	while	(GetMessage (&msg, NULL, 0, 0))//����Ϣ������ȡ����Ϣ
	{
		TranslateMessage (&msg) ; //ʵ�ּ�����Ϣ����,���䷭���Windows�ַ���.
		DispatchMessage (&msg) ;// ����Ϣ���͵����ڴ���.
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
		//�����ı����Ӵ���
		hwndChatEdit=CreateWindow(TEXT("EDIT"),NULL,	WS_CHILD | WS_VISIBLE |WS_BORDER|WS_TABSTOP
			| ES_MULTILINE | ES_LEFT | ES_READONLY|ES_AUTOVSCROLL|WS_VSCROLL,
			10,10,630,450,hwnd,(HMENU)IDB_EDIT,hInst,NULL);
		MyGame.InitSocket(hwnd);
		MyGame.InitGame(hwndChatEdit);
		if (MyGame.StartServer(8000))
		{
			MyGame.ShowText(TEXT("��������ʼ��8000�˿ڼ���"));
		}
		else
		{
			MyGame.ShowText(TEXT("����������ʧ��"));
		}
		

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);	
		break;
	case WM_CLOSE:
		if(IDYES==MessageBoxW(hwnd,TEXT("�Ƿ���Ľ�����"),TEXT("GameWindow"),MB_YESNO))
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

