#include "TextSpriteManager.h"


TextSpriteManager::TextSpriteManager()
{
}


TextSpriteManager::~TextSpriteManager()
{
	list<TextSprite *>::iterator ite = textSpriteList.begin();
	while (ite != textSpriteList.end())
	{
		delete *ite;
		ite++;
	}
	textSpriteList.clear();
}

void TextSpriteManager::init(ID2D1HwndRenderTarget 	*pRenderTarget,
	IDWriteFactory* pWriteFactory)
{
	this->pRenderTarget = pRenderTarget;
	this->pWriteFactory = pWriteFactory;
}

TextSprite * TextSpriteManager::CreateTextSprite(
	LPTSTR pText,
	D2D1_RECT_F &rt,
	int fontColor,
	int fontSize,
	bool isHeap
	)
{
	TextSprite* pTextSprite = new TextSprite(pText,rt,fontColor,fontSize,isHeap);
	pTextSprite->init(pRenderTarget, pWriteFactory);
	textSpriteList.push_back(pTextSprite);
	return pTextSprite;
}
void TextSpriteManager::DeleteTextSprite(TextSprite *pTextSprite)
{
	
	pTextSprite->SetVisible(false);
	toBeDeleted.push_back(pTextSprite);

}
void TextSpriteManager::Render()									//‰÷»æ	
{
	for (list<TextSprite*>::iterator ite = textSpriteList.begin(); ite != textSpriteList.end(); ite++)
	{
		if ((*ite)->IsVisible())
		{
			(*ite)->Render();
		}
	}

}

void TextSpriteManager::Update(float fDeltaTime)
{
	for (int i = 0; i<toBeDeleted.size(); ++i)
	{
		delete toBeDeleted[i];
		textSpriteList.remove(toBeDeleted[i]);
	}
	if (toBeDeleted.size() > 0)
	{
		toBeDeleted.clear();
	}

}


void TextSpriteManager::Release()
{
	for (list<TextSprite*>::iterator ite = textSpriteList.begin(); ite != textSpriteList.end(); ite++)
	{
		(*ite)->Release();
	}
}