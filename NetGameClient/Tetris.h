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
	
	// 连接完成
	void OnConnect(LPARAM lParam);
	// 一个连接关闭
	void OnClose(SOCKET s);
	// 一个连接上的读操作完成
	void OnRead(SOCKET s, char *pBuffer, int nLen);

	LoginUI* pLoginUI;
	StartUI *pStartUI;
	WasteSortingGame *pWasteSortingGame;
	RankingList *pRankingList;


	XAudio2SoundPlayer   soundPlayer;
	bool needSendFail;
	
private:
	std::map<int, PlayerInfo*> clientMap; //玩家信息集合

	std::map<int, TextSprite*> playerTextSpriteMap;

	//我的信息
	PlayerInfo* MyInfo;
	//匹配到的对手的信息
	PlayerInfo CompetitorInfo;


	
	bool PlayMusic;

	int nGameState;

	
	
private:
	
};
