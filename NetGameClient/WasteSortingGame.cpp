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

//��ʼ��
void WasteSortingGame::Init()
{

	GameBackground=CSpritesManager::GetInstance()->CreateSprite(TEXT("����"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	TwoEarthworm = new Earthworms();
	TwoEarthworm->EarthwormsSprite = CSpritesManager::GetInstance()->CreateAnimationSprite(TEXT("���"), 4, 8, D2D1::Point2F(65, 475),386, 141.25);
	TwoEarthworm->EarthwormsSprite->Stop();
	TwoEarthworm->Recoverable =false;

	GameOver = CSpritesManager::GetInstance()->CreateSprite(TEXT("GameOver"), D2D1::Point2F(0, 205), 0, 0, 0, 0);
	GameOver->SetVisible(false);
	EarthwormsDieAnimationSprite = CSpritesManager::GetInstance()->CreateAnimationSprite(TEXT("�������"), 15, 15, D2D1::Point2F(65, 465), 5790/15, 312/2);
	EarthwormsDieAnimationSprite->SetVisible(false);
	//����ɻ�������
	recoverableWasteCount=14;
	recoverableWasteArry=new Waste[recoverableWasteCount];
	recoverableWasteArry[0] = Waste(TEXT("ţ�̺�"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("ţ�̺�"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[1] = Waste(TEXT("��"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[2] = Waste(TEXT("������"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("������"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[3] = Waste(TEXT("ֽ��"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("ֽ��"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[4] = Waste(TEXT("��ֽ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��ֽ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[5] = Waste(TEXT("��ͷ��"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��ͷ��"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[6] = Waste(TEXT("�����;�"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("�����;�"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[7] = Waste(TEXT("�鲣��ƿ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("�鲣��ƿ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[8] = Waste(TEXT("ֽ��"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("ֽ��"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
		recoverableWasteArry[9] = Waste(TEXT("����"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("����"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[10] = Waste(TEXT("����"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("����"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[11] = Waste(TEXT("ľ��"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("ľ��"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[12] = Waste(TEXT("��ĭ����"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��ĭ����"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	recoverableWasteArry[13] = Waste(TEXT("����"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("����"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), true);
	for(int i=0;i<recoverableWasteCount;i++){
		(*(recoverableWasteArry+i)).WasteSprite->SetVisible(false);
	}

	//���벻�ɻ�������
	unrecoverableWasteCount=14;
	unrecoverableWasteArry=new Waste[unrecoverableWasteCount];
	unrecoverableWasteArry[0] = Waste(TEXT("����"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("����"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[1] = Waste(TEXT("��ͷ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��ͷ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[2] = Waste(TEXT("�㽶Ƥ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("�㽶Ƥ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[3] = Waste(TEXT("��ͷ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��ͷ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[4] = Waste(TEXT("��Ҷ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��Ҷ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[5] = Waste(TEXT("ƻ����"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("ƻ����"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[6] = Waste(TEXT("��ή��"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��ή��"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[7] = Waste(TEXT("����Ƥ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("����Ƥ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
	unrecoverableWasteArry[8] = Waste(TEXT("���ͷ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("���ͷ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[9] = Waste(TEXT("��ֽ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("��ֽ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[10] = Waste(TEXT("Ģ��"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("Ģ��"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[11] = Waste(TEXT("����"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("����"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[12] = Waste(TEXT("����"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("����"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		unrecoverableWasteArry[13] = Waste(TEXT("����Ͱ"), (CSpritesManager::GetInstance()->CreateSprite(TEXT("����Ͱ"), D2D1::Point2F(0, 0), 0, 0, 0, 0)), false);
		for(int i=0;i<unrecoverableWasteCount;i++){
		(*(unrecoverableWasteArry+i)).WasteSprite->SetVisible(false);
	}
	//���ֿ���
	pGamemusic = CSpritesManager::GetInstance()->CreateSprite(TEXT("music"), D2D1::Point2F(435, 5), 0, 0, 0, 0);
	pGamemusic1 = CSpritesManager::GetInstance()->CreateSprite(TEXT("music1"), D2D1::Point2F(435, 5), 0, 0, 0, 0);

	pGamemusic1->SetVisible(false);


	//��ʾ����
	TScore=TextSpriteManager::GetInstance()->CreateTextSprite(TEXT("0"),D2D1::RectF(230,0,500,200),0xFFFFFF,50);
	TTipInfo=TextSpriteManager::GetInstance()->CreateTextSprite(TEXT("1111"),D2D1::RectF(150,230,370,500),0x000000,25);
	BattleTScore = TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(""), D2D1::RectF(0, 20, 500, 200), 0x000000, 20);
	BattleName = TextSpriteManager::GetInstance()->CreateTextSprite(TEXT(""), D2D1::RectF(0, 0, 500, 200), 0x000000, 20);

	BattleTScore->SetVisible(false);
	BattleName->SetVisible(false);

	CollisionEffects = CSpritesManager::GetInstance()->CreateSprite(TEXT("�׿�"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	//���ؽ���ͼƬ
	
	ClearWindowsBackground = CSpritesManager::GetInstance()->CreateSprite(TEXT("���㵯��"), D2D1::Point2F(15, 0), 0, 0, 0, 0);
	

	//������水ť
	//������Ϸ���˵����鰴ť����
	
	CSprite *bGoBackStartButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("���ؽ��氼"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite *bGoBackStartButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("���ؽ���͹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bGoBackStartButton = new CSpriteButton(1, D2D1::Point2F(55, 420), bGoBackStartButtonDown,bGoBackStartButtonUp);
	//�ϴ�������ť����

	CSprite * bUploadScoreButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("�ϴ�������"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite * bUploadScoreButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("�ϴ�����͹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bUploadScoreButton = new CSpriteButton(1, D2D1::Point2F(155, 455) ,bUploadScoreButtonDown, bUploadScoreButtonUp);
	// ���¿�ʼ��Ϸ
	
	CSprite * bRestartGameButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("������Ϸ��"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite * bRestartGameButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("������Ϸ͹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bRestartGameButton = new CSpriteButton(1, D2D1::Point2F(265, 455), bRestartGameButtonDown, bRestartGameButtonUp);
	
	//�˳���Ϸ��ť����

	CSprite * bExitGameButtonUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("�˳���Ϸ��"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite * bExitGameButtonDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("�˳���Ϸ͹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bExitGameButton = new CSpriteButton(1, D2D1::Point2F(360, 420), bExitGameButtonDown, bExitGameButtonUp);

	MatchWindowsBackground = CSpritesManager::GetInstance()->CreateSprite(TEXT("ƥ����"), D2D1::Point2F(70, 160), 0, 0, 0, 0);

	CSprite * bCanelUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("ȡ����ť͹"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	CSprite * bCanelDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("ȡ����ť��"), D2D1::Point2F(0, 0), 0, 0, 0, 0);
	bMatchWindowsCanelButton = new CSpriteButton(1, D2D1::Point2F(200, 350), bCanelUp, bCanelDown);

	ClaerWindows(false);
	CollisionEffects->SetVisible(false);
	MatchWindows(false);

	//������Ч
	soundPlayer.LoadSound("����", TEXT("music/����.wav"));
	soundPlayer.LoadSound("��ײ", TEXT("music/��ײ.wav"));
	soundPlayer.LoadSound("ʧ��", TEXT("music/ʧ��.wav"));
}


// ��ʾ���㴰��
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
		wsprintf(a1, L"%d��", score);
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
	//UI��ʾ
	pGamemusic->SetVisible(Open);
	pGamemusic1->SetVisible(!Open);

}

void  WasteSortingGame::MatchWindows(bool IsShow){
	MatchWindowsBackground->SetVisible(IsShow);
	bMatchWindowsCanelButton->SetVisible(IsShow);
}
// �ϴ�����
int WasteSortingGame::UploadScore()
{
	TTipInfo->SetText(TEXT("�ϴ��ɹ���"));
	return score;

}


// �˳���Ϸ
void WasteSortingGame::ExitGame()
{
		PostQuitMessage(0);
}


// ������Ϸ���˵�
void WasteSortingGame::GoBackStartUI()
{
	TScore->SetVisible(false);
	TTipInfo->SetVisible(false);


}


// ���½��㴰�ڵ���ʾ��Ϣ
void WasteSortingGame::UpdateClearInfo()
{
	//����ģʽ
	if (nGameMode == GAME_Mode::Single){
	wchar_t *a3 = new wchar_t[30];
	wchar_t *a1 = new wchar_t[30];
	wchar_t *a2 = new wchar_t[30];
	wsprintf(a1, L"%s���ڿɻ���������", ResultRecoverable);
	wsprintf(a2, L"%s���ڲ��ɻ���������", ResultunRecoverable);
	a3 = wcscat(a1, a2);
	TTipInfo->SetText(a3);}
	//˫��ģʽ
	else {
		if (battleScore == score){
			TTipInfo->SetText(TEXT("������������൱����"));
		}
		else if (BattleResult == GAME_result::Win){
		TTipInfo->SetText(TEXT("��ϲ�㣬����˶��֣�"));}
		else if (BattleResult == GAME_result::Fail){
			TTipInfo->SetText(TEXT("ʤ���˱��ҳ��£��ٽ������ɣ�"));

		}
		
	}
}


// ���¿�ʼ��Ϸ
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
		//���ؽ��㴰��
		ClaerWindows(false);


		MatchWindows(false);
		TScore->SetVisible(true);
	
}


// ��������
void WasteSortingGame::WasteDrop()
{
		
	
    for(list<Waste>::iterator it = LeftWasteOfScense.begin();it!=LeftWasteOfScense.end();it++){
       (*it).WasteSprite->SetPos(D2D1::Point2F((*it).WasteSprite->GetPos().x,(*it).WasteSprite->GetPos().y + DropSpeed));
    }

	 for(list<Waste>::iterator it =  RightWasteOfScense.begin();it!= RightWasteOfScense.end();it++){
       (*it).WasteSprite->SetPos(D2D1::Point2F((*it).WasteSprite->GetPos().x,(*it).WasteSprite->GetPos().y + DropSpeed));
    }

	
}


// ����λ��
void WasteSortingGame::ChangePosition()
{
	soundPlayer.PlaySound("����");
	//�ɻ��ձ䲻�ɻ��գ����ɻ��ձ�ɻ���
	TwoEarthworm->Recoverable = !TwoEarthworm->Recoverable;
	//������Ӧ�Ķ���
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


// ����һ������
void WasteSortingGame::GenerateWaste()
{
	int LeftIndex = rand() % recoverableWasteCount;
	int RightIndex = rand() % unrecoverableWasteCount;
	Waste WasteA = Waste(recoverableWasteArry[LeftIndex].WasteName, CSpritesManager::GetInstance()->CreateSprite(recoverableWasteArry[LeftIndex].WasteName, D2D1::Point2F(0, 0), 0, 0, 0, 0), recoverableWasteArry[LeftIndex].Recoverable);
	Waste WasteB = Waste(unrecoverableWasteArry[RightIndex].WasteName, CSpritesManager::GetInstance()->CreateSprite(unrecoverableWasteArry[RightIndex].WasteName, D2D1::Point2F(0, 0), 0, 0, 0, 0), unrecoverableWasteArry[RightIndex].Recoverable);
	//0��1�����ȡһ����
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


// ��������
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

//ÿ֡����
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
	
		//����ģʽ���սģʽӮ�˵�ʱ��
		if (nGameMode == GAME_Mode::Single || (nGameMode == GAME_Mode::Battle && BattleResult == GAME_result::Win) ){
			ClaerWindows(true);
		}
	}
	}


	if (nGameState == GAME_STATE::GAME_START){
		//��ײ��Ч
		if (GetTickCount() - EffectsTime > 100){
			CollisionEffects->SetVisible(false);
			EffectsTime = GetTickCount();
		}

		//��������
	if (GetTickCount() - t > WaitTime)					//��ʱ	
	{
		GenerateWaste();
	}

	WasteDrop();

	if ((TwoEarthworm->EarthwormsSprite->CollideWith(*(LeftWasteOfScense.front().WasteSprite))) || (TwoEarthworm->EarthwormsSprite->CollideWith(*(RightWasteOfScense.front().WasteSprite)))){
		if (EliminateWaste()==false){
			//�������
			soundPlayer.PlaySound("ʧ��");
			
			nGameState = GAME_STATE::GAME_OVER;

		

			 for(list<Waste>::iterator it = LeftWasteOfScense.begin();it!=LeftWasteOfScense.end();it++){
       CSpritesManager::GetInstance()->DeleteSprite((*it).WasteSprite);
    }

	 for(list<Waste>::iterator it =  RightWasteOfScense.begin();it!= RightWasteOfScense.end();it++){
     CSpritesManager::GetInstance()->DeleteSprite((*it).WasteSprite);
    }
			LeftWasteOfScense.clear();
			RightWasteOfScense.clear();

			//��ʾGameOverͼƬ
			GameOver->SetVisible(true);
			//������������
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

			soundPlayer.PlaySound("��ײ");
	
			//������ȷ�����ӷ���
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
	

			//��Ч��ʾ
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

//���̰���
void WasteSortingGame::HandleKeyUp(WPARAM wParam, LPARAM lParam){

	if(wParam == VK_SPACE){
	if (nGameState == GAME_STATE::GAME_START){
		ChangePosition();}}
}

void  WasteSortingGame::AlterBattleScore(int so){
	battleScore = so;
	wchar_t *a1 = new wchar_t[10];
	wsprintf(a1, L"���ֵ÷֣�%d", so);
	BattleTScore->SetText(a1);

}
void  WasteSortingGame::AlterBattleName(WCHAR cName[20]){
	wchar_t *a1 = new wchar_t[10];
	wsprintf(a1, L"�������ƣ�%s", cName);
	BattleName->SetText(a1);

}

