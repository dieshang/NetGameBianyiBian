#include "StartUI.h"


StartUI::StartUI()
{
	Init();
}


StartUI::~StartUI()
{
	CSpritesManager::GetInstance()->DeleteSprite(pGameBackGround);
	CSpritesManager::GetInstance()->DeleteSprite(pGamemusic);
	CSpritesManager::GetInstance()->DeleteSprite(pGamemusic1);
	CSpritesManager::GetInstance()->DeleteSprite(pGameSm);
	delete(bKsButton);
	delete(bSmButton);
	delete(bPhButton);
	delete(bTcButton);
	delete(bXxButton);
}


void StartUI::Init()
{
	




	pGameBackGround = CSpritesManager::GetInstance()->CreateSprite(TEXT("ksbackground"), D2D1::Point2F(0, 0), 0, 0, 0, 0);

	CSprite *pKsButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("KsButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pKsButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("KsButton1"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bKsButton = new CSpriteButton(1, D2D1::Point2F(113, 100), pKsButtonUp, pKsButtonDown);

	CSprite *pSmButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("SmButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pSmButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("SmButton1"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bSmButton = new CSpriteButton(1, D2D1::Point2F(113, 207), pSmButtonUp, pSmButtonDown);

	CSprite *pPhButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("PhButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pPhButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("PhButton1"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bPhButton = new CSpriteButton(1, D2D1::Point2F(113, 314), pPhButtonUp, pPhButtonDown);

	CSprite *pTcButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("TcButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pTcButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("TcButton1"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bTcButton = new CSpriteButton(1, D2D1::Point2F(113, 421), pTcButtonUp, pTcButtonDown);

	pGamemusic = CSpritesManager::GetInstance()->CreateSprite(TEXT("music"), D2D1::Point2F(435, 5), 0, 0, 0, 0);
	pGamemusic1 = CSpritesManager::GetInstance()->CreateSprite(TEXT("music1"), D2D1::Point2F(435, 5), 0, 0, 0, 0);

	pGameSm = CSpritesManager::GetInstance()->CreateSprite(TEXT("gameSm"), D2D1::Point2F(16, 57), 0, 0, 0, 0);

	CSprite *pXxUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("XxButton"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pXxDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("XxButton1"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bXxButton = new CSpriteButton(1, D2D1::Point2F(410, 67), pXxUp, pXxDown);

	CSprite *pSingleUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("单人挑战"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pSingleDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("单人挑战凹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bSingleButton = new CSpriteButton(1, D2D1::Point2F(45, 150), pSingleUp, pSingleDown);

	CSprite *pBattleUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("双人PK凸"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pBattleDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("双人PK凹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bBattleButton = new CSpriteButton(1, D2D1::Point2F(90, 270), pBattleUp, pBattleDown);

	CSprite *pReverseButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("返回凸"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *pReverseButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("返回凹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bReverseButton = new CSpriteButton(1, D2D1::Point2F(0, 0), pReverseButtonUp, pReverseButtonDown);

	ShowGameSM(false);
	pGamemusic1->SetVisible(false);
	ShowModeSelectionSM(false);
}


// 显示游戏说明
void StartUI::ShowGameSM(bool IsShow)
{
	pGameSm->SetVisible(IsShow);
	bXxButton->SetVisible(IsShow);
}
void StartUI::ShowModeSelectionSM(bool IsShow){

	bSingleButton->SetVisible(IsShow);
	bBattleButton->SetVisible(IsShow);
	bReverseButton->SetVisible(IsShow);
	bKsButton->SetVisible(!IsShow);
	bSmButton->SetVisible(!IsShow);
	bPhButton->SetVisible(!IsShow);
	bTcButton->SetVisible(!IsShow);


}

void StartUI::MusicOpen(bool Open)
{
	//UI显示
	pGamemusic->SetVisible(Open);
	pGamemusic1->SetVisible(!Open);

	////音乐开关
	//if (!Open){
	//	soundPlayer.stop
	//}
}


void StartUI::Exit(){
	PostQuitMessage(0);
}
