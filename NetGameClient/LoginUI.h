#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Framework\SpritesManager.h"
#include "Framework\ResourcesPool.h"
#include "Framework\Game.h"
#include "Framework\SpriteButton.h"

#include "GlobalData.h"
const int IDC_LOGINUI_LABEL = 1;
const int IDB_EDIT_NAME = 2;
const int IDB_EDIT_PWD = 3;
const int IDB_BUTTON_LOGIN = 4;


class LoginUI
{
private:
	CSprite *loginUIBg;
	CSprite *LOGO;
	CSprite *PasswordEntryBox;

	HINSTANCE hInstance;
	HWND hWnd;


public:
	CSpriteButton *btnLogin;
	CSpriteButton *btnEnter;
	CSpriteButton *ExitButton;
	HWND hName;
	HWND hPwd;
	LoginUI(HINSTANCE hInstance, HWND hWnd);
	~LoginUI();
	void Init();
	void LoginWindow(bool IsShow);

};

