#include "Input.h"

CInput::CInput(void)
{
	bUseJoystick = false;
	pKeyboard = NULL;
	pMouse    = NULL;
	pJoystick = NULL;
	
	mouseMoveX =0;
	mouseMoveY = 0;

}

CInput::~CInput(void)
{
	ReleaseInput();

}

//------------------------------------------------------------------------------------
// Release all input resource.
//------------------------------------------------------------------------------------
void CInput::ReleaseInput()
{
	// Releases access to keyboard
	if(pKeyboard)
		pKeyboard->Unacquire();

	// Releases access to mouse
	if(pMouse)
		pMouse->Unacquire();

	// Releases access to joystick
	if(bUseJoystick && (pJoystick != NULL))
		pJoystick->Unacquire();

	// release keyboard and mouse
	Safe_Release(pKeyboard);
	Safe_Release(pMouse);

	// release joystick
	if(bUseJoystick)
		Safe_Release(pJoystick);

	Safe_Release(g_directinput);
}

//------------------------------------------------------------------------------------
// Create directinput, include keybrad, mouse, joystick.
//------------------------------------------------------------------------------------
void CInput::CreateInput(HINSTANCE instance, HWND hwnd, int min, int max, int nDeadZone, bool bUseJoystick)
{
	CreateDirectinput(instance);

	CreateKeyboard(hwnd);
	CreateMouse(hwnd);

	if(bUseJoystick)
		CreateJoystick(hwnd, min, max, nDeadZone);
}

