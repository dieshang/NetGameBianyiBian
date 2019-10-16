#include "TCPClient.h"

CTCPClient::CTCPClient()  //��ʼ������
{	
	sClient=NULL;
	ZeroMemory(msgBuffer, MSG_SIZE * 2);
	nHalfMsgLen = 0;
}
CTCPClient::~CTCPClient()  //��ʼ������
{
	
}

void CTCPClient::InitSocket(HWND hwnd)  //��ʼ������
{

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	sClient=socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(sClient,hwnd,WM_SOCKET,FD_CONNECT|FD_WRITE|FD_READ|FD_CLOSE);

}

BOOL CTCPClient::ConnectServer(char *ipaddr,short port)//���ӷ�����
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


BOOL  CTCPClient::Release()         //�رշ�����
{
	closesocket(sClient);
	WSACleanup();
	return true;
}

int  CTCPClient::SendMsg(char* pBuffer, UINT lLength)
{
	if( sClient == INVALID_SOCKET )
		return 0;

	int	nBytesSent = 0; //���η��͵��ֽ���
	int nBytes;			//һ�η��͵��ֽ���

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
	case FD_CONNECT:	//lParamΪ���ӷ������Ϣ	
		/*if( WSAGETSELECTERROR(lParam) != 0 )	
			MessageBox(hwnd,"������ĩ����","OK",0);
		else	
			MessageBox(hwnd,"���ӳɹ�","OK",0);	*/
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
	//��ʣ�µ�һ���ָ��Ƶ�msgBuffer�У�����¼��һ�������ݳ���nHalfMsgLen
	memcpy(msgBuffer, pBuffer + nLen - nRemainLen, nRemainLen);
	nHalfMsgLen = nRemainLen;
}

void CTCPClient::SplitMsg(SOCKET s, char *pBuffer, int nLen)
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
				OnRead(s, p, pGenericMsg->nLen); //����������Ϣ	
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