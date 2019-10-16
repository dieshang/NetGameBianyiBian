#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include "TextSprite.h"
#include <list>
#include <vector>
#include <string>
using namespace std;
class TextSpriteManager
{
public:
	TextSpriteManager();
	static TextSpriteManager *instance;
	ID2D1HwndRenderTarget 	*pRenderTarget;
	IDWriteFactory* pWriteFactory;
	list<TextSprite*>				textSpriteList;
	vector<TextSprite*>			toBeDeleted;
public:
	static TextSpriteManager  *GetInstance()
	{
		if (!instance)
		{
			instance = new TextSpriteManager();
		}
		return instance;
	}
	void init(ID2D1HwndRenderTarget 	*pRenderTarget,
		IDWriteFactory* pWriteFactory);
	~TextSpriteManager();

	TextSprite * CreateTextSprite(ID2D1HwndRenderTarget 	*pRenderTarget,
		IDWriteFactory* pWriteFactory,
		LPTSTR pText,
		D2D1_RECT_F &rc,
		D2D1::ColorF &fontColor,
		int fontSize
		);		//创建精灵节点
	void DeleteTextSprite(TextSprite *pTextSprite);	//删除精灵节点				
	void Render();									//渲染	
	void Release();
	void Update(float fDeltaTime);
};

