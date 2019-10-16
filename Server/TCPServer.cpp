#include "TCPServer.h"

CTCPServer::CTCPServer()  //��ʼ������
{
	sListen=NULL;
	bCreate=false;
	ZeroMemory(msgBuffer, MSG_SIZE * 2);
	nHalfMsgLen = 0;
}
CTCPServer::~CTCPServer()  //��������
{
	Release();
}

void CTCPServer::InitSocket(HWND hWin)  //��ʼ������
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	sListen=socket(AF_INET,SOCK_STREAM,0); 
	hwndWin = hWin;
	WSAAsyncSelect(sListen,hWin,WM_SOCKET, FD_ACCEPT | FD_CLOSE  ) ;
}

BOOL CTCPServer::StartServer(short port)//��ʼ������
{
	if(!bCreate)//��������û������
	{
		SOCKADDR_IN ServerAddr;
		ServerAddr.sin_family = AF_INET;
		ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		ServerAddr.sin_port = htons(port);
		bind(sListen,(struct sockaddr*)&ServerAddr,sizeof(ServerAddr));
		listen(sListen,5);
		bCreate=true;
		return true;
	}

	return false;//���������Ѿ�����
}

BOOL  CTCPServer::Release()         //�رշ�����
{
	closesocket(sListen);

	WSACleanup();
	return true;
}



LRESULT CTCPServer::WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:	//lParamΪ���ӷ������Ϣ
		{
		SOCKET sClient;
		struct sockaddr_in ClientAddr; 
		int addrlen; 
		addrlen=sizeof(ClientAddr); 
		sClient=accept(sListen,(struct sockaddr *)&ClientAddr,&addrlen); 
		const int bNodelay = 1;
		setsockopt(sClient ,IPPROTO_TCP,TCP_NODELAY,(char *)&bNodelay,sizeof(bNodelay)); 
		WSAAsyncSelect(sClient,hwnd,WM_SOCKET, FD_WRITE | FD_READ | FD_CLOSE ) ;
		OnAccept(sClient,ClientAddr);
		}
			
		break;
	case FD_READ:
		{
			char recvbuf[MSG_SIZE];
			memset(recvbuf,0,MSG_SIZE);
			int iBytes = recv(wParam,recvbuf,MSG_SIZE,0);
			if(iBytes>0)
			{
				SplitMsg(wParam,recvbuf, iBytes);  //���÷ְ��㷨�ְ�
			}	
		}
		break;
	case FD_WRITE:
		break;
	case FD_CLOSE:
		OnClose(wParam);
		break;
	}
	return 0;
}

void CTCPServer::CopyRemainMsg(char *pBuffer, int nLen, int nRemainLen)
{
	ZeroMemory(msgBuffer, MSG_SIZE * 2);
	//��ʣ�µ�һ���ָ��Ƶ�msgBuffer�У�����¼��һ�������ݳ���nHalfMsgLen
	memcpy(msgBuffer, pBuffer + nLen - nRemainLen, nRemainLen);
	nHalfMsgLen = nRemainLen;
}

void CTCPServer::SplitMsg(SOCKET s,char *pBuffer, int nLen)
{
	memcpy(msgBuffer + nHalfMsgLen, pBuffer, nLen);
	char* p = msgBuffer;
	int nRemainLen = nLen + nHalfMsgLen;
	static int m = 1;//���ڴ洢ʵ���յ������ݰ�����

	Msg_Generic* pGenericMsg;
	while (p != NULL)
	{
		if (nRemainLen < sizeof(struct Msg_Generic)) //ʣ�µĳ��Ȳ�����Ϣͷ�ĳ���
		{
			CopyRemainMsg(pBuffer, nLen, nRemainLen);
			p = NULL;
			break;
		}
		else
		{
			pGenericMsg = (Msg_Generic*)p;
			if (nRemainLen < pGenericMsg->nLen) //ʣ�µĳ��Ȳ���һ�������ĸýṹ�峤��ʱ
			{
				CopyRemainMsg(pBuffer, nLen, nRemainLen);
				p = NULL;
				break;
			}
			else //ʣ�µĳ��ȹ�һ�������ĸýṹ�峤��ʱ
			{
				nRemainLen -= pGenericMsg->nLen;//�õ���ǰʣ���ֽ���
				OnRead(s,p, pGenericMsg->nLen); //����������Ϣ	
				if (nRemainLen == 0)//��ʣ���ֽ�������0,˵��û�����ݰ�Ҫ��������ѭ��
				{
					p = NULL;
					nHalfMsgLen = 0;
					break;
				}
				else if (nRemainLen > 0) //��ʣ���ֽ�������0��˵���������ݰ���Ҫ������ָ��ָ����һ���ݰ�
				{
					p += pGenericMsg->nLen;
				}
			}
		}
	}
}