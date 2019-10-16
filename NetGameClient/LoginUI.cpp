#include "LoginUI.h"

GlobalData *GlobalData::instance = NULL;
LoginUI::LoginUI( HINSTANCE hInstance, HWND hWnd)
{
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	
	Init();
}


LoginUI::~LoginUI()
{
	CSpritesManager::GetInstance()->DeleteSprite(loginUIBg);
	CSpritesManager::GetInstance()->DeleteSprite(LOGO);
	CSpritesManager::GetInstance()->DeleteSprite(PasswordEntryBox);
	DestroyWindow(hName);
	DestroyWindow(hPwd);
	delete(btnLogin);
	delete(btnEnter);
	delete(ExitButton);
		
}



void LoginUI::Init()
{
	

	loginUIBg = CSpritesManager::GetInstance()->CreateSprite(TEXT("loginUIBg"), D2D1::Point2F(0, 0),0,0);
	LOGO = CSpritesManager::GetInstance()->CreateSprite(TEXT("LOGO"), D2D1::Point2F(0, 0), 0, 0);
	PasswordEntryBox = CSpritesManager::GetInstance()->CreateSprite(TEXT("PasswordEntryBox"), D2D1::Point2F(30, 155), 0, 0);

	//创建文本框子窗口
	//SetBkMode(,TRANSPARENT);
	hName = CreateWindow(TEXT("EDIT"), NULL,
		WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | WS_BORDER
		| ES_MULTILINE | ES_LEFT,
		195, 245, 180, 24, hWnd, (HMENU)IDB_EDIT_NAME,
		hInstance, NULL);

	hPwd = CreateWindow(TEXT("EDIT"), NULL,
		WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | WS_BORDER
		| ES_LEFT | ES_PASSWORD,
		195, 310, 180, 24, hWnd, (HMENU)IDB_EDIT_PWD,
		hInstance, NULL);
	

	CSprite *pEnterUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("EnterButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pEnterDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("EnterButton1"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	btnEnter = new CSpriteButton(1, D2D1::Point2F(63, 350), pEnterUp, pEnterDown);

	CSprite *pExitUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("ExitButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pExitDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("ExitButton1"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	ExitButton = new CSpriteButton(1, D2D1::Point2F(410, 160), pExitUp, pExitDown);


	CSprite *pLoginUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("LoginButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pLoginDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("LoginButton1"), D2D1::Point2F(0, 0), 0,0, 0, 0);
	 
	btnLogin = new CSpriteButton(1, D2D1::Point2F(170, 387), pLoginUp, pLoginDown);
	
	//隐藏登陆框
	LoginWindow(false);
}

void LoginUI :: LoginWindow(bool IsShow){
	
	if (IsShow){
		ShowWindow(hName, SW_SHOWNORMAL);//隐藏文本
		ShowWindow(hPwd, SW_SHOWNORMAL);
	}
	else{
		ShowWindow(hName, SW_HIDE);//隐藏文本
		ShowWindow(hPwd, SW_HIDE);
	}
	btnEnter->SetVisible(!IsShow);
	btnLogin->SetVisible(IsShow);
	PasswordEntryBox->SetVisible(IsShow);
	ExitButton->SetVisible(IsShow);
}

