#include "Tetris.h"



CTetris::CTetris(HINSTANCE hInstance, HWND hWnd, int nFps) :CGame(hInstance, hWnd, nFps)
{

	 PlayMusic=true;

	 //开始界面背景
	CResourcesPool::GetInstance()->AddTexture(TEXT("ksbackground"), TEXT("Images/ksbackground.png"));


	//开始游戏按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("KsButton"), TEXT("Images/KsButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("KsButton1"), TEXT("Images/KsButton1.png"));

	//游戏说明按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("SmButton"), TEXT("Images/SmButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("SmButton1"), TEXT("Images/SmButton1.png"));

	//查看排行榜按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("PhButton"), TEXT("Images/PhButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("PhButton1"), TEXT("Images/PhButton1.png"));

	//退出游戏按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("TcButton"), TEXT("Images/TcButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("TcButton1"), TEXT("Images/TcButton1.png"));

	//单人挑战按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("单人挑战"), TEXT("Images/单人挑战.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("单人挑战凹"), TEXT("Images/单人挑战凹.png"));
	//退出游戏按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("双人PK凹"), TEXT("Images/双人PK凹.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("双人PK凸"), TEXT("Images/双人PK凸.png"));

	//返回菜单游戏按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("返回凸"), TEXT("Images/返回.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("返回凹"), TEXT("Images/返回2.png"));
	//音乐
	CResourcesPool::GetInstance()->AddTexture(TEXT("music"), TEXT("Images/music.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("music1"), TEXT("Images/music1.png"));

	//游戏说明
	CResourcesPool::GetInstance()->AddTexture(TEXT("gameSm"), TEXT("Images/gameSm.png"));

	//退出按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("XxButton"), TEXT("Images/ExitButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("XxButton1"), TEXT("Images/ExitButton1.png"));
		//加载图片
	CResourcesPool::GetInstance()->AddTexture(TEXT("蚯蚓"), TEXT("Images/WasteSortingGame/Earthworms.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("蚯蚓死亡"), TEXT("Images/WasteSortingGame/die.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("GameOver"), TEXT("Images/WasteSortingGame/gameover.png"));
	//加载图片
	CResourcesPool::GetInstance()->AddTexture(TEXT("背景"), TEXT("Images/WasteSortingGame/背景.jpg"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("白框"), TEXT("Images/WasteSortingGame/边边的白框.png"));
	//可回收垃圾
	CResourcesPool::GetInstance()->AddTexture(TEXT("牛奶盒"), TEXT("Images/WasteSortingGame/Waste/recoverable/牛奶盒.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("书"), TEXT("Images/WasteSortingGame/Waste/recoverable/书.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("易拉罐"), TEXT("Images/WasteSortingGame/Waste/recoverable/易拉罐.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("纸杯"), TEXT("Images/WasteSortingGame/Waste/recoverable/纸杯.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("报纸"), TEXT("Images/WasteSortingGame/Waste/recoverable/报纸.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("罐头盒"), TEXT("Images/WasteSortingGame/Waste/recoverable/罐头盒.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("金属餐具"), TEXT("Images/WasteSortingGame/Waste/recoverable/金属餐具.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("碎玻璃瓶"), TEXT("Images/WasteSortingGame/Waste/recoverable/碎玻璃瓶.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("纸箱"), TEXT("Images/WasteSortingGame/Waste/recoverable/纸箱.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("磁铁"), TEXT("Images/WasteSortingGame/Waste/recoverable/磁铁.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("钉子"), TEXT("Images/WasteSortingGame/Waste/recoverable/钉子.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("木板"), TEXT("Images/WasteSortingGame/Waste/recoverable/木板.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("泡沫饭盒"), TEXT("Images/WasteSortingGame/Waste/recoverable/泡沫饭盒.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("袜子"), TEXT("Images/WasteSortingGame/Waste/recoverable/袜子.png"));
		//不可回收垃圾
	CResourcesPool::GetInstance()->AddTexture(TEXT("蛋壳"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/蛋壳.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("骨头"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/骨头.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("香蕉皮"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/香蕉皮.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("烟头"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/烟头.png"));
		CResourcesPool::GetInstance()->AddTexture(TEXT("菜叶"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/菜叶.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("枯萎花"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/枯萎花.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("苹果核"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/苹果骸.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("西瓜皮"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/西瓜皮.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("鱼骨头"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/鱼骨头.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("厕纸"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/厕纸.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("蘑菇"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/蘑菇.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("奶酪"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/奶酪.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("破碗"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/破碗.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("油漆桶"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/油漆桶.png"));

	CResourcesPool::GetInstance()->AddTexture(TEXT("loginUIBg"), TEXT("Images/loginUIBg.png"));
	//辨一辨logo
	CResourcesPool::GetInstance()->AddTexture(TEXT("LOGO"), TEXT("Images/LOGO.png"));
	//游客按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("EnterButton"), TEXT("Images/TouristButton.png"));
	//登录按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("LoginButton"), TEXT("Images/LoginButton.png"));
	//登录弹窗
	CResourcesPool::GetInstance()->AddTexture(TEXT("PasswordEntryBox"), TEXT("Images/PasswordEntryBox.png"));
	//退出按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("ExitButton"), TEXT("Images/ExitButton.png"));

	//游客按下状态按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("EnterButton1"), TEXT("Images/TouristButton1.png"));
	//登录按下状态按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("LoginButton1"), TEXT("Images/LoginButton1.png"));
	//退出按下状态按钮
	CResourcesPool::GetInstance()->AddTexture(TEXT("ExitButton1"), TEXT("Images/ExitButton1.png"));

	CResourcesPool::GetInstance()->AddTexture(TEXT("返回界面凹"), TEXT("Images/WasteSortingGame/返回界面凹.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("返回界面凸"), TEXT("Images/WasteSortingGame/返回界面凸.png"));
		CResourcesPool::GetInstance()->AddTexture(TEXT("上传分数凹"), TEXT("Images/WasteSortingGame/上传分数凹.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("上传分数凸"), TEXT("Images/WasteSortingGame/上传分数凸.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("重新游戏凹"), TEXT("Images/WasteSortingGame/重新游戏凹.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("重新游戏凸"), TEXT("Images/WasteSortingGame/重新游戏凸.png"));
		CResourcesPool::GetInstance()->AddTexture(TEXT("退出游戏凹"), TEXT("Images/WasteSortingGame/退出游戏凹.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("退出游戏凸"), TEXT("Images/WasteSortingGame/退出游戏凸.png"));

	CResourcesPool::GetInstance()->AddTexture(TEXT("结算弹窗"), TEXT("Images/WasteSortingGame/结算弹窗.png"));	

	

	CResourcesPool::GetInstance()->AddTexture(TEXT("排行榜框"), TEXT("Images/排行榜界面/排行榜界面.png"));	


	CResourcesPool::GetInstance()->AddTexture(TEXT("匹配中"), TEXT("Images/WasteSortingGame/匹配窗口/匹配中.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("取消按钮凹"), TEXT("Images/WasteSortingGame/匹配窗口/取消按钮凹.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("取消按钮凸"), TEXT("Images/WasteSortingGame/匹配窗口/取消按钮凸.png"));
	//加载声音
	soundPlayer.LoadSound("按钮", TEXT("music/按钮.wav"));
	soundPlayer.LoadSound("失败", TEXT("music/失败.wav"));
	soundPlayer.LoadSound("碰撞", TEXT("music/碰撞.wav"));
	
	soundPlayer.LoadSound("bgm", TEXT("music/bgm_01.wav"));
	soundPlayer.PlaySound("bgm");


}

CTetris::~CTetris(void)
{
}

void CTetris::HandleMouseUp(WPARAM wParam, LPARAM lParam)
{
	if (pLoginUI)
	{
		if (pLoginUI->btnEnter->HandleMouseUp(wParam, lParam)){
		pLoginUI->LoginWindow(true);
		return;
		}
		if (pLoginUI->ExitButton->HandleMouseUp(wParam, lParam)){
			pLoginUI->LoginWindow(false);
		}
		if (pLoginUI->btnLogin->HandleMouseUp(wParam, lParam))
		{
			if (pLoginUI->btnLogin->btnState == BtnUp)
			{
				WCHAR *tmp = new WCHAR[200];
				GlobalData *globalData = GlobalData::GetInstance();
				GetWindowText(pLoginUI->hName, tmp, 200);
				wcscpy(globalData->username, tmp);
				GetWindowText(pLoginUI->hPwd, tmp, 200);
				wcscpy(globalData->password, tmp);
				InitSocket(hWnd);
				ConnectServer("127.0.0.1", 8000);
			}
		}
	}

	

	if (pStartUI){

		
	
	if(	pStartUI->bPhButton->HandleMouseUp(wParam, lParam)){
			delete(pStartUI);
		pStartUI = NULL;
		pRankingList = new RankingList();
		//向服务器发送获取排行榜信息请求
		Msg_Sock g;
		g.dwType = MSGID_RankingList;
		g.nLen = sizeof(struct Msg_Sock);
		g.s = MyInfo->s;
		SendMsg((char*)&g, g.nLen);
		return;
	}
		if(pStartUI->bTcButton->HandleMouseUp(wParam, lParam)){
			if(pStartUI->bXxButton->GetVisible()==false){
				pStartUI->Exit();}
		}
	

		if (pStartUI->bSmButton->HandleMouseUp(wParam, lParam)){
			
			pStartUI->ShowGameSM(true);
		
		}

	if (pStartUI->bXxButton->HandleMouseUp(wParam, lParam)){
		
				pStartUI->ShowGameSM(false);
			}

	if (pStartUI->pGamemusic1->IsSelected(LOWORD(lParam), HIWORD(lParam))){

			if (PlayMusic){
				pStartUI->MusicOpen(false);
				PlayMusic = false;
				soundPlayer.StopSound("bgm");
			}
			else{

				pStartUI->MusicOpen(true);
				PlayMusic = true;
				soundPlayer.PlaySound("bgm");

				
			}
		}
	if (pStartUI->bSingleButton->HandleMouseUp(wParam, lParam)){

		
			delete(pStartUI);
			pStartUI = NULL;
			pWasteSortingGame = new WasteSortingGame(GAME_Mode::Single);

			return;
		
	}

	if (pStartUI->bReverseButton->HandleMouseUp(wParam, lParam)){
		pStartUI->ShowModeSelectionSM(false);
	
	}

	if (pStartUI->bKsButton->HandleMouseUp(wParam, lParam)){
	pStartUI->ShowModeSelectionSM(true);
	return;
	}


	if (pStartUI->bBattleButton->HandleMouseUp(wParam, lParam)){
		delete(pStartUI);
		pStartUI = NULL;
		pWasteSortingGame = new WasteSortingGame(GAME_Mode::Battle);
		//向服务器发送匹配请求消息
		Msg_Sock g;
		g.dwType = MSGID_Match;
		g.nLen = sizeof(struct Msg_Sock);
		g.s = MyInfo->s;
		SendMsg((char*)&g, g.nLen);
		

		return;
	}
	}

	if(pRankingList){
		if(pRankingList->bGoBackStartButton->HandleMouseUp(wParam, lParam)){
		delete(pRankingList);
		pRankingList = NULL;
		pStartUI = new StartUI();
		}
	
	}

	if (pWasteSortingGame){
		pWasteSortingGame->MouseUp();

		if (pWasteSortingGame->pGamemusic1->IsSelected(LOWORD(lParam), HIWORD(lParam))){
		if (PlayMusic){
				pWasteSortingGame->OpenMusic(false);
				PlayMusic = false;
			}
			else{

				pWasteSortingGame->OpenMusic(true);
				PlayMusic = true;
			}}


		if(pWasteSortingGame->bExitGameButton->HandleMouseUp(wParam, lParam)){
			pWasteSortingGame->ExitGame();
		}
	
		if (pWasteSortingGame->bUploadScoreButton->HandleMouseUp(wParam, lParam)){
		//将分数发送给服务器
		Msg_Score MyScore;
		MyScore.dwType = MSGID_UpLoadScore;
		MyScore.nLen = sizeof(struct Msg_Score);
		MyScore.nScore = pWasteSortingGame->UploadScore();
		MyScore.s =MyInfo->s;
		SendMsg((char*)&MyScore, MyScore.nLen);
		}
	
	if(pWasteSortingGame->bRestartGameButton->HandleMouseUp(wParam, lParam)){
		if (pWasteSortingGame->nGameMode == GAME_Mode::Single){
		pWasteSortingGame->RestartGame();}
		if (pWasteSortingGame->nGameMode == GAME_Mode::Battle){
			delete(pWasteSortingGame);
			pWasteSortingGame = NULL;
			pWasteSortingGame = new WasteSortingGame(GAME_Mode::Battle);
		//向服务器发送匹配请求消息
		Msg_Sock g;
		g.dwType = MSGID_Match;
		g.nLen = sizeof(struct Msg_Sock);
		g.s = MyInfo->s;
		SendMsg((char*)&g, g.nLen);}
		}

	if (pWasteSortingGame->bMatchWindowsCanelButton->HandleMouseUp(wParam, lParam)){

		//向服务器发送取消匹配消息
		Msg_Sock g;
		g.dwType = MSGID_MatchCanel;
		g.nLen = sizeof(struct Msg_Sock);
		g.s = MyInfo->s;
		SendMsg((char*)&g, g.nLen);
	}
		
	if (pWasteSortingGame->bGoBackStartButton->HandleMouseUp(wParam, lParam) || pWasteSortingGame->bMatchWindowsCanelButton->HandleMouseUp(wParam, lParam)){
			pWasteSortingGame->GoBackStartUI();
		delete(pWasteSortingGame);
		pWasteSortingGame = NULL;
		pStartUI = new StartUI();
		

		}
	}
}
void CTetris::HandleMouseDown(WPARAM wParam, LPARAM lParam)
{
	if (pLoginUI)
	{
		if (pLoginUI->btnLogin->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
			
		}
		if (pLoginUI->ExitButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pLoginUI->btnEnter->HandleMouseDown(wParam, lParam)){
            soundPlayer.PlaySound("按钮");
		}
		

	}


	if (pStartUI){
		if (pStartUI->bReverseButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pStartUI->bKsButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pStartUI->bSmButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pStartUI->bPhButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pStartUI->bTcButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pStartUI->bXxButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pStartUI->bSingleButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pStartUI->bBattleButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
	}

	if(pRankingList){
		if (pRankingList->bGoBackStartButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
	}

	if (pWasteSortingGame){
		if (pWasteSortingGame->bGoBackStartButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}
		if (pWasteSortingGame->bMatchWindowsCanelButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}

		if (pWasteSortingGame->bExitGameButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}


		if (pWasteSortingGame->bUploadScoreButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}


		if (pWasteSortingGame->bRestartGameButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("按钮");
		}

	}
}

void CTetris::InitGame()
{
	




pLoginUI = new LoginUI(hInstance, hWnd); //创建登录UI并显示
	
	pStartUI = NULL;
	pWasteSortingGame = NULL;
	pRankingList = NULL;


}
void CTetris::Update(float fDeltaTime)
{
	CGame::Update(fDeltaTime);

	if (pWasteSortingGame){
		pWasteSortingGame->Update(fDeltaTime);
	
	//当游戏开始才开始进行游戏交互与计分及计算是否结束
		if (pWasteSortingGame->nGameMode == GAME_Mode::Battle&&pWasteSortingGame->nGameState != GAME_STATE::GAME_Ready)
{
	
//当用户得分增加则发消息给服务器及通过服务器通知其它客户端
			if (pWasteSortingGame->scoreNeedUpdate)
			{
				/*WCHAR temp[100];
				wsprintf(temp, TEXT("增加得分%d\r\n"), nAddScore);
				OutputDebugStringW(temp);*/
				Msg_Score myScore;
				myScore.dwType = MSGID_SCORE;
				myScore.nLen = sizeof(struct Msg_Score);
				myScore.nScore = pWasteSortingGame->score;
				//对手套接字
				myScore.s = CompetitorInfo.s;
				SendMsg((char*)&myScore, myScore.nLen);
				pWasteSortingGame->scoreNeedUpdate = false;
	}
			//游戏失败
			if (pWasteSortingGame->nGameState == GAME_STATE::GAME_OVER&&needSendFail){
				Msg_Score g;
				g.dwType = MSGID_FAILED;
				g.nLen = sizeof(struct Msg_Score);
				g.s = CompetitorInfo.s;
				g.nScore = pWasteSortingGame->score;
				SendMsg((char*)&g, g.nLen);
				needSendFail = false;
			}

		

		}
	}
	
}
void CTetris::HandleKeyUp(WPARAM wParam, LPARAM lParam)
{
	if (pWasteSortingGame){
		pWasteSortingGame->HandleKeyUp(wParam,lParam);
	}
	
}






void CTetris::OnConnect(LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam) != 0)
	{
		bConnected = false;
		MessageBox(NULL, TEXT("服务器未开放"), TEXT("OK"), 0);
	}
	else
	{


		delete(pLoginUI);
		pLoginUI = NULL;
		bConnected = true;

	
		Msg_Login myLogin;
		myLogin.dwType = MSGID_LOGIN;
		myLogin.nLen = sizeof(myLogin);
		GlobalData *globalData = GlobalData::GetInstance();

		wcscpy(myLogin.cName, globalData->username);
		wcscpy(myLogin.cPwd, globalData->password);
		SendMsg((char*)&myLogin, myLogin.nLen);

		pStartUI = new StartUI();

	}
}

void CTetris::OnClose(SOCKET s)
{

	WCHAR tchar[MSG_SIZE];
	wsprintf(tchar, TEXT("服务端关闭或主动断开了与我们的连接。"), s);
	closesocket(s);

}



// 一个连接上的读操作完成
void CTetris::OnRead(SOCKET s, char *pBuffer, int nLen)
{
	WCHAR tmp[200];
	Msg_Generic* pGenericMsg = (Msg_Generic*)pBuffer;
	switch (pGenericMsg->dwType) // 判断收到的消息类型
	{
	case MSGID_SCORE:
	{
						Msg_Score *pScore = (Msg_Score*)pBuffer;
						//更新对手分数
						pWasteSortingGame->AlterBattleScore(pScore->nScore);
	}
		break;
		//排行榜
	case  MSGID_RankingList:
	{
		Msg_Ranking*rank = (Msg_Ranking*)pBuffer;
		switch (rank->Place)
		{
		case 1:
			pRankingList->WritePrize(1, rank->cName, rank->nScore);
			break;
		case 2:
			pRankingList->WritePrize(2, rank->cName, rank->nScore);
			break;
		case 3:
			pRankingList->WritePrize(3, rank->cName, rank->nScore);
			break;
		case 4:
			pRankingList->WritePrize(4, rank->cName, rank->nScore);
			break;
		case 5:
			pRankingList->WritePrize(5, rank->cName, rank->nScore);
			break;
		}
	}
	break;
	//匹配成功
	case MSGID_MatchSucceed:
	{
			 Msg_Player*Matchs = (Msg_Player*)pBuffer;
			 wcscpy(CompetitorInfo.cName, Matchs->player.cName);
			 CompetitorInfo.s=Matchs->player.s;
		

			 //开始游戏
			pWasteSortingGame-> RestartGame();
			pWasteSortingGame->BattleTScore->SetVisible(true);
			pWasteSortingGame->BattleName->SetVisible(true);
			pWasteSortingGame->AlterBattleName(CompetitorInfo.cName);
			pWasteSortingGame->AlterBattleScore(0);
			pWasteSortingGame->BattleResult = GAME_result::Fail;
			needSendFail = true;
	}break;
	//对手失败
	case MSGID_FAILED:
	{ Msg_Score* pFailed = (Msg_Score*)pBuffer;
		//我也失败了
			if( pWasteSortingGame->nGameState==GAME_STATE::GAME_OVER){
				//if (pFailed->nScore == pWasteSortingGame->score){
				//	//平局
				//	pWasteSortingGame->BattleResult = GAME_result::dogfall;
				//}

				//就显示结算窗口
				pWasteSortingGame->ClaerWindows(true);
			}
			else{
				
					//胜利
					pWasteSortingGame->BattleResult = GAME_result::Win;
			
			}
	}
		break;

	case MSGID_PLAYER_SELF:  //登录成功时收到自己的用户信息
	{
		struct Msg_Player* pSelf = (struct Msg_Player*)pBuffer;

	
		MyInfo = new PlayerInfo();
		wsprintf(MyInfo->cName, pSelf->player.cName);
		MyInfo->s = pSelf->player.s;


	}
		break;
	
	}

}

