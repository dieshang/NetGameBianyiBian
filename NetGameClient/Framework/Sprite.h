#pragma  once


/*******************************************************************************
	建立精灵类,用于管理精灵自身的行为,包括将图片渲染到指定的地方,
	渲染时可以进行拉伸和透明渲染。并且能检查是否与其它精灵碰撞

********************************************************************************/

#define _WINSOCKAPI_  
#include <Windows.h> 
#include <math.h>
#include <d2d1.h>
#include <assert.h>
#include <string>
#include "Helper.h"
//#include "Resources.h"

#define MAXRESCHARS			255


using namespace D2D1;
using namespace std;

class CSprite
{
	
public:

	CSprite(ID2D1HwndRenderTarget 		*pRenderTarget,													//RenderTarget										
			ID2D1Bitmap					*pTexture,														//纹理
			D2D1_POINT_2F				&vPos, 															//位置向量
			float							w,																//精灵宽度
			float							h,																//精灵高度
			int							tx = 0,															//纹理x
			int							ty = 0,															//纹理y
			D2D1_POINT_2F				vHotSpot=Point2F(0.0f,0.0f),										//热点
			wstring						wsName = TEXT("")
			);														
	virtual ~CSprite(void);				//析构
	
	friend class CSpritesManager;
protected:
	wstring						wsName;
	ID2D1Bitmap					*pTexture;
	ID2D1BitmapBrush			*pSpriteBrush;
	ID2D1Bitmap					*pSpriteBitmap;
	ID2D1SolidColorBrush		*pBoundingBoxBrush;
	ID2D1SolidColorBrush		*pBackgroundBrush;
	D2D1_RECT_F					rtBoundingBox;
	//D2D1_RECT_U					rectSprite;																//精灵矩形 
	D2D1_POINT_2F				vPos;																	//位置向量
	float							tx;																		//纹理图x
	float							ty;																		//纹理图y									
	float							tw;
	float							th;

	float							width;																	//精灵宽度
	float							height;																	//精灵高度			
	float							nTexWidth;
	float							nTexHeight;
	float							nDestWidth;																//目的宽度
	float							nDestHeight;															//目的高度
	bool						bVisible;
	bool						bEnabled;
	bool						bDrawBoundingBox;
	bool						bTexPosChanged;
	bool						bStretch;

	int							nBlendMode;
	D2D1_COLOR_F				color;
	D2D1_POINT_2F	            vHotSpot;																//热点

	ID2D1HwndRenderTarget 		*pRenderTarget;		
	HRESULT						hState;
	Matrix3x2F			        matWorld;
	Matrix3x2F					matScale;
	Matrix3x2F					matRotation;
	Matrix3x2F					matTranslation;

	float						fRotationAngle;
	float                       fsx;
	float                       fsy;

	D2D1_RECT_F					destRect;

	D2D1_POINT_2F				ptBoundingBox[4];


	void                        ComputerBoundingBox();

	virtual void Update(float fDeltaTime){}	//更新
	virtual CSprite *Clone();

	void Release();
	
public:

	
	
	bool IsSelected(int x,int y);
	bool CollideWith(CSprite & sprite);															//是否碰撞
	bool CollideWith(RECT &rect);																//是否和某个矩形碰撞

	void SetTexture(ID2D1Bitmap *tex);															//设置精灵的纹理
	const ID2D1Bitmap *GetTexture();

	const ID2D1Bitmap *GetBitmap();																//得到精灵渲染的位图


	void SetScaleFactor(float sx,float sy);														//设置缩放系数 

	void SetDestRect(float x1,float y1,float w,float h,bool bStretch = true);					//设置渲染的目的矩形

	void SetTransform(Matrix3x2F &matTrans);													//设置变换矩阵 
	const Matrix3x2F *GetTransform();
	
	void SetTexPos(float x,float y);																//设置精灵在纹理上截取的左上角坐标	

	void SetPos(D2D1_POINT_2F &vPos);															//设置精灵的位置
	D2D1_POINT_2F	&GetPos();	


	void SetHotSpot(D2D1_POINT_2F &vHotSpot);													//设置热点			
	D2D1_POINT_2F &GetHotSpot();																//得到热点

	void SetRotationAngle(float fAngle);														//设置旋转角度			
	float GetRotationAngle();

	void SetVisible(bool bVal);																	//设置精灵可见性 
	bool IsVisible();	

	void SetEnabled(bool bVal);
	bool IsEnabled();

	float GetWidth();																				//得到精灵宽度
	float GetHeight();																			//得到精灵高度



	const wstring &GetSpriteName();
	const D2D1_RECT_F* GetBoundingBox();																//得到精灵矩形范围		

	void Render();
	void Render(D2D1_POINT_2F &vPos);
	void Render(D2D1_RECT_F &destRect,bool bStretch=true,D2D1_EXTEND_MODE extendModeX=D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE extendModeY=D2D1_EXTEND_MODE_WRAP);
	

	void SetColor(const D2D1_COLOR_F &color);
};





