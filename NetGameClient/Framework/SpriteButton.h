#pragma once

#include "Game.h"


enum ButtonState			//��ť״̬
{
	BtnDown,
	BtnUp
};

class CSpriteButton			//��ť�࣬ͨ��������������ʾ��갴�º�̧��״̬
{
public:
	CSpriteButton(int ID,D2D1_POINT_2F &vPos,CSprite *pUpSprite,CSprite *pDownSprite);//���캯��
	~CSpriteButton(void);

	bool HandleMouseUp(WPARAM wParam,LPARAM lParam);								//��갴��̧���״̬
	bool HandleMouseDown(WPARAM wParam,LPARAM lParam);								//��갴�����µ�״̬
	void Reset();																	//���谴ť
	void SetVisible(bool bVal);														//���ð�ť�ɼ���
	ButtonState btnState;	//��ť״̬
	bool GetVisible();
private:
	int				nBtnID;																		//Button ID
	CSprite			*pUp;																	//��ʾ��갴��̧��ľ���
	CSprite			*pDown;																	//��ʾ��갴�����µľ���
	D2D1_POINT_2F	vPos;	//λ��
	bool Visible;
};
