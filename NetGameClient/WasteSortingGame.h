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
	GAME_Ready,    //��Ϸ׼������״̬
	GAME_START,    //��Ϸ��ʼ����״̬
	GAME_OVER      //��Ϸ������״̬
};

enum GAME_Mode
{
	//����
	Single,
	//˫�˶�ս
	Battle
};
//��Ϸ��� �öԶ�ս
enum GAME_result
{
	//ʤ��
	Win,
	//ʧ��
	Fail,
	//ƽ��
	dogfall
};
//����
struct Waste{
	//��������
	wchar_t WasteName[10];
	CSprite* WasteSprite;
	//true���������ɻ���
	bool Recoverable;
	Waste(){};
	Waste(wchar_t Name[10], CSprite* Sprite, bool R){
		wcscpy(WasteName, Name);
	WasteSprite=Sprite;
	Recoverable=R;
	};
};
//���
struct Earthworms{
	CAnimationSprite* EarthwormsSprite;
	//true���������ɻ���
	bool Recoverable;
};

class WasteSortingGame
{
public:
	WasteSortingGame(GAME_Mode );
	~WasteSortingGame();
	int GameMode;
	//������ʼ��
	void Init();
	// ��ʾ���㴰��
	void ClaerWindows(bool IsShow);
	void OpenMusic(bool Open);
	// �ϴ�����
	int UploadScore();
	// �˳���Ϸ
	void ExitGame();
	// ������Ϸ���˵�
	void GoBackStartUI();
	// ���¿�ʼ��Ϸ
	void RestartGame();
	// ����λ��
	void ChangePosition();
	//ÿ֡����
	int Update(float fDeltaTime);
	//������Ϸ���˵����鰴ť����
	CSpriteButton *bGoBackStartButton;
	//�˳���Ϸ��ť����
	CSpriteButton *bExitGameButton;
	//�ϴ�������ť����
	CSpriteButton *bUploadScoreButton;
	// ���¿�ʼ��Ϸ
	CSpriteButton *bRestartGameButton;
	CSpriteButton *bMatchWindowsCanelButton;
	//��Ч
	XAudio2SoundPlayer   soundPlayer;

	//��������
	TextSprite *TScore;
	//��ʾ��Ϣ����
	TextSprite *TTipInfo;

	//���ַ�������
	TextSprite *BattleTScore;
	//�������ƾ���
	TextSprite *BattleName;
	//��д��ս����
	void AlterBattleScore(int);
	//��д��ս����
	void AlterBattleName(WCHAR cName[20]);
	CSprite* pGamemusic;
	CSprite* pGamemusic1;

	GAME_STATE nGameState;
	GAME_Mode nGameMode;
	//����
	int score;
	//��갴��
	void MouseUp();
	//���̰���
	void HandleKeyUp(WPARAM wParam, LPARAM lParam);
	GAME_result BattleResult;
	bool scoreNeedUpdate=false;
private:
	int battleScore;
	//����������ʧ֮��ʱ����ۼ�ֵ
	DWORD				t;
	//������ײ��Ч����֮��ʱ����ۼ�ֵ
	DWORD				EffectsTime;
	//��Ϸ�ײ���һ�����
	Earthworms * TwoEarthworm;
	//���������������
	CAnimationSprite* EarthwormsDieAnimationSprite;
	//��Ϸ��������
	CSprite * GameOver;
	//��Ϸ������
	CSprite * GameBackground;
	//���㴰�ڱ�����
	CSprite*ClearWindowsBackground;
	
	// ���½��㴰�ڵ���ʾ��Ϣ
	void UpdateClearInfo();
	// ��������
	void WasteDrop();
	//�ɻ���������
	int recoverableWasteCount;
	//���ɻ���������
	int unrecoverableWasteCount;
	//�ɻ�����������
	Waste*recoverableWasteArry;
	//���ɻ�����������
	Waste*unrecoverableWasteArry;
	//������̬����
	list<Waste>LeftWasteOfScense;
	//�����Ҷ�̬����
	list<Waste>RightWasteOfScense;
	// ����һ������
	void GenerateWaste();
	// ��������
	bool EliminateWaste();
	
	wchar_t ResultRecoverable[10];
	wchar_t	ResultunRecoverable[10];
	//�����ٶ�
	float		DropSpeed;
	//�ȴ�ʱ��
	float WaitTime;
	//��ײ��Ч��
	CSprite * CollisionEffects;
	//ƥ�䴰��
	void MatchWindows(bool IsShow);
	CSprite * MatchWindowsBackground;
};

