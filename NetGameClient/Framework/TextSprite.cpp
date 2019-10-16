#include "TextSprite.h"


TextSprite::TextSprite(
	LPTSTR pText,
	D2D1_RECT_F &rt,
	int fontColor,
	int fontSize, 
	bool isHeap = false)
{
	this->pText = pText;
	this->rt = rt;
	this->fontColor = fontColor;
	this->fontSize = fontSize;
	this->isHeap = isHeap;

	bVisible = true;

}


TextSprite::~TextSprite()
{
	Release();
}


void TextSprite::init(ID2D1HwndRenderTarget 	*pRenderTarget,
	IDWriteFactory* pWriteFactory)
{
	this->pRenderTarget = pRenderTarget;
	this->pWriteFactory = pWriteFactory;
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr))
	{
		hr = pWriteFactory->CreateTextFormat(
			L"ºÚÌå",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"zh-CN",
			&pTextFormat
			);
	}

	if (SUCCEEDED(hr))
	{
		hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(fontColor,1.0), &pTextBrush);
	}
}

void TextSprite::Render()
{
	if (this->pText == NULL)
	{
		return;
	}


	if (this->bVisible)
	{
		pRenderTarget->DrawText(pText, wcslen(pText), pTextFormat, rt, pTextBrush);
	}
	

	//pFont->DrawText(NULL, pText, -1, &Rect, DT_CALCRECT, 0);			//Calculate the size of the rect needed
	//pFont->DrawText(NULL, pText, -1, &Rect, DT_LEFT, rgbFontColor);	//Draw the text
}


void TextSprite::Release()
{
	
	SafeRelease(&pTextFormat);
	SafeRelease(&pTextBrush);
	if (isHeap)
	{
		delete []pText;
	}

}

void TextSprite::SetVisible(bool bVal)
{
	bVisible = bVal;
}

bool TextSprite::IsVisible()
{
	return bVisible;
}


void TextSprite::SetColor(const int fontColor)
{
	SafeRelease(&pTextBrush);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(fontColor, 1.0), &pTextBrush);
}
void TextSprite::SetFontSize(int fontSize){
	this->fontSize = fontSize;
}
void TextSprite::SetRect(D2D1_RECT_F &rt)
{
	this->rt = rt;
}

void TextSprite::SetText(const LPTSTR pStr){

	this->pText =pStr;
}