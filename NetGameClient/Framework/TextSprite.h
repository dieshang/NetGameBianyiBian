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
	void SetVisible(bool bVal);																	//设置精灵可见性 
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

	LPTSTR		pText;       //显示文本
private:

	ID2D1HwndRenderTarget 	*pRenderTarget;
	IDWriteFactory* pWriteFactory;
	IDWriteTextFormat* pTextFormat; 
	ID2D1SolidColorBrush		*pTextBrush;
	
	bool isHeap;    //文本是否是堆，默认是栈值为false
	D2D1_RECT_F rt;          //输出矩形位置
	int fontColor;  //字体颜色
	int fontSize;             //字体大小

	bool	bVisible;
	

};

