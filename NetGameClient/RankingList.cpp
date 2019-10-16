#include "RankingList.h"


RankingList::RankingList()
{
	Init();
}


RankingList::~RankingList()
{
	TextSpriteManager::GetInstance()->DeleteTextSprite(FirstPrize); 
	TextSpriteManager::GetInstance()->DeleteTextSprite(SecondPrize);
	TextSpriteManager::GetInstance()->DeleteTextSprite(ThirdPrize);
	TextSpriteManager::GetInstance()->DeleteTextSprite(FourthPrize);
	TextSpriteManager::GetInstance()->DeleteTextSprite(FifthPrize);
}


void RankingList::Init()
{
	 Bgs=CSpritesManager::GetInstance()->CreateSprite(TEXT("ksbackground"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	 BgKs=CSpritesManager::GetInstance()->CreateSprite(TEXT("ÅÅÐÐ°ñ¿ò"), D2D1::Point2F(0, 0), 0, 0, 0, 0);

	 CSprite *pExitUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("ExitButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pExitDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("ExitButton1"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bGoBackStartButton = new CSpriteButton(1, D2D1::Point2F(400, 100), pExitUp, pExitDown);

	FirstPrize = TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(" "), D2D1::RectF(170, 155, 500, 225), 0xDFA718, 38);
	SecondPrize= TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(" "), D2D1::RectF(170, 235, 500, 305), 0xA062BC, 38);
	ThirdPrize = TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(" "), D2D1::RectF(170, 315, 500, 385), 0xD56D4C, 38);
	FourthPrize = TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(" "), D2D1::RectF(170, 395, 500, 465), 0x737373, 38);
	FifthPrize = TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(" "), D2D1::RectF(170, 475, 500, 800), 0x737373, 38);
}


void RankingList::WritePrize(int Prize, WCHAR cName1[20], int score){
	wchar_t *a1 = new wchar_t[10];
	wsprintf(a1, L"%s     %d", cName1, score);
	switch (Prize)
	{
	case 1:
		FirstPrize->SetText(a1);
		break;
	case 2:
		SecondPrize->SetText(a1);
		break;
	case 3:
		ThirdPrize->SetText(a1);
		break;
	case 4:
		FourthPrize->SetText(a1);
		break;
	case 5:
		FifthPrize->SetText(a1);
		break;
	}

}


