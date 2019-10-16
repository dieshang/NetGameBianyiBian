#pragma  once


/*******************************************************************************
	����������,���ڹ������������Ϊ,������ͼƬ��Ⱦ��ָ���ĵط�,
	��Ⱦʱ���Խ��������͸����Ⱦ�������ܼ���Ƿ�������������ײ

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
			ID2D1Bitmap					*pTexture,														//����
			D2D1_POINT_2F				&vPos, 															//λ������
			float							w,																//������
			float							h,																//����߶�
			int							tx = 0,															//����x
			int							ty = 0,															//����y
			D2D1_POINT_2F				vHotSpot=Point2F(0.0f,0.0f),										//�ȵ�
			wstring						wsName = TEXT("")
			);														
	virtual ~CSprite(void);				//����
	
	friend class CSpritesManager;
protected:
	wstring						wsName;
	ID2D1Bitmap					*pTexture;
	ID2D1BitmapBrush			*pSpriteBrush;
	ID2D1Bitmap					*pSpriteBitmap;
	ID2D1SolidColorBrush		*pBoundingBoxBrush;
	ID2D1SolidColorBrush		*pBackgroundBrush;
	D2D1_RECT_F					rtBoundingBox;
	//D2D1_RECT_U					rectSprite;																//������� 
	D2D1_POINT_2F				vPos;																	//λ������
	float							tx;																		//����ͼx
	float							ty;																		//����ͼy									
	float							tw;
	float							th;

	float							width;																	//������
	float							height;																	//����߶�			
	float							nTexWidth;
	float							nTexHeight;
	float							nDestWidth;																//Ŀ�Ŀ��
	float							nDestHeight;															//Ŀ�ĸ߶�
	bool						bVisible;
	bool						bEnabled;
	bool						bDrawBoundingBox;
	bool						bTexPosChanged;
	bool						bStretch;

	int							nBlendMode;
	D2D1_COLOR_F				color;
	D2D1_POINT_2F	            vHotSpot;																//�ȵ�

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

	virtual void Update(float fDeltaTime){}	//����
	virtual CSprite *Clone();

	void Release();
	
public:

	
	
	bool IsSelected(int x,int y);
	bool CollideWith(CSprite & sprite);															//�Ƿ���ײ
	bool CollideWith(RECT &rect);																//�Ƿ��ĳ��������ײ

	void SetTexture(ID2D1Bitmap *tex);															//���þ��������
	const ID2D1Bitmap *GetTexture();

	const ID2D1Bitmap *GetBitmap();																//�õ�������Ⱦ��λͼ


	void SetScaleFactor(float sx,float sy);														//��������ϵ�� 

	void SetDestRect(float x1,float y1,float w,float h,bool bStretch = true);					//������Ⱦ��Ŀ�ľ���

	void SetTransform(Matrix3x2F &matTrans);													//���ñ任���� 
	const Matrix3x2F *GetTransform();
	
	void SetTexPos(float x,float y);																//���þ����������Ͻ�ȡ�����Ͻ�����	

	void SetPos(D2D1_POINT_2F &vPos);															//���þ����λ��
	D2D1_POINT_2F	&GetPos();	


	void SetHotSpot(D2D1_POINT_2F &vHotSpot);													//�����ȵ�			
	D2D1_POINT_2F &GetHotSpot();																//�õ��ȵ�

	void SetRotationAngle(float fAngle);														//������ת�Ƕ�			
	float GetRotationAngle();

	void SetVisible(bool bVal);																	//���þ���ɼ��� 
	bool IsVisible();	

	void SetEnabled(bool bVal);
	bool IsEnabled();

	float GetWidth();																				//�õ�������
	float GetHeight();																			//�õ�����߶�



	const wstring &GetSpriteName();
	const D2D1_RECT_F* GetBoundingBox();																//�õ�������η�Χ		

	void Render();
	void Render(D2D1_POINT_2F &vPos);
	void Render(D2D1_RECT_F &destRect,bool bStretch=true,D2D1_EXTEND_MODE extendModeX=D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE extendModeY=D2D1_EXTEND_MODE_WRAP);
	

	void SetColor(const D2D1_COLOR_F &color);
};





