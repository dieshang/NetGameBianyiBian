/************************************************************************
��Ϸ�����࣬���ڴ������־���ʹ�������������¼���
����һ�������࣬����ֱ�Ӵ�����������ʹ����Ӧ�ö���һ������̳�
��CGame,������������дInitGame()�������Լ��ĸ�����Դ
************************************************************************/
#pragma once

#include <D2D1.h>
#include <dwrite.h>
#include <wincodec.h>   //����WICλͼ�ļ���Ҫ��

#include "ResourcesPool.h"
#include "SpritesManager.h"
#include "TextSpriteManager.h"
#include "Input.h"




class CGame
{
public:
	CGame(HINSTANCE hInstance,HWND hWnd,int nFps = 0);											//���캯��
	virtual ~CGame(void);
public:
	//-----������Ӧ�����ͼ����¼�����������Ϊ�麯������������Ը��ݳ�����Ҫ������д---------
	virtual void HandleMouseUp(WPARAM wParam,LPARAM lParam){}				
	virtual void HandleMouseDown(WPARAM wParam,LPARAM lParam){}
	virtual void HandleMouseMove(WPARAM wParam,LPARAM lParam){}
	virtual void HandleDoubleClick(WPARAM wParam,LPARAM lParam){}
	virtual void HandleKeyUp(WPARAM wParam,LPARAM lParam){}
	virtual void HandleKeyDown(WPARAM wParam,LPARAM lParam){}

	
	virtual bool IsKeyUp(int key)
	{
		pInput->ReadKeyboard();
		return pInput->IsKeyUp(key);
	}
	virtual bool IsKeyPressed(int key)
	{
		pInput->ReadKeyboard();
		return pInput->IsKeyPressed(key);
	}
	virtual bool IsLButtonPressed()
	{
		pInput->ReadMouse();
		return pInput->IsLButtonPressed();
	}
	virtual bool IsRButtonPressed()
	{
		pInput->ReadMouse();
		return pInput->IsRButtonPressed();
	}

	virtual bool IsLButtonUp()
	{
		pInput->ReadMouse();
		return pInput->IsLButtonUp();
	}
	virtual bool IsRButtonUp()
	{
		pInput->ReadMouse();
		return pInput->IsRButtonUp();
	}

	//-----------------------------------------------------------------------------------------
	virtual void InitGame() = 0;										//���麯����������Դ		
	

	void GameFunc();															//ִ����Ϸ֡����
	virtual void Render();		//��Ⱦ	
	IDWriteFactory				*pDWriteFactory;
protected:

	HRESULT 	Init(HWND hWnd);
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();


	virtual void Update(float fDeltaTime);								//֡����	

	
	ID2D1Factory				*pD2DFactory  ;	 // Direct2D factory
	ID2D1HwndRenderTarget		*pRenderTarget; 
	IWICImagingFactory			*pWICFactory ;

	IDWriteTextFormat			*pTextFormat;
	ID2D1SolidColorBrush		*pTextBrush;

	

	CSpritesManager		*pSpritesManager;									//����������ָ��	
	CResourcesPool	    *pResPool	;										//��Դ�������ָ��	
	TextSpriteManager   *pTextSpriteManager;                                //�ı��������ָ��
	HWND				hWnd;												//���ھ��
	int					nFps;												//ÿ�����֡
	RECT				rectClient;											//�ͻ�������

	DWORD				t0;													//ǰһ֡��ʱ��
	int					nFixedDeltaTime;									//�̶���ʱ��

	double				t;													//����֡Ƶ����Ҫ���ۼ�ʱ��
	int					nfps;												//֡Ƶ
	unsigned int        nFrames;											//��֡��
	TCHAR               szBuf[255];											//��֡Ƶת��Ϊ�ַ������õ����ַ����� 


	HINSTANCE			hInstance;	
	CInput				*pInput;


	
	

	void Cleanup();


	
	

};
