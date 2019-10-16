#pragma once
#include <iostream>
using namespace std;


#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "MsgDefine.h"
#define WM_SOCKET WM_USER+1 //������Ϣ����
#define MSG_SIZE 2048

class CTCPClient
{
private:
	int nHalfMsgLen;
	char msgBuffer[MSG_SIZE * 2];
public:
	CTCPClient(void);
	~CTCPClient(void);
	void InitSocket(HWND hwnd);  //��ʼ������
	LRESULT WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL	ConnectServer(char *ipaddr,short port);//��ʼ���ӷ�����
	BOOL	Release();         //�رշ�����
	int  SendMsg(char* pBuffer, UINT lLength);
	
	void CopyRemainMsg(char *pBuffer, int nLen, int nRemainLen);
	void SplitMsg(SOCKET s, char *pBuffer, int nLen);
protected:
	SOCKET	sClient;  //���������׽���
	bool bConnected;      //�Ƿ��Ѿ�����
	// �������
	virtual void OnConnect(LPARAM lParam){}
	// һ�����ӹر�
	virtual void OnClose(SOCKET s){}
	// һ�������ϵĶ��������
	virtual void OnRead(SOCKET s,char *pBuffer,int nLen){}	

};