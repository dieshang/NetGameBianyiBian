#include "Game.h"

CGame::CGame(void)
{
	
}

CGame::~CGame(void)
{
}

void CGame::InitGame(HWND h)
{
	this->hwndEdit=h;
	AdoConnect();


}
void CGame::ShowText(WCHAR *p)
{

	wcscat(bigchar, p);
	wcscat(bigchar, TEXT("\r\n"));
	SetWindowTextW(hwndEdit,bigchar);//��ʾ�����ַ���
	int ChatEditLineCount=SendMessage(hwndEdit,EM_GETLINECOUNT,0,0);	//�õ�һ��������
	SendMessage(hwndEdit,EM_LINESCROLL,0,ChatEditLineCount);     //ʵ�ֹ��������һ��
}

void CGame::OnAccept(SOCKET sClient,struct sockaddr_in addr)
{
		//sClientList.push_back(sClient);
		WCHAR tchar[MSG_SIZE];
		wsprintf(tchar, TEXT("IP%S���ӳɹ�,�װ���Ϊ:%d"), inet_ntoa(addr.sin_addr), sClient);
		ShowText(tchar);
}

void CGame::OnClose(SOCKET s)
{
	PlayerInfo *player = GetPlayer(s);
	WCHAR tchar[MSG_SIZE];
	wsprintf(tchar, TEXT("�û�%s�˳�����Ϸ��"), player->cName);
	
	Msg_Player_Delete playerDelete;
	playerDelete.dwType = MSGID_PLAYER_DELETE;
	playerDelete.nLen = sizeof(playerDelete);
	playerDelete.s = player->s;
	SendMsg((char*)&playerDelete, sizeof(playerDelete));

	DeletePlayer(s);
}



void CGame::OnRead(SOCKET s, char *pBuffer, int nLen)
{
	Msg_Generic *pGenericMsg = (Msg_Generic *)pBuffer;
	switch (pGenericMsg->dwType)//�ж���Ϣ������
	{
	case MSGID_UpLoadScore:
	{
	     _RecordsetPtr rsSign = m_pRecordset.CreateInstance(__uuidof(Recordset));
		 Msg_Score*pScore = (Msg_Score*)pBuffer;
		 WCHAR cName1[20];
		 CString sqlStr;
		
		 wcscpy(cName1, GetPlayer(pScore->s)->cName);
		 int score = pScore->nScore;
		 sqlStr.Format(TEXT("SELECT * FROM [user] WHERE Name='%s'"), cName1);
		 rsSign = ADOObj->search(sqlStr);
		 if (rsSign->adoEOF)//��������ڸ��û���
		 {
			 sqlStr.Format(TEXT("INSERT INTO [user]([Name],[Score]) VALUES ('%s',%d)"), cName1, score);
		  ADOObj->insert(sqlStr);
		 }
		 //���û���cName������scoreд�����ݿ�
		 else{
			int oldScore = (_variant_t)rsSign->GetCollect("Score").intVal;
			if (score>oldScore)//����ϴ��ķ����������ݿ���ķ���
			{//�������ݿ���ķ���
			 sqlStr.Format(_T("update [user] set Score=%d where Name='%s'"), score, cName1);
			 ADOObj->update(sqlStr);
		 }
		 }
		//rsSign->Close();//�رռ�¼��
	}
		
		break;
		//���а���Ϣ
	case 	MSGID_RankingList:{
		  CString sqlStr;
		  CString nqlStr;
		 
			
		 _RecordsetPtr rsSign = m_pRecordset.CreateInstance(__uuidof(Recordset));
		 Msg_Sock*rank = (Msg_Sock*)pBuffer;
			 Msg_Ranking pScore[200];
			//��ȡ����
			 nqlStr.Format(TEXT("SELECT  COUNT(*) FROM [user]"));
			 rsSign= ADOObj->search(nqlStr);
			 int Datacount = rsSign->GetCollect((_variant_t(long(0)))).intVal;
			//�����ݿ��ж�ȡ���������Ʋ���ֵ��cName1��score
			 for (int i = 0; i < Datacount; i++){
				 sqlStr.Format(TEXT("SELECT * FROM [user] WHERE Id=%d"), i+1);
			 rsSign = ADOObj->search(sqlStr);
			 if (!rsSign->adoEOF){
				 pScore[i].nScore = (_variant_t)rsSign->GetCollect("Score").intVal;
				 wcscpy(pScore[i].cName,rsSign->GetCollect("Name").bstrVal);
		
			 }
			 }
			 //����
			 sort(pScore, pScore + Datacount, cmp);

			 //��ǰ��
			 for (int i = 0; i < 5; i++){
				 pScore[i].dwType = MSGID_RankingList;
				 pScore[i].nLen = sizeof(struct Msg_Ranking);
				 pScore[i].Place = i + 1;
				 SendMsg((char*)&pScore[i], pScore[i].nLen, rank->s);
}
	}
		break;
	case 	MSGID_Match:
	{
	  Msg_Sock*Match = (Msg_Sock*)pBuffer;
	  MatchSock.push_back(Match->s);
	  //MatchSock��Ŀֻ����Ϊ0��1��2
	  //ƥ���е��������ڵ���2ʱ
	  if (MatchSock.size() >= 2){
		//�������ֵ���Ϣ
		  Msg_Player matchsuc;
		  matchsuc.nLen = sizeof(matchsuc);
		  matchsuc.dwType = MSGID_MatchSucceed;
		  wcscpy(matchsuc.player.cName,GetPlayer(MatchSock[0])->cName);
		  matchsuc.player.s = GetPlayer(MatchSock[0])->s;
		 
		  SendMsg((char*)&matchsuc, matchsuc.nLen, MatchSock[1]);
		 

		  wcscpy(matchsuc.player.cName, GetPlayer(MatchSock[1])->cName);
		  matchsuc.player.s = GetPlayer(MatchSock[1])->s;
		
		  SendMsg((char*)&matchsuc, matchsuc.nLen, MatchSock[0]);

		  //��ƥ���б����Ƴ�
		  MatchSock.pop_front();
		  MatchSock.pop_front();


	  }

	}
		break;

	//ȡ��ƥ��
	case MSGID_MatchCanel:
	{

		Msg_Sock*CanelMatch = (Msg_Sock*)pBuffer;
		//���ÿͻ����׽��ִ�ƥ�������ɾ��
			for (deque<int>::iterator it = MatchSock.begin(); it != MatchSock.end(); it++){
				if ((*it) == CanelMatch->s){
					MatchSock.erase(it);
					break;
				}
			}
			

						  

	}
		break;
	case MSGID_FAILED:
	{
		 Msg_Score* pFailed = (Msg_Score*)pBuffer;
		SendMsg(pBuffer, nLen, pFailed->s);
	}
		break;
	case MSGID_SCORE:
	{
		Msg_Score *pScore = (Msg_Score*)pBuffer;
		SendMsg(pBuffer, nLen, pScore->s);
	

	}
		break;
	case MSGID_LOGIN:
	{
			struct Msg_Login *pLogin = (struct Msg_Login*)pBuffer;
			
	
			PlayerInfo *playerInfo = new PlayerInfo();
		
			wcscpy(playerInfo->cName, pLogin->cName);
			playerInfo->s = s;



			////�������������ҷ��������û���¼���û���Ϣ
			Msg_Player newPlayer;
		
			newPlayer.nLen = sizeof(newPlayer);
			memcpy(&newPlayer.player, playerInfo, sizeof(struct PlayerInfo));
		

			//��ǰ��ҷ��͵�ǰ����Լ����û���Ϣ
			newPlayer.dwType = MSGID_PLAYER_SELF;
			SendMsg((char*)&newPlayer, newPlayer.nLen,s);

			//����ǰ�û���Ϣ�����û���Ϣ�б�
			AddPlayer(s, playerInfo);
			int a;
			a = 1;

	}
		break;
	}
}

