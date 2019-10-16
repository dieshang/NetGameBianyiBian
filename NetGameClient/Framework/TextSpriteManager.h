#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include "TextSprite.h"
#include <list>
#include <vector>
using namespace std;
class TextSpriteManager
{
private:
	ID2D1HwndRenderTarget 	*pRenderTarget;
	IDWriteFactory* pWriteFactory;
	list<TextSprite*>	textSpriteList;
	vector<TextSprite*>			toBeDeleted;
	

	
public:
	TextSpriteManager();

	virtual ~TextSpriteManager();
	static TextSpriteManager *instance;
	static TextSpriteManager *GetInstance()
	{
		if (instance == NULL)
		{
			instance = new TextSpriteManager();
		}
		return instance;
	}

	void init(ID2D1HwndRenderTarget 	*pRenderTarget,
		IDWriteFactory* pWriteFactory);


	TextSprite * CreateTextSprite(
		LPTSTR pText,
		D2D1_RECT_F &rc,
		int fontColor,
		int fontSize,
		bool isHeap = false
		);		//创建精灵节点
	void DeleteTextSprite(TextSprite *pTextSprite);	//删除精灵节点				
	void Render();									//渲染	
	void Release();
	void Update(float fDeltaTime);
};