//------------------------------------------------------------------------------------
// Creates a Microsoft DirectInput object.
//------------------------------------------------------------------------------------
bool CInput::CreateDirectinput(HINSTANCE instance)
{
	if(FAILED(DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**) &g_directinput, NULL)))
	{
		MessageBox(NULL, TEXT("Create Directinput object failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------------
// Create keyboard device.
//------------------------------------------------------------------------------------
bool CInput::CreateKeyboard(HWND hwnd)
{
	// create keyboard device
	if(FAILED(g_directinput->CreateDevice(GUID_SysKeyboard, &pKeyboard, NULL)))
	{
		MessageBox(NULL, TEXT("DirectInput interface create failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// Sets the data format for the Microsoft DirectInput device.
	if(FAILED(pKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(NULL, TEXT("Set data format with keyboard read mode failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// Establishes the cooperative level for this instance of the device. 
	// The cooperative level determines how this instance of the device interacts with other instances
	// of the device and the rest of the system.
	if (FAILED(pKeyboard->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	//if(FAILED(pKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, TEXT("Set cooperative Leve failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// Obtains access to the keyboard device
	if(FAILED(pKeyboard->Acquire()))
	{
		MessageBox(NULL, TEXT("Acquire keyboard access failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// zero keyboard buffer
	ZeroMemory(keyBuffer, sizeof(char) * 256);
	ZeroMemory(oldKeyBuffer,sizeof(char) * 256);

	return true;
}

//------------------------------------------------------------------------------------
// Read keyboard data from buffer.
//------------------------------------------------------------------------------------
bool CInput::ReadKeyboard()
{
	/*HRESULT hr = pKeyboard->GetDeviceState(sizeof(keyBuffer), (LPVOID) keyBuffer);*/
	if(FAILED(pKeyboard->GetDeviceState(sizeof(keyBuffer), (LPVOID) keyBuffer)))
	{
		// re-acquire access to keyboard
		HRESULT hr = pKeyboard->Acquire();

		if(FAILED(pKeyboard->GetDeviceState(sizeof(keyBuffer), (LPVOID) keyBuffer)))
			return false;
	}

	return true;
}

//------------------------------------------------------------------------------------
// Create mouse device.
//------------------------------------------------------------------------------------
bool CInput::CreateMouse(HWND hwnd)
{
	// create mouse input device
	if(FAILED(g_directinput->CreateDevice(GUID_SysMouse, &pMouse, NULL)))
	{
		MessageBox(NULL, TEXT("Create mouse input device failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// set data format for mouse
	if(FAILED(pMouse->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(NULL, TEXT("Set mouse data format failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// set cooperative level for mouse
	if(FAILED(pMouse->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(NULL, TEXT("Set mouse cooperative level failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// set property for mouse
	DIPROPDWORD device_prop;

	device_prop.diph.dwSize       = sizeof(DIPROPDWORD);
	device_prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	device_prop.diph.dwObj        = 0;
	device_prop.diph.dwHow        = DIPH_DEVICE;
	device_prop.dwData            = ITEMS_NUM;

	if(FAILED(pMouse->SetProperty(DIPROP_BUFFERSIZE, &device_prop.diph)))
	{
		MessageBox(NULL, TEXT("Set property for mouse failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// get access to mouse
	if(FAILED(pMouse->Acquire()))
	{
		MessageBox(NULL, TEXT("Get access to mouse failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}
	ZeroMemory(mouseBuffer, sizeof(DIDEVICEOBJECTDATA) * ITEMS_NUM);

	return true;
}

//------------------------------------------------------------------------------------
// Read data from mouse buffer.
//------------------------------------------------------------------------------------
bool CInput::ReadMouse()
{
	DWORD read_num = ITEMS_NUM;

	// zero mouse buffer before reading data 
	ZeroMemory(mouseBuffer, sizeof(DIDEVICEOBJECTDATA) * ITEMS_NUM);

	// read all mouse data from buffer
	
		if(FAILED(pMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mouseBuffer, &read_num, 0)))
		{
			pMouse->Acquire();

			if(FAILED(pMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mouseBuffer, &read_num, 0)))
				return false;
		}

		mouseMoveX= mouseMoveY = 0;
	for(int i = 0; i < read_num; i++)
	{

		if(mouseBuffer[i].dwOfs == DIMOFS_X)
			mouseMoveX += mouseBuffer[i].dwData;

		if(mouseBuffer[i].dwOfs == DIMOFS_Y)
			mouseMoveY += mouseBuffer[i].dwData;        
	}

	return true;
}

//------------------------------------------------------------------------------------
// Judge whether left mouse button has been pressed.
//------------------------------------------------------------------------------------
bool CInput::IsLButtonPressed()
{
	for(int i = 0; i < ITEMS_NUM; i++)
	{
		if((mouseBuffer[i].dwOfs == DIMOFS_BUTTON0) && (mouseBuffer[i].dwData & 0x80))
			return true;
	}

	return false;
}

//------------------------------------------------------------------------------------
// Judge whether right mouse button has been pressed.
//------------------------------------------------------------------------------------
bool CInput::IsRButtonPressed()
{
	for(int i = 0; i < ITEMS_NUM; i++)
	{
		if((mouseBuffer[i].dwOfs == DIMOFS_BUTTON1) && (mouseBuffer[i].dwData & 0x80))
			return true;
	}

	return false;
}

//------------------------------------------------------------------------------------
// Judge whether mouse wheel has been pressed.
//------------------------------------------------------------------------------------
bool CInput::IsMButtonPressed()
{
	for(int i = 0; i < ITEMS_NUM; i++)
	{
		if((mouseBuffer[i].dwOfs == DIMOFS_BUTTON2) && (mouseBuffer[i].dwData & 0x80))
			return true;
	}

	return false;
}

//------------------------------------------------------------------------------------
// Judge whether left mouse button has been pressed.
//------------------------------------------------------------------------------------
bool CInput::IsLButtonUp()
{
	for(int i = 0; i < ITEMS_NUM; i++)
	{
		if((mouseBuffer[i].dwOfs == DIMOFS_BUTTON0) && (mouseBuffer[i].dwData & 0x80))
		{
			ZeroMemory(mouseBuffer, sizeof(DIDEVICEOBJECTDATA) * ITEMS_NUM);
			return true;
		}
			
	}

	return false;
}

//------------------------------------------------------------------------------------
// Judge whether right mouse button has been pressed.
//------------------------------------------------------------------------------------
bool CInput::IsRButtonUp()
{
	for(int i = 0; i < ITEMS_NUM; i++)
	{
		if((mouseBuffer[i].dwOfs == DIMOFS_BUTTON1) && (mouseBuffer[i].dwData & 0x80))
		{
			ZeroMemory(mouseBuffer, sizeof(DIDEVICEOBJECTDATA) * ITEMS_NUM);
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------------
// Judge whether mouse wheel has been pressed.
//------------------------------------------------------------------------------------
bool CInput::IsMButtonUp()
{
	for(int i = 0; i < ITEMS_NUM; i++)
	{
		if((mouseBuffer[i].dwOfs == DIMOFS_BUTTON2) && (mouseBuffer[i].dwData & 0x80))
		{
			ZeroMemory(mouseBuffer, sizeof(DIDEVICEOBJECTDATA) * ITEMS_NUM);
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------------
// Create joystick.
//------------------------------------------------------------------------------------
bool CInput::CreateJoystick(HWND hwnd, int min, int max, int nDeadZone)
{
	// Enumerates all joystick that have been installed successfully
	if(FAILED(g_directinput->EnumDevices(DI8DEVCLASS_GAMECTRL, Enum_Joystick, &pJoystick, DIEDFL_ATTACHEDONLY)))
	{
		MessageBox(NULL, TEXT("Enumerate joystick failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	if(pJoystick == NULL)
	{
		MessageBox(NULL, TEXT("There is no joystick has been installed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// set data format for mouse
	if(FAILED(pMouse->SetDataFormat(&c_dfDIJoystick2)))
	{
		MessageBox(NULL, TEXT("Set joystick data format failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// set cooperative level for mouse
	if(FAILED(pMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(NULL, TEXT("Set joystick cooperative level failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// set property for mouse
	DIPROPRANGE device_prop;

	device_prop.diph.dwSize       = sizeof(DIPROPRANGE);
	device_prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	device_prop.diph.dwObj        = 0;
	device_prop.diph.dwHow        = DIPH_DEVICE;
	device_prop.lMin              = min;
	device_prop.lMax              = max;

	if(FAILED(pJoystick->SetProperty(DIPROP_RANGE, &device_prop.diph)))
	{
		MessageBox(NULL, TEXT("Set property range for joystick failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// set dead zone for joystick
	DIPROPDWORD dead_zone_prop;

	dead_zone_prop.diph.dwSize       = sizeof(DIPROPDWORD);
	dead_zone_prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dead_zone_prop.diph.dwObj        = 0;
	dead_zone_prop.diph.dwHow        = DIPH_DEVICE;
	dead_zone_prop.dwData            = 100 * nDeadZone;DIPROP_DEADZONE;

	if(FAILED(pJoystick->SetProperty(DIPROP_DEADZONE, &dead_zone_prop.diph)))
	{
		MessageBox(NULL, TEXT("Set dead zone for joystick failed."), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	// zero joystick buffer
	ZeroMemory(&pJoystick, sizeof(DIJOYSTATE2));

	return true;
}

//------------------------------------------------------------------------------------
// Read data from joystick.
//------------------------------------------------------------------------------------
bool CInput::ReadJoystick()
{
	// get access to joystick
	if(FAILED(pJoystick->Acquire()))
		return false;

	// polling joystick to retrieve data
	if(FAILED(pJoystick->Poll()))
		return false;

	// get joystick current state
	if(DIERR_INPUTLOST == pJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &joystickBuffer))
	{
		// re-acquire access to joystick
		pJoystick->Acquire();

		if(FAILED(pJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &joystickBuffer)))
			return false;
	}

	return true;
}

//------------------------------------------------------------------------------------
// Application-defined callback function that receives Microsoft DirectInput devices 
// as a result of a call to the IDirectInput8::EnumDevices method.
//------------------------------------------------------------------------------------
BOOL CALLBACK Enum_Joystick(LPCDIDEVICEINSTANCE device_instance, LPVOID data)
{
	LPDIRECTINPUTDEVICE8* diDevice = (LPDIRECTINPUTDEVICE8*) data;

	if(FAILED(g_directinput->CreateDevice(device_instance->guidInstance, diDevice, NULL)))
		return DIENUM_CONTINUE;

	return DIENUM_STOP;
}
