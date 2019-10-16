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
	SetWindowTextW(hwndEdit,bigchar);//显示聊天字符串
	int ChatEditLineCount=SendMessage(hwndEdit,EM_GETLINECOUNT,0,0);	//得到一共多少行
	SendMessage(hwndEdit,EM_LINESCROLL,0,ChatEditLineCount);     //实现滚动到最后一行
}

void CGame::OnAccept(SOCKET sClient,struct sockaddr_in addr)
{
		//sClientList.push_back(sClient);
		WCHAR tchar[MSG_SIZE];
		wsprintf(tchar, TEXT("IP%S连接成功,套按字为:%d"), inet_ntoa(addr.sin_addr), sClient);
		ShowText(tchar);
}

void CGame::OnClose(SOCKET s)
{
	PlayerInfo *player = GetPlayer(s);
	WCHAR tchar[MSG_SIZE];
	wsprintf(tchar, TEXT("用户%s退出了游戏。"), player->cName);
	
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
	switch (pGenericMsg->dwType)//判断消息包类型
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
		 if (rsSign->adoEOF)//如果不存在该用户名
		 {
			 sqlStr.Format(TEXT("INSERT INTO [user]([Name],[Score]) VALUES ('%s',%d)"), cName1, score);
		  ADOObj->insert(sqlStr);
		 }
		 //将用户名cName，分数score写入数据库
		 else{
			int oldScore = (_variant_t)rsSign->GetCollect("Score").intVal;
			if (score>oldScore)//如果上传的分数大于数据库里的分数
			{//更新数据库里的分数
			 sqlStr.Format(_T("update [user] set Score=%d where Name='%s'"), score, cName1);
			 ADOObj->update(sqlStr);
		 }
		 }
		//rsSign->Close();//关闭记录集
	}
		
		break;
		//排行榜消息
	case 	MSGID_RankingList:{
		  CString sqlStr;
		  CString nqlStr;
		 
			
		 _RecordsetPtr rsSign = m_pRecordset.CreateInstance(__uuidof(Recordset));
		 Msg_Sock*rank = (Msg_Sock*)pBuffer;
			 Msg_Ranking pScore[200];
			//获取列数
			 nqlStr.Format(TEXT("SELECT  COUNT(*) FROM [user]"));
			 rsSign= ADOObj->search(nqlStr);
			 int Datacount = rsSign->GetCollect((_variant_t(long(0)))).intVal;
			//从数据库中读取分数与名称并赋值给cName1与score
			 for (int i = 0; i < Datacount; i++){
				 sqlStr.Format(TEXT("SELECT * FROM [user] WHERE Id=%d"), i+1);
			 rsSign = ADOObj->search(sqlStr);
			 if (!rsSign->adoEOF){
				 pScore[i].nScore = (_variant_t)rsSign->GetCollect("Score").intVal;
				 wcscpy(pScore[i].cName,rsSign->GetCollect("Name").bstrVal);
		
			 }
			 }
			 //排序
			 sort(pScore, pScore + Datacount, cmp);

			 //发前五
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
	  //MatchSock数目只可能为0，1，2
	  //匹配中的人数大于等于2时
	  if (MatchSock.size() >= 2){
		//互发对手的信息
		  Msg_Player matchsuc;
		  matchsuc.nLen = sizeof(matchsuc);
		  matchsuc.dwType = MSGID_MatchSucceed;
		  wcscpy(matchsuc.player.cName,GetPlayer(MatchSock[0])->cName);
		  matchsuc.player.s = GetPlayer(MatchSock[0])->s;
		 
		  SendMsg((char*)&matchsuc, matchsuc.nLen, MatchSock[1]);
		 

		  wcscpy(matchsuc.player.cName, GetPlayer(MatchSock[1])->cName);
		  matchsuc.player.s = GetPlayer(MatchSock[1])->s;
		
		  SendMsg((char*)&matchsuc, matchsuc.nLen, MatchSock[0]);

		  //从匹配列表中移除
		  MatchSock.pop_front();
		  MatchSock.pop_front();


	  }

	}
		break;

	//取消匹配
	case MSGID_MatchCanel:
	{

		Msg_Sock*CanelMatch = (Msg_Sock*)pBuffer;
		//将该客户端套接字从匹配队列中删掉
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



			////向服务器其它玩家发送有新用户登录的用户信息
			Msg_Player newPlayer;
		
			newPlayer.nLen = sizeof(newPlayer);
			memcpy(&newPlayer.player, playerInfo, sizeof(struct PlayerInfo));
		

			//向当前玩家发送当前玩家自己的用户信息
			newPlayer.dwType = MSGID_PLAYER_SELF;
			SendMsg((char*)&newPlayer, newPlayer.nLen,s);

			//将当前用户信息存入用户信息列表
			AddPlayer(s, playerInfo);
			int a;
			a = 1;

	}
		break;
	}
}

//发送信息给在线所有用户
int CGame::SendMsg(char* buf, int len)
{
	std::map<int, PlayerInfo*>::iterator iter;
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		send(iter->first, buf, len, 0);
	}
	return 0;
}

//发送信息给某个客户端
int CGame::SendMsg(char* buffer, int len, int sockid)
{
	int n = send(sockid, buffer, len, 0);
	return n;
}

//发送信息给除了某个客户端外的其它所有客户端
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

BOOL  CGame::Release()         //关闭服务器
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

//添加新客户端玩家信息
void CGame::AddPlayer(int s, struct PlayerInfo *player)
{
	clientMap.insert(std::make_pair(s, player));
}

//删除找到的客户端玩家信息
void CGame::DeletePlayer(int s)
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	iter = clientMap.find(s);
	if (iter != clientMap.end()) {
		SAFE_DELETE(iter->second);
		clientMap.erase(iter);
	}
}

//根据套接字ID获取一个用户信息
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


//用ADO连接SQL数据库
bool CGame::AdoConnect()
{
	CString strSQL;    //配置初始连接串
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


//清空玩家用户列表
void CGame::ClearClientMap()
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	clientMap.clear();
	if (clientMap.empty()) {
		printf("clientMap清空了\n");
	}
}


