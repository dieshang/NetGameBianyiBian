#pragma once
#include "Common.h"
#include "MsgDefine.h"

#define WM_SOCKET WM_USER+1 //网络消息类型


class CTCPServer
{
private:
	SOCKET  sListen;            //定义监听套接字
	int nHalfMsgLen;
	char msgBuffer[MSG_SIZE * 2];
public:
	CTCPServer(void);
	~CTCPServer(void);
	
	HWND hwndWin;
	HWND hwndEdit;
	void InitSocket(HWND hWin);  //初始化函数
	LRESULT WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL StartServer(short port);//开始服务器
	BOOL Release();              //关闭服务器


	void CopyRemainMsg(char *pBuffer, int nLen, int nRemainLen);
	void SplitMsg(SOCKET s,char *pBuffer, int nLen);
	
protected:
	bool bCreate;      //是否已经连接
	// 连接完成
	virtual void OnAccept(SOCKET s,struct sockaddr_in addr){}
	// 一个连接关闭
	virtual void OnClose(SOCKET s){}
	// 收到数据包时解析出一条消息
	virtual void OnRead(SOCKET s,char *pBuffer,int nLen){}	

	
};