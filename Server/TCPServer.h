#pragma once
#include "Common.h"
#include "MsgDefine.h"

#define WM_SOCKET WM_USER+1 //������Ϣ����


class CTCPServer
{
private:
	SOCKET  sListen;            //��������׽���
	int nHalfMsgLen;
	char msgBuffer[MSG_SIZE * 2];
public:
	CTCPServer(void);
	~CTCPServer(void);
	
	HWND hwndWin;
	HWND hwndEdit;
	void InitSocket(HWND hWin);  //��ʼ������
	LRESULT WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL StartServer(short port);//��ʼ������
	BOOL Release();              //�رշ�����


	void CopyRemainMsg(char *pBuffer, int nLen, int nRemainLen);
	void SplitMsg(SOCKET s,char *pBuffer, int nLen);
	
protected:
	bool bCreate;      //�Ƿ��Ѿ�����
	// �������
	virtual void OnAccept(SOCKET s,struct sockaddr_in addr){}
	// һ�����ӹر�
	virtual void OnClose(SOCKET s){}
	// �յ����ݰ�ʱ������һ����Ϣ
	virtual void OnRead(SOCKET s,char *pBuffer,int nLen){}	

	
};