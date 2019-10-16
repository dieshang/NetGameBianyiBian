#pragma once
#include <windows.h>
#include "Framework\SpritesManager.h"
#include "Framework\ResourcesPool.h"
#include "Framework\Game.h"
#include "Framework\TextSpriteManager.h"
#include "Framework\SpriteButton.h"

class StartUI
{
public:
	StartUI();
	~StartUI();
	void Init();
	// 显示游戏说明
	void ShowGameSM(bool IsShow);
	//显示模式选择
	void ShowModeSelectionSM(bool IsShow);
	void MusicOpen(bool Open);
	void Exit();
	CSpriteButton *bKsButton;
	CSpriteButton *bSmButton;
	CSpriteButton *bPhButton;
	CSpriteButton *bTcButton;
	CSpriteButton *bXxButton;
	CSprite* pGamemusic;
	CSprite* pGamemusic1;
	CSpriteButton *bSingleButton;
	CSpriteButton *bBattleButton;
	CSpriteButton *bReverseButton;

	
private:
	CSprite* pGameBackGround;
	CSprite* pGameSm;
};