//������Ϣ�����������û�
int CGame::SendMsg(char* buf, int len)
{
	std::map<int, PlayerInfo*>::iterator iter;
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		send(iter->first, buf, len, 0);
	}
	return 0;
}

//������Ϣ��ĳ���ͻ���
int CGame::SendMsg(char* buffer, int len, int sockid)
{
	int n = send(sockid, buffer, len, 0);
	return n;
}

//������Ϣ������ĳ���ͻ�������������пͻ���
int CGame::SendMsgExceptSelf(char *buf, int len, int s)
{
	std::map<int, PlayerInfo*>::iterator iter;
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		if (iter->first != s) {
			send(iter->first, buf, len, 0);
		}
	}
	return 0;
}

BOOL  CGame::Release()         //�رշ�����
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	clientMap.clear();
	CTCPServer::Release();
	return true;
}

//����¿ͻ��������Ϣ
void CGame::AddPlayer(int s, struct PlayerInfo *player)
{
	clientMap.insert(std::make_pair(s, player));
}

//ɾ���ҵ��Ŀͻ��������Ϣ
void CGame::DeletePlayer(int s)
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	iter = clientMap.find(s);
	if (iter != clientMap.end()) {
		SAFE_DELETE(iter->second);
		clientMap.erase(iter);
	}
}

//�����׽���ID��ȡһ���û���Ϣ
PlayerInfo* CGame::GetPlayer(int s)
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	iter = clientMap.find(s);
	if (iter != clientMap.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}


//��ADO����SQL���ݿ�
bool CGame::AdoConnect()
{
	CString strSQL;    //���ó�ʼ���Ӵ�
	strSQL = "Provider=Microsoft.Jet.OleDb.4.0;Data Source=data.mdb;";
	ADOObj = new CADO();
	ADOObj->openDB(strSQL, "", "", "Microsoft.Jet.OleDb.4.0");
	return true;

}

bool CGame::AdoClose()
{
	delete ADOObj;
	return true;
}


//�������û��б�
void CGame::ClearClientMap()
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	clientMap.clear();
	if (clientMap.empty()) {
		printf("clientMap�����\n");
	}
}


