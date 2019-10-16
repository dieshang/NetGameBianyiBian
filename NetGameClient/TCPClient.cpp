#include "TCPClient.h"

CTCPClient::CTCPClient()  //初始化函数
{	
	sClient=NULL;
	ZeroMemory(msgBuffer, MSG_SIZE * 2);
	nHalfMsgLen = 0;
}
CTCPClient::~CTCPClient()  //初始化函数
{
	
}

void CTCPClient::InitSocket(HWND hwnd)  //初始化函数
{

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	sClient=socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(sClient,hwnd,WM_SOCKET,FD_CONNECT|FD_WRITE|FD_READ|FD_CLOSE);

}

BOOL CTCPClient::ConnectServer(char *ipaddr,short port)//连接服务器
{
	
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr(ipaddr);
	ServerAddr.sin_port = htons(port);
	
	int nRet=connect(sClient,(struct sockaddr *)&ServerAddr,sizeof(ServerAddr)); 
	
	
	if (nRet==0)
	{
		
		return true;
	}
	else
	{
		return false;
	}
}


BOOL  CTCPClient::Release()         //关闭服务器
{
	closesocket(sClient);
	WSACleanup();
	return true;
}

int  CTCPClient::SendMsg(char* pBuffer, UINT lLength)
{
	if( sClient == INVALID_SOCKET )
		return 0;

	int	nBytesSent = 0; //当次发送的字节数
	int nBytes;			//一次发送的字节数

	while (nBytesSent < lLength)  
	{
		if ((nBytes = send(sClient, (char*)pBuffer + nBytesSent, lLength - nBytesSent,0)) == SOCKET_ERROR){
			if (GetLastError() == WSAEWOULDBLOCK) {
				Sleep(100);
				//break;	
			}
			else{
				return 0;
			}
		}
		else{
			nBytesSent += nBytes;		
		}
	}
	return 1;
}



LRESULT CTCPClient::WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:	//lParam为连接服务端消息	
		/*if( WSAGETSELECTERROR(lParam) != 0 )	
			MessageBox(hwnd,"服务器末开放","OK",0);
		else	
			MessageBox(hwnd,"连接成功","OK",0);	*/
		OnConnect(lParam);
		break;
	case FD_READ:
		{
			char recvbuf[MSG_SIZE];
			int iBytes = recv(wParam,recvbuf,MSG_SIZE,0);
			if(iBytes>0)
			{
				recvbuf[iBytes]='\0';
				//OnRead(sClient,recvbuf,iBytes);
				SplitMsg(wParam, recvbuf, iBytes);
			}
			
		}
		break;
		break;
	case FD_WRITE:
		break;
	case FD_CLOSE:
		OnClose(wParam);
		break;
	}

	return 0;
}

void CTCPClient::CopyRemainMsg(char *pBuffer, int nLen, int nRemainLen)
{
	ZeroMemory(msgBuffer, MSG_SIZE * 2);
	//将剩下的一部分复制到msgBuffer中，并记录这一部分数据长度nHalfMsgLen
	memcpy(msgBuffer, pBuffer + nLen - nRemainLen, nRemainLen);
	nHalfMsgLen = nRemainLen;
}

void CTCPClient::SplitMsg(SOCKET s, char *pBuffer, int nLen)
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
				OnRead(s, p, pGenericMsg->nLen); //解析处理消息	
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