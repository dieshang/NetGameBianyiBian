#pragma once

/***************************************************************************
	����ڵ�����࣬����������������
***************************************************************************/
#include "sprite.h"
#include "ResourcesPool.h"

#include "AnimationSprite.h"
#include <list>
#include <vector>
#include <string>
using namespace std;

class CSpritesManager
{
private:
	CSpritesManager()
	{
		pRenderTarget = NULL;
	}
	CSpritesManager(const CSpritesManager&){}
	CSpritesManager &operator =(const CSpritesManager&){}
	static CSpritesManager *instance;
public:
	static CSpritesManager *GetInstance()
	{
		if (!instance)
		{
			instance = new CSpritesManager();
		}
		return instance;
	}
	virtual ~CSpritesManager(void);
	
public:
	void SetRenderTarget(ID2D1HwndRenderTarget *pRenderTarget);
	CSprite * CreateSprite	(	const wstring		sResourceName,
								//ResourceType		rt,
								D2D1_POINT_2F		&vPos,
								float					w = 0,
								float					h=0,
								int					tx = 0,
								int					ty = 0,
								D2D1_POINT_2F		vHotSpot=D2D1::Point2F(0,0)
								);		//��������ڵ�
	CAnimationSprite * CreateAnimationSprite   (	const wstring   sResourceName,
													//ResourceType	rt,
													int				nFrames,
													float			nFps,
													D2D1_POINT_2F	&vPos,
													float				w,
													float				h,
													int				tx = 0,
													int				ty = 0,
													D2D1_POINT_2F   vHotSpot=D2D1::Point2F(0,0)
													);//������������ڵ�
	void DeleteSprite(CSprite *pSpriteNode);	//ɾ������ڵ�				
	void Render();									//��Ⱦ	
	void Release();
	void Update(float fDeltaTime);
	
	CSprite *Clone(CSprite *pSprite);
	CAnimationSprite *Clone(CAnimationSprite *pAniSprite);
protected:
	bool GetTextureFromResource(const wstring		sResourceName,
								//ResourceType		rt,
								ID2D1Bitmap			**ppTexture,
								int					w,
								int					h,
								int					&nWidth,
								int					&nHeight);

		
	ID2D1HwndRenderTarget       *pRenderTarget; 
	list<CSprite*>				spriteList;
	vector<CSprite*>			toBeDeleted;
	
};


