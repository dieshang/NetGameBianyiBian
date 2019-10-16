#include "WasteSortingGame.h"


WasteSortingGame::WasteSortingGame(GAME_Mode mode)
{
	nGameMode = mode;
	srand(time(NULL));
	score = 0;
	
	
	
	DropSpeed=1;
	WaitTime=3000;
	//DropSpeed=3.85;
	//WaitTime=580;

	
	
	Init();
	

	if (nGameMode == GAME_Mode::Single){
		GenerateWaste();
	nGameState = GAME_STATE::GAME_START;}
	else{
		MatchWindows(true);
		TScore->SetVisible(false);
		TwoEarthworm->EarthwormsSprite->SetVisible(false); 
		nGameState = GAME_STATE::GAME_Ready;
	}
}


WasteSortingGame::~WasteSortingGame()
{
	CSpritesManager::GetInstance()->DeleteSprite(GameBackground);
	CSpritesManager::GetInstance()->DeleteSprite(pGamemusic);
	CSpritesManager::GetInstance()->DeleteSprite(pGamemusic1);
	CSpritesManager::GetInstance()->DeleteSprite(ClearWindowsBackground);
	TextSpriteManager::GetInstance()->DeleteTextSprite(TScore);
	TextSpriteManager::GetInstance()->DeleteTextSprite(TTipInfo);
	TextSpriteManager::GetInstance()->DeleteTextSprite(BattleTScore);
	TextSpriteManager::GetInstance()->DeleteTextSprite(BattleName);
	delete(bGoBackStartButton);
	delete(bRestartGameButton);
	delete(bExitGameButton);
	delete(bUploadScoreButton);

	delete(TwoEarthworm);
	
}

