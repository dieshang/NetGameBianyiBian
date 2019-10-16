#include "SpriteButton.h"

CSpriteButton::CSpriteButton(int ID,D2D1_POINT_2F&vPos,CSprite *pUpSprite,CSprite *pDownSprite)
{
	this->nBtnID = ID;
	this->vPos = vPos;
	pUp = pUpSprite;
	pDown = pDownSprite;
	pUp->SetPos(vPos);
	pDown->SetPos(vPos);
	pUp->SetVisible(true);
	pDown->SetVisible(false);
	btnState = BtnUp;
	Visible=true;
}

CSpriteButton::~CSpriteButton(void)
{
	CSpritesManager::GetInstance()->DeleteSprite(pUp);
	CSpritesManager::GetInstance()->DeleteSprite(pDown);

}
bool CSpriteButton:: GetVisible(){
	return Visible;
}
bool CSpriteButton::HandleMouseUp(WPARAM wParam,LPARAM lParam)
{
		if (Visible == true){
	int x = LOWORD(lParam) ;
	int y = HIWORD(lParam) ;
	if (pDown->IsSelected(x,y))
	{
		pDown->SetVisible(false);
		pUp->SetVisible(true);
		btnState = BtnUp;
		return true;
	}}
	return false;
}
bool CSpriteButton::HandleMouseDown(WPARAM wParam,LPARAM lParam)
{
	if (Visible == true){
	int x = LOWORD(lParam) ;
	int y = HIWORD(lParam) ;
	if (pUp->IsSelected(x,y))
	{
		pUp->SetVisible(false);
		pDown->SetVisible(true);
		btnState = BtnDown;
		return true;
		
	}
	}
	return false;
}
void CSpriteButton::Reset()
{
	btnState = BtnUp;
	pUp->SetVisible(true);
	pDown->SetVisible(false);
}
void CSpriteButton::SetVisible(bool bVal)
{
	if (bVal)
	{
		Reset();
		Visible = true;
	}
	else
	{
		pUp->SetVisible(bVal);
		pDown->SetVisible(bVal);
		Visible = false;
	}
}
