#include "Tetris.h"



CTetris::CTetris(HINSTANCE hInstance, HWND hWnd, int nFps) :CGame(hInstance, hWnd, nFps)
{

	 PlayMusic=true;

	 //��ʼ���汳��
	CResourcesPool::GetInstance()->AddTexture(TEXT("ksbackground"), TEXT("Images/ksbackground.png"));


	//��ʼ��Ϸ��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("KsButton"), TEXT("Images/KsButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("KsButton1"), TEXT("Images/KsButton1.png"));

	//��Ϸ˵����ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("SmButton"), TEXT("Images/SmButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("SmButton1"), TEXT("Images/SmButton1.png"));

	//�鿴���а�ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("PhButton"), TEXT("Images/PhButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("PhButton1"), TEXT("Images/PhButton1.png"));

	//�˳���Ϸ��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("TcButton"), TEXT("Images/TcButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("TcButton1"), TEXT("Images/TcButton1.png"));

	//������ս��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("������ս"), TEXT("Images/������ս.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("������ս��"), TEXT("Images/������ս��.png"));
	//�˳���Ϸ��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("˫��PK��"), TEXT("Images/˫��PK��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("˫��PK͹"), TEXT("Images/˫��PK͹.png"));

	//���ز˵���Ϸ��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("����͹"), TEXT("Images/����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("���ذ�"), TEXT("Images/����2.png"));
	//����
	CResourcesPool::GetInstance()->AddTexture(TEXT("music"), TEXT("Images/music.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("music1"), TEXT("Images/music1.png"));

	//��Ϸ˵��
	CResourcesPool::GetInstance()->AddTexture(TEXT("gameSm"), TEXT("Images/gameSm.png"));

	//�˳���ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("XxButton"), TEXT("Images/ExitButton.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("XxButton1"), TEXT("Images/ExitButton1.png"));
		//����ͼƬ
	CResourcesPool::GetInstance()->AddTexture(TEXT("���"), TEXT("Images/WasteSortingGame/Earthworms.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("�������"), TEXT("Images/WasteSortingGame/die.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("GameOver"), TEXT("Images/WasteSortingGame/gameover.png"));
	//����ͼƬ
	CResourcesPool::GetInstance()->AddTexture(TEXT("����"), TEXT("Images/WasteSortingGame/����.jpg"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("�׿�"), TEXT("Images/WasteSortingGame/�߱ߵİ׿�.png"));
	//�ɻ�������
	CResourcesPool::GetInstance()->AddTexture(TEXT("ţ�̺�"), TEXT("Images/WasteSortingGame/Waste/recoverable/ţ�̺�.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("��"), TEXT("Images/WasteSortingGame/Waste/recoverable/��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("������"), TEXT("Images/WasteSortingGame/Waste/recoverable/������.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("ֽ��"), TEXT("Images/WasteSortingGame/Waste/recoverable/ֽ��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("��ֽ"), TEXT("Images/WasteSortingGame/Waste/recoverable/��ֽ.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("��ͷ��"), TEXT("Images/WasteSortingGame/Waste/recoverable/��ͷ��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("�����;�"), TEXT("Images/WasteSortingGame/Waste/recoverable/�����;�.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("�鲣��ƿ"), TEXT("Images/WasteSortingGame/Waste/recoverable/�鲣��ƿ.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("ֽ��"), TEXT("Images/WasteSortingGame/Waste/recoverable/ֽ��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("����"), TEXT("Images/WasteSortingGame/Waste/recoverable/����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("����"), TEXT("Images/WasteSortingGame/Waste/recoverable/����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("ľ��"), TEXT("Images/WasteSortingGame/Waste/recoverable/ľ��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("��ĭ����"), TEXT("Images/WasteSortingGame/Waste/recoverable/��ĭ����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("����"), TEXT("Images/WasteSortingGame/Waste/recoverable/����.png"));
		//���ɻ�������
	CResourcesPool::GetInstance()->AddTexture(TEXT("����"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("��ͷ"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/��ͷ.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("�㽶Ƥ"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/�㽶Ƥ.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("��ͷ"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/��ͷ.png"));
		CResourcesPool::GetInstance()->AddTexture(TEXT("��Ҷ"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/��Ҷ.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("��ή��"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/��ή��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("ƻ����"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/ƻ����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("����Ƥ"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/����Ƥ.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("���ͷ"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/���ͷ.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("��ֽ"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/��ֽ.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("Ģ��"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/Ģ��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("����"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("����"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("����Ͱ"), TEXT("Images/WasteSortingGame/Waste/unrecoverable/����Ͱ.png"));

	CResourcesPool::GetInstance()->AddTexture(TEXT("loginUIBg"), TEXT("Images/loginUIBg.png"));
	//��һ��logo
	CResourcesPool::GetInstance()->AddTexture(TEXT("LOGO"), TEXT("Images/LOGO.png"));
	//�οͰ�ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("EnterButton"), TEXT("Images/TouristButton.png"));
	//��¼��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("LoginButton"), TEXT("Images/LoginButton.png"));
	//��¼����
	CResourcesPool::GetInstance()->AddTexture(TEXT("PasswordEntryBox"), TEXT("Images/PasswordEntryBox.png"));
	//�˳���ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("ExitButton"), TEXT("Images/ExitButton.png"));

	//�οͰ���״̬��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("EnterButton1"), TEXT("Images/TouristButton1.png"));
	//��¼����״̬��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("LoginButton1"), TEXT("Images/LoginButton1.png"));
	//�˳�����״̬��ť
	CResourcesPool::GetInstance()->AddTexture(TEXT("ExitButton1"), TEXT("Images/ExitButton1.png"));

	CResourcesPool::GetInstance()->AddTexture(TEXT("���ؽ��氼"), TEXT("Images/WasteSortingGame/���ؽ��氼.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("���ؽ���͹"), TEXT("Images/WasteSortingGame/���ؽ���͹.png"));
		CResourcesPool::GetInstance()->AddTexture(TEXT("�ϴ�������"), TEXT("Images/WasteSortingGame/�ϴ�������.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("�ϴ�����͹"), TEXT("Images/WasteSortingGame/�ϴ�����͹.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("������Ϸ��"), TEXT("Images/WasteSortingGame/������Ϸ��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("������Ϸ͹"), TEXT("Images/WasteSortingGame/������Ϸ͹.png"));
		CResourcesPool::GetInstance()->AddTexture(TEXT("�˳���Ϸ��"), TEXT("Images/WasteSortingGame/�˳���Ϸ��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("�˳���Ϸ͹"), TEXT("Images/WasteSortingGame/�˳���Ϸ͹.png"));

	CResourcesPool::GetInstance()->AddTexture(TEXT("���㵯��"), TEXT("Images/WasteSortingGame/���㵯��.png"));	

	

	CResourcesPool::GetInstance()->AddTexture(TEXT("���а��"), TEXT("Images/���а����/���а����.png"));	


	CResourcesPool::GetInstance()->AddTexture(TEXT("ƥ����"), TEXT("Images/WasteSortingGame/ƥ�䴰��/ƥ����.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("ȡ����ť��"), TEXT("Images/WasteSortingGame/ƥ�䴰��/ȡ����ť��.png"));
	CResourcesPool::GetInstance()->AddTexture(TEXT("ȡ����ť͹"), TEXT("Images/WasteSortingGame/ƥ�䴰��/ȡ����ť͹.png"));
	//��������
	soundPlayer.LoadSound("��ť", TEXT("music/��ť.wav"));
	soundPlayer.LoadSound("ʧ��", TEXT("music/ʧ��.wav"));
	soundPlayer.LoadSound("��ײ", TEXT("music/��ײ.wav"));
	
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
		//����������ͻ�ȡ���а���Ϣ����
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
		//�����������ƥ��������Ϣ
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
		//���������͸�������
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
		//�����������ƥ��������Ϣ
		Msg_Sock g;
		g.dwType = MSGID_Match;
		g.nLen = sizeof(struct Msg_Sock);
		g.s = MyInfo->s;
		SendMsg((char*)&g, g.nLen);}
		}

	if (pWasteSortingGame->bMatchWindowsCanelButton->HandleMouseUp(wParam, lParam)){

		//�����������ȡ��ƥ����Ϣ
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
			soundPlayer.PlaySound("��ť");
			
		}
		if (pLoginUI->ExitButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pLoginUI->btnEnter->HandleMouseDown(wParam, lParam)){
            soundPlayer.PlaySound("��ť");
		}
		

	}


	if (pStartUI){
		if (pStartUI->bReverseButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pStartUI->bKsButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pStartUI->bSmButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pStartUI->bPhButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pStartUI->bTcButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pStartUI->bXxButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pStartUI->bSingleButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pStartUI->bBattleButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
	}

	if(pRankingList){
		if (pRankingList->bGoBackStartButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
	}

	if (pWasteSortingGame){
		if (pWasteSortingGame->bGoBackStartButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}
		if (pWasteSortingGame->bMatchWindowsCanelButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}

		if (pWasteSortingGame->bExitGameButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}


		if (pWasteSortingGame->bUploadScoreButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}


		if (pWasteSortingGame->bRestartGameButton->HandleMouseDown(wParam, lParam)){
			soundPlayer.PlaySound("��ť");
		}

	}
}

void CTetris::InitGame()
{
	




pLoginUI = new LoginUI(hInstance, hWnd); //������¼UI����ʾ
	
	pStartUI = NULL;
	pWasteSortingGame = NULL;
	pRankingList = NULL;


}
void CTetris::Update(float fDeltaTime)
{
	CGame::Update(fDeltaTime);

	if (pWasteSortingGame){
		pWasteSortingGame->Update(fDeltaTime);
	
	//����Ϸ��ʼ�ſ�ʼ������Ϸ������Ʒּ������Ƿ����
		if (pWasteSortingGame->nGameMode == GAME_Mode::Battle&&pWasteSortingGame->nGameState != GAME_STATE::GAME_Ready)
{
	
//���û��÷���������Ϣ����������ͨ��������֪ͨ�����ͻ���
			if (pWasteSortingGame->scoreNeedUpdate)
			{
				/*WCHAR temp[100];
				wsprintf(temp, TEXT("���ӵ÷�%d\r\n"), nAddScore);
				OutputDebugStringW(temp);*/
				Msg_Score myScore;
				myScore.dwType = MSGID_SCORE;
				myScore.nLen = sizeof(struct Msg_Score);
				myScore.nScore = pWasteSortingGame->score;
				//�����׽���
				myScore.s = CompetitorInfo.s;
				SendMsg((char*)&myScore, myScore.nLen);
				pWasteSortingGame->scoreNeedUpdate = false;
	}
			//��Ϸʧ��
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
		MessageBox(NULL, TEXT("������δ����"), TEXT("OK"), 0);
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
	wsprintf(tchar, TEXT("����˹رջ������Ͽ��������ǵ����ӡ�"), s);
	closesocket(s);

}



// һ�������ϵĶ��������
void CTetris::OnRead(SOCKET s, char *pBuffer, int nLen)
{
	WCHAR tmp[200];
	Msg_Generic* pGenericMsg = (Msg_Generic*)pBuffer;
	switch (pGenericMsg->dwType) // �ж��յ�����Ϣ����
	{
	case MSGID_SCORE:
	{
						Msg_Score *pScore = (Msg_Score*)pBuffer;
						//���¶��ַ���
						pWasteSortingGame->AlterBattleScore(pScore->nScore);
	}
		break;
		//���а�
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
	//ƥ��ɹ�
	case MSGID_MatchSucceed:
	{
			 Msg_Player*Matchs = (Msg_Player*)pBuffer;
			 wcscpy(CompetitorInfo.cName, Matchs->player.cName);
			 CompetitorInfo.s=Matchs->player.s;
		

			 //��ʼ��Ϸ
			pWasteSortingGame-> RestartGame();
			pWasteSortingGame->BattleTScore->SetVisible(true);
			pWasteSortingGame->BattleName->SetVisible(true);
			pWasteSortingGame->AlterBattleName(CompetitorInfo.cName);
			pWasteSortingGame->AlterBattleScore(0);
			pWasteSortingGame->BattleResult = GAME_result::Fail;
			needSendFail = true;
	}break;
	//����ʧ��
	case MSGID_FAILED:
	{ Msg_Score* pFailed = (Msg_Score*)pBuffer;
		//��Ҳʧ����
			if( pWasteSortingGame->nGameState==GAME_STATE::GAME_OVER){
				//if (pFailed->nScore == pWasteSortingGame->score){
				//	//ƽ��
				//	pWasteSortingGame->BattleResult = GAME_result::dogfall;
				//}

				//����ʾ���㴰��
				pWasteSortingGame->ClaerWindows(true);
			}
			else{
				
					//ʤ��
					pWasteSortingGame->BattleResult = GAME_result::Win;
			
			}
	}
		break;

	case MSGID_PLAYER_SELF:  //��¼�ɹ�ʱ�յ��Լ����û���Ϣ
	{
		struct Msg_Player* pSelf = (struct Msg_Player*)pBuffer;

	
		MyInfo = new PlayerInfo();
		wsprintf(MyInfo->cName, pSelf->player.cName);
		MyInfo->s = pSelf->player.s;


	}
		break;
	
	}

}

