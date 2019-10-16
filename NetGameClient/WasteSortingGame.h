#pragma once
#include "Framework\SpritesManager.h"
#include "Framework\ResourcesPool.h"
#include "Framework\SpriteButton.h"
#include "Framework\TextSpriteManager.h"
#include "Framework\XAudio2SoundPlayer.h"


#include <list>
#include<time.h>

enum GAME_STATE
{
	GAME_Ready,    //游戏准备运行状态
	GAME_START,    //游戏开始运行状态
	GAME_OVER      //游戏结束的状态
};

enum GAME_Mode
{
	//单人
	Single,
	//双人对战
	Battle
};
//游戏结果 用对对战
enum GAME_result
{
	//胜利
	Win,
	//失败
	Fail,
	//平局
	dogfall
};
//垃圾
struct Waste{
	//垃圾名称
	wchar_t WasteName[10];
	CSprite* WasteSprite;
	//true代表垃圾可回收
	bool Recoverable;
	Waste(){};
	Waste(wchar_t Name[10], CSprite* Sprite, bool R){
		wcscpy(WasteName, Name);
	WasteSprite=Sprite;
	Recoverable=R;
	};
};
//蚯蚓
struct Earthworms{
	CAnimationSprite* EarthwormsSprite;
	//true代表垃圾可回收
	bool Recoverable;
};

class WasteSortingGame
{
public:
	WasteSortingGame(GAME_Mode );
	~WasteSortingGame();
	int GameMode;
	//场景初始化
	void Init();
	// 显示结算窗口
	void ClaerWindows(bool IsShow);
	void OpenMusic(bool Open);
	// 上传分数
	int UploadScore();
	// 退出游戏
	void ExitGame();
	// 返回游戏主菜单
	void GoBackStartUI();
	// 重新开始游戏
	void RestartGame();
	// 交换位置
	void ChangePosition();
	//每帧更新
	int Update(float fDeltaTime);
	//返回游戏主菜单精灵按钮精灵
	CSpriteButton *bGoBackStartButton;
	//退出游戏按钮精灵
	CSpriteButton *bExitGameButton;
	//上传分数按钮精灵
	CSpriteButton *bUploadScoreButton;
	// 重新开始游戏
	CSpriteButton *bRestartGameButton;
	CSpriteButton *bMatchWindowsCanelButton;
	//音效
	XAudio2SoundPlayer   soundPlayer;

	//分数精灵
	TextSprite *TScore;
	//提示信息精灵
	TextSprite *TTipInfo;

	//对手分数精灵
	TextSprite *BattleTScore;
	//对手名称精灵
	TextSprite *BattleName;
	//改写对战分数
	void AlterBattleScore(int);
	//改写对战名字
	void AlterBattleName(WCHAR cName[20]);
	CSprite* pGamemusic;
	CSprite* pGamemusic1;

	GAME_STATE nGameState;
	GAME_Mode nGameMode;
	//分数
	int score;
	//鼠标按下
	void MouseUp();
	//键盘按下
	void HandleKeyUp(WPARAM wParam, LPARAM lParam);
	GAME_result BattleResult;
	bool scoreNeedUpdate=false;
private:
	int battleScore;
	//用于垃圾消失之后时间的累计值
	DWORD				t;
	//用于碰撞特效出现之后时间的累计值
	DWORD				EffectsTime;
	//游戏底部的一对蚯蚓
	Earthworms * TwoEarthworm;
	//蚯蚓死亡动画精灵
	CAnimationSprite* EarthwormsDieAnimationSprite;
	//游戏结束精灵
	CSprite * GameOver;
	//游戏背景框
	CSprite * GameBackground;
	//结算窗口背景框
	CSprite*ClearWindowsBackground;
	
	// 更新结算窗口的提示信息
	void UpdateClearInfo();
	// 垃圾掉落
	void WasteDrop();
	//可回收垃圾数
	int recoverableWasteCount;
	//不可回收垃圾数
	int unrecoverableWasteCount;
	//可回收垃圾数组
	Waste*recoverableWasteArry;
	//不可回收垃圾数组
	Waste*unrecoverableWasteArry;
	//场景左动态数组
	list<Waste>LeftWasteOfScense;
	//场景右动态数组
	list<Waste>RightWasteOfScense;
	// 生成一对垃圾
	void GenerateWaste();
	// 消灭垃圾
	bool EliminateWaste();
	
	wchar_t ResultRecoverable[10];
	wchar_t	ResultunRecoverable[10];
	//掉落速度
	float		DropSpeed;
	//等待时间
	float WaitTime;
	//碰撞特效框
	CSprite * CollisionEffects;
	//匹配窗口
	void MatchWindows(bool IsShow);
	CSprite * MatchWindowsBackground;
};

