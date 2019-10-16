#pragma once
#pragma pack(push) //保存对齐状态
#pragma pack(4)//设定为4字节对齐

#define MSGID_LOGIN             1   //登录消息
#define MSGID_PLAYER_SELF       2   //自已登录成功的用户消息
#define MSGID_PLAYER_DELETE     3   //删除玩家消息
#define MSGID_SCORE             4   //玩家分数信息
#define MSGID_UpLoadScore             5   //上传分数消息
#define MSGID_DownLoadScore             6  //下载分数消息
#define MSGID_RankingList             7  //排行榜消息
#define MSGID_Match 8//匹配请求消息
#define MSGID_MatchSucceed  9//匹配成功消息
#define MSGID_MatchCanel  10//取消匹配消息
#define MSGID_FAILED 11//取消匹配消息

struct PlayerInfo
{
	int s;
	WCHAR cName[20];

};

struct Msg_Generic
{
	DWORD dwType;  //消息类型
	int   nLen;    //消息长度，需分包时用
};



struct Msg_Ranking :public Msg_Generic
{
	WCHAR cName[20];
	int nScore;
	//名次
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
	WCHAR cName[20];         //用户名
	WCHAR cPwd[20];          //密码
};



#pragma pack(pop) // 恢复先前设置