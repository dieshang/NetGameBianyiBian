#pragma once
#include "framework\game.h"
#include "TCPClient.h"

#include "LoginUI.h"
#include"StartUI.h"
#include"WasteSortingGame.h"
#include"RankingList.h"
#include "GlobalData.h"
#include "Framework\XAudio2SoundPlayer.h"





#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
class CTetris : public CGame,public CTCPClient
{
public:



	CTetris(HINSTANCE hInstance,HWND hWnd,int nFps = 0);
	~CTetris(void);
	void InitGame();
	void HandleKeyUp(WPARAM wParam,LPARAM lParam);
	void HandleMouseUp(WPARAM wParam, LPARAM lParam);
	void HandleMouseDown(WPARAM wParam, LPARAM lParam);

	
	
	void Update(float fDeltaTime);	

protected:
	
	// �������
	void OnConnect(LPARAM lParam);
	// һ�����ӹر�
	void OnClose(SOCKET s);
	// һ�������ϵĶ��������
	void OnRead(SOCKET s, char *pBuffer, int nLen);

	LoginUI* pLoginUI;
	StartUI *pStartUI;
	WasteSortingGame *pWasteSortingGame;
	RankingList *pRankingList;


	XAudio2SoundPlayer   soundPlayer;
	bool needSendFail;
	
private:
	std::map<int, PlayerInfo*> clientMap; //�����Ϣ����

	std::map<int, TextSprite*> playerTextSpriteMap;

	//�ҵ���Ϣ
	PlayerInfo* MyInfo;
	//ƥ�䵽�Ķ��ֵ���Ϣ
	PlayerInfo CompetitorInfo;


	
	bool PlayMusic;

	int nGameState;

	
	
private:
	
};
