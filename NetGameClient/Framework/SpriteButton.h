#pragma once

#include "Game.h"


enum ButtonState			//按钮状态
{
	BtnDown,
	BtnUp
};

class CSpriteButton			//按钮类，通过两个精灵对象表示鼠标按下和抬起状态
{
public:
	CSpriteButton(int ID,D2D1_POINT_2F &vPos,CSprite *pUpSprite,CSprite *pDownSprite);//构造函数
	~CSpriteButton(void);

	bool HandleMouseUp(WPARAM wParam,LPARAM lParam);								//鼠标按键抬起的状态
	bool HandleMouseDown(WPARAM wParam,LPARAM lParam);								//鼠标按键按下的状态
	void Reset();																	//重设按钮
	void SetVisible(bool bVal);														//设置按钮可见性
	ButtonState btnState;	//按钮状态
	bool GetVisible();
private:
	int				nBtnID;																		//Button ID
	CSprite			*pUp;																	//表示鼠标按键抬起的精灵
	CSprite			*pDown;																	//表示鼠标按键按下的精灵
	D2D1_POINT_2F	vPos;	//位置
	bool Visible;
};
