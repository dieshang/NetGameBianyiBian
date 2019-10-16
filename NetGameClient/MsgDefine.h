#pragma once
#pragma pack(push) //�������״̬
#pragma pack(4)//�趨Ϊ4�ֽڶ���

#define MSGID_LOGIN             1   //��¼��Ϣ
#define MSGID_PLAYER_SELF       2   //���ѵ�¼�ɹ����û���Ϣ
#define MSGID_PLAYER_DELETE     3   //ɾ�������Ϣ
#define MSGID_SCORE             4   //��ҷ�����Ϣ
#define MSGID_UpLoadScore             5   //�ϴ�������Ϣ
#define MSGID_DownLoadScore             6  //���ط�����Ϣ
#define MSGID_RankingList             7  //���а���Ϣ
#define MSGID_Match 8//ƥ��������Ϣ
#define MSGID_MatchSucceed  9//ƥ��ɹ���Ϣ
#define MSGID_MatchCanel  10//ȡ��ƥ����Ϣ
#define MSGID_FAILED 11//ȡ��ƥ����Ϣ

struct PlayerInfo
{
	int s;
	WCHAR cName[20];

};

struct Msg_Generic
{
	DWORD dwType;  //��Ϣ����
	int   nLen;    //��Ϣ���ȣ���ְ�ʱ��
};



struct Msg_Ranking :public Msg_Generic
{
	WCHAR cName[20];
	int nScore;
	//����
	int Place;
};
struct Msg_Score :public Msg_Generic
{
	int s;
	int nScore;
};
struct Msg_Sock :public Msg_Generic
{
	int s;
};



struct Msg_Player :public Msg_Generic
{

	struct PlayerInfo player;
};

struct Msg_Player_Delete :public Msg_Generic
{
	int s;
};

struct Msg_Login :public Msg_Generic
{
	WCHAR cName[20];         //�û���
	WCHAR cPwd[20];          //����
};



#pragma pack(pop) // �ָ���ǰ����