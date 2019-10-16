#include "TCPServer.h"

CTCPServer::CTCPServer()  //初始化函数
{
	sListen=NULL;
	bCreate=false;
	ZeroMemory(msgBuffer, MSG_SIZE * 2);
	nHalfMsgLen = 0;
}
CTCPServer::~CTCPServer()  //析构函数
{
	Release();
}

void CTCPServer::InitSocket(HWND hWin)  //初始化函数
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	sListen=socket(AF_INET,SOCK_STREAM,0); 
	hwndWin = hWin;
	WSAAsyncSelect(sListen,hWin,WM_SOCKET, FD_ACCEPT | FD_CLOSE  ) ;
}

BOOL CTCPServer::StartServer(short port)//开始服务器
{
	if(!bCreate)//当服务器没有启动
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

	return false;//当服务器已经启动
}

BOOL  CTCPServer::Release()         //关闭服务器
{
	closesocket(sListen);

	WSACleanup();
	return true;
}



LRESULT CTCPServer::WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:	//lParam为连接服务端消息
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
				SplitMsg(wParam,recvbuf, iBytes);  //调用分包算法分包
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
	//将剩下的一部分复制到msgBuffer中，并记录这一部分数据长度nHalfMsgLen
	memcpy(msgBuffer, pBuffer + nLen - nRemainLen, nRemainLen);
	nHalfMsgLen = nRemainLen;
}

void CTCPServer::SplitMsg(SOCKET s,char *pBuffer, int nLen)
{
	memcpy(msgBuffer + nHalfMsgLen, pBuffer, nLen);
	char* p = msgBuffer;
	int nRemainLen = nLen + nHalfMsgLen;
	static int m = 1;//用于存储实现收到的数据包个数

	Msg_Generic* pGenericMsg;
	while (p != NULL)
	{
		if (nRemainLen < sizeof(struct Msg_Generic)) //剩下的长度不够消息头的长度
		{
			CopyRemainMsg(pBuffer, nLen, nRemainLen);
			p = NULL;
			break;
		}
		else
		{
			pGenericMsg = (Msg_Generic*)p;
			if (nRemainLen < pGenericMsg->nLen) //剩下的长度不够一个完整的该结构体长度时
			{
				CopyRemainMsg(pBuffer, nLen, nRemainLen);
				p = NULL;
				break;
			}
			else //剩下的长度够一个完整的该结构体长度时
			{
				nRemainLen -= pGenericMsg->nLen;//得到当前剩余字节数
				OnRead(s,p, pGenericMsg->nLen); //解析处理消息	
				if (nRemainLen == 0)//当剩余字节数等于0,说明没有数据包要处理，跳出循环
				{
					p = NULL;
					nHalfMsgLen = 0;
					break;
				}
				else if (nRemainLen > 0) //当剩余字节数大于0，说明还有数据包需要处理，则指针指向下一数据包
				{
					p += pGenericMsg->nLen;
				}
			}
		}
	}
}