#pragma once
#include "sprite.h"

#define	ANI_FWD		0
#define ANI_REV		1
#define ANI_LOOP	2
class CAnimationSprite:public CSprite						//继承自CSprite
{
public:
	
	CAnimationSprite(				ID2D1HwndRenderTarget	*pRenderTarget,  //带参构造函数
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
	
	void		Play();										//播放动画精灵
	void		Stop() { bPlaying=false; }					//停止播放
	void		Resume() { bPlaying=true; }					//恢复播放
	bool		IsPlaying() const { return bPlaying; }		//是否在播放

	void        SetTexture(ID2D1Bitmap *tex);						//设置精灵图片
	void        SetTexture(ID2D1Bitmap *tex,D2D1_POINT_2F &vPos,int w,int h,int tx,int ty);//设置精灵图片和更详细的参数
	void		SetMode(int nMode) {this->nMode = nMode;}	//设置动画播放模式
	void		SetSpeed(float FPS) { fInterval=1.0f/FPS; }	//设置帧速	
	void		SetFrame(int n);							//设置当前播放帧
	void		SetFrames(int n) { nFrames=n; }				//设置总帧数

	int			GetMode()  { return nMode; }			//得到当前动画模式
	float		GetSpeed() { return 1.0f/fInterval; }		//得到当前帧数
	int			GetFrame() { return nCurFrame; }		//返回当前帧
	int			GetFrames(){ return nFrames; }			//得到总帧数

	

	void        SetTexturePos(int tx,int ty);					//设置从精灵图片上开始切割的位置

protected:

	
	float			txStart;
	float			tyStart;

	bool		bPlaying;								//是否播放

	float		fInterval;									//速度
	float		fSinceLastFrame;						//从上一帧到现在经过了多少毫秒

	int			nMode;									//播放模式
	int			nDelta;									//每次更新多少帧
	int			nFrames;								//总帧数
	int			nFps;									//每秒多少帧
	int			nCurFrame;								//当前帧

	
	CAnimationSprite *Clone();
public:
	void		Update(float fDeltaTime);				//更新动画
};
