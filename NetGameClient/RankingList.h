#pragma once
#include "Framework\SpritesManager.h"
#include "Framework\ResourcesPool.h"
#include "Framework\SpriteButton.h"
#include "Framework\TextSpriteManager.h"
class RankingList
{
public:
	RankingList();
	~RankingList();
	void Init();
	//������Ϸ���˵���ť
	CSpriteButton *bGoBackStartButton;
	//��ʾ���а�
	void WritePrize(int Prize, WCHAR cName1[20], int score);

private:
	

	//����ͼƬ
	CSprite * Bgs;
	//������
	CSprite*BgKs;
	
	TextSprite *FirstPrize;
	TextSprite *SecondPrize;
	TextSprite *ThirdPrize;
	TextSprite *FourthPrize;
	TextSprite *FifthPrize;
};

