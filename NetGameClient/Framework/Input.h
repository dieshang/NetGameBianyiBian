#pragma once

#define DIRECTINPUT_VERSION 0x0800  

#include <dinput.h>

#define Safe_Release(object) if((object) != NULL) { (object)->Release(); (object)=NULL; }

#define ITEMS_NUM   10

static LPDIRECTINPUT8 g_directinput = NULL;

BOOL CALLBACK Enum_Joystick(LPCDIDEVICEINSTANCE device_instance, LPVOID data);


class CInput
{
public:
	CInput(void);
public:
	~CInput(void);
private:
	bool bUseJoystick;

	LPDIRECTINPUTDEVICE8 pKeyboard;
	LPDIRECTINPUTDEVICE8 pMouse;
	LPDIRECTINPUTDEVICE8 pJoystick;

	char keyBuffer[256];     // keyboad buffer (immediate mode)
	char oldKeyBuffer[256];
	DIDEVICEOBJECTDATA mouseBuffer[ITEMS_NUM];    // mouse data buffer (buffer mode)
	DIJOYSTATE2 joystickBuffer;                   // joystick buffer (immediate mode)

	int mouseMoveX, mouseMoveY;    // mouse move coordinate
public:
	void CreateInput(HINSTANCE instance, HWND hwnd, int min = -100, int max = 100, 
		int nDeadZone = 20, bool bUseJoystick = false);

	bool ReadKeyboard();
	bool ReadMouse();
	bool ReadJoystick();
	bool IsLButtonPressed();
	bool IsRButtonPressed();    
	bool IsMButtonPressed();

	bool IsLButtonUp();
	bool IsRButtonUp();    
	bool IsMButtonUp();


	// Judge which key user has been pressed
	bool IsKeyPressed(int key)    { return (keyBuffer[key] & 0x80 ? true : false); }
	bool IsKeyUp(int key)
	{
		bool bRet = false;
		if (keyBuffer[key] == oldKeyBuffer[key])
		{

			bRet = false;
		}
		else
		{

		
			if (keyBuffer[key] & 0x80)
			{
				
				bRet = true;
			}
			else
			{

				bRet = false;
			}
			memcpy(oldKeyBuffer,keyBuffer,sizeof(oldKeyBuffer));
		}
		return bRet;

	}

	int GetMouseX() { return mouseMoveX; }
	int GetMouseY() { return mouseMoveY; }

	// Judge which joystick button has been pressed
	bool IsJSButtonPressed(int button)
	{
		return (joystickBuffer.rgbButtons[button] & 0x80) ? true : false;
	}
private:
	bool CreateDirectinput(HINSTANCE instance);
	bool CreateKeyboard(HWND hwnd);
	bool CreateMouse(HWND hwnd);
	bool CreateJoystick(HWND hwnd, int min, int max, int nDeadZone);
	void ReleaseInput();

};