//初始化
void WasteSortingGame::Init()
{

	GameBackground=CSpritesManager::GetInstance()->CreateSprite(TEXT("背景"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	TwoEarthworm = new Earthworms();
	TwoEarthworm->EarthwormsSprite = CSpritesManager::GetInstance()->CreateAnimationSprite(TEXT("蚯蚓"), 4, 8, D2D1::Point2F(65, 475),386, 141.25);
	TwoEarthworm->EarthwormsSprite->Stop();
	TwoEarthworm->Recoverable =false;

	GameOver = CSpritesManager::GetInstance()->CreateSprite(TEXT("GameOver"), D2D1::Point2F(0, 205), 0, 0, 0, 0);
	GameOver->SetVisible(false);
	EarthwormsDieAnimationSprite = CSpritesManager::GetInstance()->CreateAnimationSprite(TEXT("蚯蚓死亡"), 15, 15, D2D1::Point2F(65, 465), 5790/15, 312/2);
	EarthwormsDieAnimationSprite->SetVisible(false);
	//载入可回收垃圾
	recoverableWasteCount=14;
	recoverableWasteArry=new Waste[recoverableWasteCount];
	recoverableWasteArry[0] = Waste(TEXT("牛奶盒"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("牛奶盒"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[1] = Waste(TEXT("书"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("书"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[2] = Waste(TEXT("易拉罐"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("易拉罐"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[3] = Waste(TEXT("纸杯"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("纸杯"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[4] = Waste(TEXT("报纸"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("报纸"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[5] = Waste(TEXT("罐头盒"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("罐头盒"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[6] = Waste(TEXT("金属餐具"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("金属餐具"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[7] = Waste(TEXT("碎玻璃瓶"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("碎玻璃瓶"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[8] = Waste(TEXT("纸箱"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("纸箱"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
		recoverableWasteArry[9] = Waste(TEXT("磁铁"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("磁铁"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[10] = Waste(TEXT("钉子"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("钉子"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[11] = Waste(TEXT("木板"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("木板"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[12] = Waste(TEXT("泡沫饭盒"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("泡沫饭盒"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[13] = Waste(TEXT("袜子"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("袜子"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	for(int i=0;i<recoverableWasteCount;i++){
		(*(recoverableWasteArry+i)).WasteSprite->SetVisible(false);
	}

	//载入不可回收垃圾
	unrecoverableWasteCount=14;
	unrecoverableWasteArry=new Waste[unrecoverableWasteCount];
	unrecoverableWasteArry[0] = Waste(TEXT("蛋壳"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("蛋壳"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[1] = Waste(TEXT("骨头"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("骨头"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[2] = Waste(TEXT("香蕉皮"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("香蕉皮"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[3] = Waste(TEXT("烟头"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("烟头"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[4] = Waste(TEXT("菜叶"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("菜叶"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[5] = Waste(TEXT("苹果核"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("苹果核"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[6] = Waste(TEXT("枯萎花"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("枯萎花"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[7] = Waste(TEXT("西瓜皮"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("西瓜皮"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[8] = Waste(TEXT("鱼骨头"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("鱼骨头"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[9] = Waste(TEXT("厕纸"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("厕纸"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[10] = Waste(TEXT("蘑菇"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("蘑菇"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[11] = Waste(TEXT("奶酪"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("奶酪"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[12] = Waste(TEXT("破碗"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("破碗"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[13] = Waste(TEXT("油漆桶"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("油漆桶"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		for(int i=0;i<unrecoverableWasteCount;i++){
		(*(unrecoverableWasteArry+i)).WasteSprite->SetVisible(false);
	}
	//音乐开关
	pGamemusic = CSpritesManager::GetInstance()->CreateSprite(TEXT("music"), D2D1::Point2F(435, 5), 0, 0, 0, 0);
	pGamemusic1 = CSpritesManager::GetInstance()->CreateSprite(TEXT("music1"), D2D1::Point2F(435, 5), 0, 0, 0, 0);

	pGamemusic1->SetVisible(false);


	//显示分数
	TScore=TextSpriteManager::GetInstance()->CreateTextSprite(TEXT("0"),D2D1::RectF(230,0,500,200),0xFFFFFF,50);
	TTipInfo=TextSpriteManager::GetInstance()->CreateTextSprite(TEXT("1111"),D2D1::RectF(150,230,370,500),0x000000,25);
	BattleTScore = TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(""), D2D1::RectF(0, 20, 500, 200), 0x000000, 20);
	BattleName = TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(""), D2D1::RectF(0, 0, 500, 200), 0x000000, 20);

	BattleTScore->SetVisible(false);
	BattleName->SetVisible(false);

	CollisionEffects = CSpritesManager::GetInstance()->CreateSprite(TEXT("白框"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	//加载结算图片
	
	ClearWindowsBackground = CSpritesManager::GetInstance()->CreateSprite(TEXT("结算弹窗"), D2D1::Point2F(15, 0), 0, 0, 0, 0);
	

	//结算界面按钮
	//返回游戏主菜单精灵按钮精灵
	
	CSprite *bGoBackStartButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("返回界面凹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *bGoBackStartButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("返回界面凸"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bGoBackStartButton = new CSpriteButton(1, D2D1::Point2F(55, 420), bGoBackStartButtonDown,bGoBackStartButtonUp);
	//上传分数按钮精灵

	CSprite * bUploadScoreButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("上传分数凹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite * bUploadScoreButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("上传分数凸"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bUploadScoreButton = new CSpriteButton(1, D2D1::Point2F(155, 455) ,bUploadScoreButtonDown, bUploadScoreButtonUp);
	// 重新开始游戏
	
	CSprite * bRestartGameButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("重新游戏凹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite * bRestartGameButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("重新游戏凸"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bRestartGameButton = new CSpriteButton(1, D2D1::Point2F(265, 455), bRestartGameButtonDown, bRestartGameButtonUp);
	
	//退出游戏按钮精灵

	CSprite * bExitGameButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("退出游戏凹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite * bExitGameButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("退出游戏凸"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bExitGameButton = new CSpriteButton(1, D2D1::Point2F(360, 420), bExitGameButtonDown, bExitGameButtonUp);

	MatchWindowsBackground = CSpritesManager::GetInstance()->CreateSprite(TEXT("匹配中"), D2D1::Point2F(70, 160), 0, 0, 0, 0);

	CSprite * bCanelUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("取消按钮凸"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite * bCanelDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("取消按钮凹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bMatchWindowsCanelButton = new CSpriteButton(1, D2D1::Point2F(200, 350), bCanelUp, bCanelDown);

	ClaerWindows(false);
	CollisionEffects->SetVisible(false);
	MatchWindows(false);

	//加载音效
	soundPlayer.LoadSound("交换", TEXT("music/交换.wav"));
	soundPlayer.LoadSound("碰撞", TEXT("music/碰撞.wav"));
	soundPlayer.LoadSound("失败", TEXT("music/失败.wav"));
}


// 显示结算窗口
void WasteSortingGame::ClaerWindows(bool IsShow)
{
	ClearWindowsBackground->SetVisible(IsShow);
	bGoBackStartButton->SetVisible(IsShow);
	bUploadScoreButton->SetVisible(IsShow);
	bRestartGameButton->SetVisible(IsShow);
	bExitGameButton->SetVisible(IsShow);
	TTipInfo->SetVisible(IsShow);

	if (IsShow){
		UpdateClearInfo();

		/*wchar_t *a1 = new wchar_t[10];
		wsprintf(a1, L"%d分", score);
		TScore->SetText(a1);*/
		TScore->SetColor(0x000000);
		TScore->SetFontSize(55);
		if(score/10==0)
			TScore->SetRect(D2D1::RectF(240, 100, 500, 200));
		else if(score/100==0&&score/10!=0)
			TScore->SetRect(D2D1::RectF(228, 100, 500, 200));
		else if(score/1000==0&&score/100!=0&&score/10!=0)
			TScore->SetRect(D2D1::RectF(216, 100, 500, 200));
		else
			TScore->SetRect(D2D1::RectF(204, 100, 500, 200));
	}
	else{
		TScore->SetColor(0xFFFFFF);
		TScore->SetFontSize(50);
	TScore->SetRect(D2D1::RectF(230, 0, 500, 200));
	
	}
}


void WasteSortingGame::OpenMusic(bool Open)
{
	//UI显示
	pGamemusic->SetVisible(Open);
	pGamemusic1->SetVisible(!Open);

}

void  WasteSortingGame::MatchWindows(bool IsShow){
	MatchWindowsBackground->SetVisible(IsShow);
	bMatchWindowsCanelButton->SetVisible(IsShow);
}
// 上传分数
int WasteSortingGame::UploadScore()
{
	TTipInfo->SetText(TEXT("上传成功！"));
	return score;

}


// 退出游戏
void WasteSortingGame::ExitGame()
{
		PostQuitMessage(0);
}


// 返回游戏主菜单
void WasteSortingGame::GoBackStartUI()
{
	TScore->SetVisible(false);
	TTipInfo->SetVisible(false);


}


// 更新结算窗口的提示信息
void WasteSortingGame::UpdateClearInfo()
{
	//单人模式
	if (nGameMode == GAME_Mode::Single){
	wchar_t *a3 = new wchar_t[30];
	wchar_t *a1 = new wchar_t[30];
	wchar_t *a2 = new wchar_t[30];
	wsprintf(a1, L"%s属于可回收垃圾，", ResultRecoverable);
	wsprintf(a2, L"%s属于不可回收垃圾。", ResultunRecoverable);
	a3 = wcscat(a1, a2);
	TTipInfo->SetText(a3);}
	//双人模式
	else {
		if (battleScore == score){
			TTipInfo->SetText(TEXT("你们真是旗鼓相当啊！"));
		}
		else if (BattleResult == GAME_result::Win){
		TTipInfo->SetText(TEXT("恭喜你，打败了对手！"));}
		else if (BattleResult == GAME_result::Fail){
			TTipInfo->SetText(TEXT("胜败乃兵家常事，再接再厉吧！"));

		}
		
	}
}


// 重新开始游戏
void WasteSortingGame::RestartGame()
{
	DropSpeed = 1;
		WaitTime = 3000;
	//DropSpeed = 3.85;
	//WaitTime = 600;
		score = 0;
		wchar_t *a1 = new wchar_t[10];
		wsprintf(a1, L"%d", score);
		TScore->SetText(a1);
		nGameState = GAME_STATE::GAME_START;
		GenerateWaste();
		GameOver->SetVisible(false);
		TwoEarthworm->EarthwormsSprite->SetVisible(true);
		EarthwormsDieAnimationSprite->SetVisible(false);
		//隐藏结算窗口
		ClaerWindows(false);


		MatchWindows(false);
		TScore->SetVisible(true);
	
}


// 垃圾掉落
void WasteSortingGame::WasteDrop()
{
		
	
    for(list<Waste>::iterator it = LeftWasteOfScense.begin();it!=LeftWasteOfScense.end();it++){
       (*it).WasteSprite->SetPos(D2D1::Point2F((*it).WasteSprite->GetPos().x,(*it).WasteSprite->GetPos().y + DropSpeed));
    }

	 for(list<Waste>::iterator it =  RightWasteOfScense.begin();it!= RightWasteOfScense.end();it++){
       (*it).WasteSprite->SetPos(D2D1::Point2F((*it).WasteSprite->GetPos().x,(*it).WasteSprite->GetPos().y + DropSpeed));
    }

	
}


// 交换位置
void WasteSortingGame::ChangePosition()
{
	soundPlayer.PlaySound("交换");
	//可回收变不可回收，不可回收变可回收
	TwoEarthworm->Recoverable = !TwoEarthworm->Recoverable;
	//播放相应的动画
	if(TwoEarthworm->Recoverable){
TwoEarthworm->EarthwormsSprite->SetTexPos(0, TwoEarthworm->EarthwormsSprite->GetHeight() * 1);
	TwoEarthworm->EarthwormsSprite->Play(); 

	
	}
	else
	{
	TwoEarthworm->EarthwormsSprite->SetTexPos(0, TwoEarthworm->EarthwormsSprite->GetHeight() * 3);
	TwoEarthworm->EarthwormsSprite->Play(); 
	}

}


// 生成一对垃圾
void WasteSortingGame::GenerateWaste()
{
	int LeftIndex = rand() % recoverableWasteCount;
	int RightIndex = rand() % unrecoverableWasteCount;
	Waste WasteA = Waste(recoverableWasteArry[LeftIndex].WasteName, CSpritesManager::GetInstance()->CreateSprite(recoverableWasteArry[LeftIndex].WasteName, D2D1::Point2F(0, 0), 0, 0, 0, 0), recoverableWasteArry[LeftIndex].Recoverable);
	Waste WasteB = Waste(unrecoverableWasteArry[RightIndex].WasteName, CSpritesManager::GetInstance()->CreateSprite(unrecoverableWasteArry[RightIndex].WasteName, D2D1::Point2F(0, 0), 0, 0, 0, 0), unrecoverableWasteArry[RightIndex].Recoverable);
	//0与1中随机取一个数
	int a = rand() % 2;
	if (a == 0){
		LeftWasteOfScense.push_back(WasteA);
		WasteA.WasteSprite->SetPos(D2D1::Point2F(115, 0));
		WasteA.WasteSprite->SetVisible(true);
		RightWasteOfScense.push_back(WasteB);
		WasteB.WasteSprite->SetPos(D2D1::Point2F(350, 0));
		WasteB.WasteSprite->SetVisible(true);
	}
	else 
	{
		LeftWasteOfScense.push_back(WasteB);
		WasteB.WasteSprite->SetPos(D2D1::Point2F(115, 0));
		WasteB.WasteSprite->SetVisible(true);
		RightWasteOfScense.push_back(WasteA);
		WasteA.WasteSprite->SetPos(D2D1::Point2F(350, 0));
		WasteA.WasteSprite->SetVisible(true);
	}
	t = GetTickCount();
}


// 消灭垃圾
bool WasteSortingGame::EliminateWaste()
{
	bool success = true;
	if (LeftWasteOfScense.front().Recoverable != TwoEarthworm->Recoverable){
		success = false;
		if (LeftWasteOfScense.front().Recoverable)
		{
			wcscpy(ResultRecoverable, LeftWasteOfScense.front().WasteName);
			wcscpy(ResultunRecoverable, RightWasteOfScense.front().WasteName);
			
		}
		else{
			wcscpy(ResultRecoverable, RightWasteOfScense.front().WasteName);
			wcscpy(ResultunRecoverable, LeftWasteOfScense.front().WasteName);
		}
	}
	CSpritesManager::GetInstance()->DeleteSprite(LeftWasteOfScense.front().WasteSprite);
	CSpritesManager::GetInstance()->DeleteSprite(RightWasteOfScense.front().WasteSprite);

	LeftWasteOfScense.pop_front();
	RightWasteOfScense.pop_front();
	
	return success;
}

//每帧更新
int WasteSortingGame::Update(float fDeltaTime)
{
	if (TwoEarthworm->EarthwormsSprite->IsPlaying()){
	if(TwoEarthworm->EarthwormsSprite->GetFrame()==3){
		TwoEarthworm->EarthwormsSprite->Stop();
	}
}
	if (EarthwormsDieAnimationSprite->IsPlaying()){
	if (EarthwormsDieAnimationSprite->GetFrame() == 14){
		EarthwormsDieAnimationSprite->Stop();
	
		//单人模式或对战模式赢了的时候
		if (nGameMode == GAME_Mode::Single || (nGameMode == GAME_Mode::Battle && BattleResult == GAME_result::Win) ){
			ClaerWindows(true);
		}
	}
	}


	if (nGameState == GAME_STATE::GAME_START){
		//碰撞特效
		if (GetTickCount() - EffectsTime > 100){
			CollisionEffects->SetVisible(false);
			EffectsTime = GetTickCount();
		}

		//垃圾产生
	if (GetTickCount() - t > WaitTime)					//延时	
	{
		GenerateWaste();
	}

	WasteDrop();

	if ((TwoEarthworm->EarthwormsSprite->CollideWith(*(LeftWasteOfScense.front().WasteSprite))) || (TwoEarthworm->EarthwormsSprite->CollideWith(*(RightWasteOfScense.front().WasteSprite)))){
		if (EliminateWaste()==false){
			//分类错误
			soundPlayer.PlaySound("失败");
			
			nGameState = GAME_STATE::GAME_OVER;

		

			 for(list<Waste>::iterator it = LeftWasteOfScense.begin();it!=LeftWasteOfScense.end();it++){
       CSpritesManager::GetInstance()->DeleteSprite((*it).WasteSprite);
    }

	 for(list<Waste>::iterator it =  RightWasteOfScense.begin();it!= RightWasteOfScense.end();it++){
     CSpritesManager::GetInstance()->DeleteSprite((*it).WasteSprite);
    }
			LeftWasteOfScense.clear();
			RightWasteOfScense.clear();

			//显示GameOver图片
			GameOver->SetVisible(true);
			//播放死亡动画
			TwoEarthworm->EarthwormsSprite->SetVisible(false);
			EarthwormsDieAnimationSprite->SetVisible(true);
			if (TwoEarthworm->Recoverable){
			
			EarthwormsDieAnimationSprite->SetTexPos(0, EarthwormsDieAnimationSprite->GetHeight() *0);
			EarthwormsDieAnimationSprite->Play();
			}
			else{
				EarthwormsDieAnimationSprite->SetTexPos(0, EarthwormsDieAnimationSprite->GetHeight() * 1);
				EarthwormsDieAnimationSprite->Play();
			}
		
			
		}
		else{

			soundPlayer.PlaySound("碰撞");
	
			//分类正确，增加分数
			score += 10;
		if(score>320){
				DropSpeed+=0.025;
				WaitTime-=1.875;
			}
		else if (score > 310){
			DropSpeed = 3.85;
			WaitTime = 600;
		}
			else if(score>150){
			DropSpeed+=0.05;
			WaitTime-=25;
			}else if(score >50){
			DropSpeed+=0.1;
			WaitTime-=50;
			}
			else if (score<=50){
			DropSpeed+=0.2;
			WaitTime-=300;
			}

			wchar_t *a1 = new wchar_t[10];
			wsprintf(a1, L"%d", score);
			TScore->SetText(a1);
			if (score / 10 == 0)
				TScore->SetRect(D2D1::RectF(230, 0, 500, 200));
			else if (score / 100 == 0 && score / 10 != 0)
				TScore->SetRect(D2D1::RectF(218, 0, 500, 200));
			else if (score / 1000 == 0 && score / 100 != 0 && score / 10 != 0)
				TScore->SetRect(D2D1::RectF(206, 0, 500, 200));
			else
				TScore->SetRect(D2D1::RectF(194, 0, 500, 200));
	

			//特效显示
			CollisionEffects->SetVisible(true);
			EffectsTime = GetTickCount();
			scoreNeedUpdate = true;
		}
	}


}

	
	return 0;
}

void WasteSortingGame::MouseUp(){
		if (nGameState == GAME_STATE::GAME_START){
			ChangePosition();}
}

//键盘按下
void WasteSortingGame::HandleKeyUp(WPARAM wParam, LPARAM lParam){

	if(wParam == VK_SPACE){
	if (nGameState == GAME_STATE::GAME_START){
		ChangePosition();}}
}

void  WasteSortingGame::AlterBattleScore(int so){
	battleScore = so;
	wchar_t *a1 = new wchar_t[10];
	wsprintf(a1, L"对手得分：%d", so);
	BattleTScore->SetText(a1);

}
void  WasteSortingGame::AlterBattleName(WCHAR cName[20]){
	wchar_t *a1 = new wchar_t[10];
	wsprintf(a1, L"对手名称：%s", cName);
	BattleName->SetText(a1);

}

