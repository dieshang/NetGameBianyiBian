#pragma once
#include <iostream>
using namespace std;


#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "MsgDefine.h"
#define WM_SOCKET WM_USER+1 //网络消息类型
#define MSG_SIZE 2048

class CTCPClient
{
private:
	int nHalfMsgLen;
	char msgBuffer[MSG_SIZE * 2];
public:
	CTCPClient(void);
	~CTCPClient(void);
	void InitSocket(HWND hwnd);  //初始化函数
	LRESULT WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL	ConnectServer(char *ipaddr,short port);//开始连接服务器
	BOOL	Release();         //关闭服务器
	int  SendMsg(char* pBuffer, UINT lLength);
	
	void CopyRemainMsg(char *pBuffer, int nLen, int nRemainLen);
	void SplitMsg(SOCKET s, char *pBuffer, int nLen);
protected:
	SOCKET	sClient;  //定义数据套接字
	bool bConnected;      //是否已经连接
	// 连接完成
	virtual void OnConnect(LPARAM lParam){}
	// 一个连接关闭
	virtual void OnClose(SOCKET s){}
	// 一个连接上的读操作完成
	virtual void OnRead(SOCKET s,char *pBuffer,int nLen){}	

};