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
	//∑µªÿ”Œœ∑÷˜≤Àµ•∞¥≈•
	CSpriteButton *bGoBackStartButton;
	//œ‘ æ≈≈––∞Ò
	void WritePrize(int Prize, WCHAR cName1[20], int score);

private:
	

	//±≥æ∞Õº∆¨
	CSprite * Bgs;
	//±≥æ∞øÚ
	CSprite*BgKs;
	
	TextSprite *FirstPrize;
	TextSprite *SecondPrize;
	TextSprite *ThirdPrize;
	TextSprite *FourthPrize;
	TextSprite *FifthPrize;
};

