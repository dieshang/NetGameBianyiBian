#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include "Sprite.h"
#include "Helper.h"
class TextSprite
{
public:
	TextSprite(LPTSTR pText, D2D1_RECT_F &rt, int fontColor, int fontSize, bool isHeap);
	~TextSprite();
	void init(ID2D1HwndRenderTarget 	*pRenderTarget,
		IDWriteFactory* pWriteFactory);
	void SetVisible(bool bVal);																	//���þ���ɼ��� 
	bool IsVisible();
	void Render();
	void SetText(const LPTSTR pStr);
	void SetRect(D2D1_RECT_F &rt);
	void SetColor(const int fontColor);
	void SetFontSize(int fontSize);
	void Release();
	const LPTSTR GetText()
	{
		return pText;
	}

	LPTSTR		pText;       //��ʾ�ı�
private:

	ID2D1HwndRenderTarget 	*pRenderTarget;
	IDWriteFactory* pWriteFactory;
	IDWriteTextFormat* pTextFormat; 
	ID2D1SolidColorBrush		*pTextBrush;
	
	bool isHeap;    //�ı��Ƿ��Ƕѣ�Ĭ����ջֵΪfalse
	D2D1_RECT_F rt;          //�������λ��
	int fontColor;  //������ɫ
	int fontSize;             //�����С

	bool	bVisible;
	

};

