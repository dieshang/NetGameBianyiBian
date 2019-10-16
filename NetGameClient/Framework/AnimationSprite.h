#pragma once
#include "sprite.h"

#define	ANI_FWD		0
#define ANI_REV		1
#define ANI_LOOP	2
class CAnimationSprite:public CSprite						//�̳���CSprite
{
public:
	
	CAnimationSprite(				ID2D1HwndRenderTarget	*pRenderTarget,  //���ι��캯��
									ID2D1Bitmap				*pTexture,
									D2D1_POINT_2F			&vPos,
									int						nFrames,
									int						nFps,
									float						width,
									float						height,
									int						tx = 0,
									int						ty = 0,
									D2D1_POINT_2F			vHotSpot=D2D1::Point2F(0,0),
									wstring					wsName = TEXT("")
									);


	virtual ~CAnimationSprite();
	
	friend class CSpritesManager;
	
	void		Play();										//���Ŷ�������
	void		Stop() { bPlaying=false; }					//ֹͣ����
	void		Resume() { bPlaying=true; }					//�ָ�����
	bool		IsPlaying() const { return bPlaying; }		//�Ƿ��ڲ���

	void        SetTexture(ID2D1Bitmap *tex);						//���þ���ͼƬ
	void        SetTexture(ID2D1Bitmap *tex,D2D1_POINT_2F &vPos,int w,int h,int tx,int ty);//���þ���ͼƬ�͸���ϸ�Ĳ���
	void		SetMode(int nMode) {this->nMode = nMode;}	//���ö�������ģʽ
	void		SetSpeed(float FPS) { fInterval=1.0f/FPS; }	//����֡��	
	void		SetFrame(int n);							//���õ�ǰ����֡
	void		SetFrames(int n) { nFrames=n; }				//������֡��

	int			GetMode()  { return nMode; }			//�õ���ǰ����ģʽ
	float		GetSpeed() { return 1.0f/fInterval; }		//�õ���ǰ֡��
	int			GetFrame() { return nCurFrame; }		//���ص�ǰ֡
	int			GetFrames(){ return nFrames; }			//�õ���֡��

	

	void        SetTexturePos(int tx,int ty);					//���ôӾ���ͼƬ�Ͽ�ʼ�и��λ��

protected:

	
	float			txStart;
	float			tyStart;

	bool		bPlaying;								//�Ƿ񲥷�

	float		fInterval;									//�ٶ�
	float		fSinceLastFrame;						//����һ֡�����ھ����˶��ٺ���

	int			nMode;									//����ģʽ
	int			nDelta;									//ÿ�θ��¶���֡
	int			nFrames;								//��֡��
	int			nFps;									//ÿ�����֡
	int			nCurFrame;								//��ǰ֡

	
	CAnimationSprite *Clone();
public:
	void		Update(float fDeltaTime);				//���¶���
};
