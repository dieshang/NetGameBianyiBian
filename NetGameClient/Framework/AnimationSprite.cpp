#include "AnimationSprite.h"


CAnimationSprite::~CAnimationSprite(void)
{

}
CAnimationSprite::CAnimationSprite(	
									ID2D1HwndRenderTarget	*pRenderTarget,  //���ι��캯��
									ID2D1Bitmap				*pTexture,
									D2D1_POINT_2F			&vPos,
									int						nFrames,
									int						nFps,
									float						width,
									float						height,
									int						tx,
									int						ty,
									D2D1_POINT_2F			vHotSpot,
									wstring					wsName
									):CSprite(pRenderTarget,pTexture,vPos,width,height,tx,ty,vHotSpot,wsName)
{
	this->nFrames = nFrames;
	this->nFps = nFps;
	
	
	this->vPos = vPos;
	txStart = tx;
	tyStart = ty;
	bPlaying = false;
	nMode = ANI_FWD | ANI_LOOP;
	this->fInterval = 1.0f/nFps;
}

//���ݲ���ģʽ���ö������ŵĳ�ʼ����
void CAnimationSprite::Play() 
{
	bPlaying=true;
	fSinceLastFrame=-1.0f;
	if(nMode == ANI_REV)
	{
		nDelta = -1;
		SetFrame(nFrames-1);
	}
	else
	{
		nDelta = 1;
		SetFrame(0);
	}
}
//����ϵͳ���ŵ�ʱ�������¶���
void CAnimationSprite::Update(float fDeltaTime)
{
	if(!bPlaying) 
	{
		return;
	}

	if(fSinceLastFrame == -1.0f)
	{
		fSinceLastFrame=0.0f;
	}
	else
	{
		fSinceLastFrame += fDeltaTime;
	}


	if(fSinceLastFrame >= fInterval)
	{
		fSinceLastFrame -= fInterval;

		if(nCurFrame + nDelta == nFrames)
		{
			switch(nMode)
			{
				case ANI_FWD:
				
					break;

				
			}
		}
		else if(nCurFrame + nDelta < 0)
		{
			switch(nMode)
			{
				case ANI_REV:
					bPlaying = false;
					break;
			}
		}

		if(bPlaying) 
		{
			SetFrame(nCurFrame+nDelta);
		}
	}
}
//���õ�ǰ֡Ӧ��ȡ�ķ�ͼƬ
  
 
void CAnimationSprite::SetFrame(int n)
{
	float tx1, ty1;

	int ncols = nTexWidth / width;


	n = n % nFrames;
	

	if(n < 0) n = nFrames + n;
	nCurFrame = n;

	// calculate texture coords for frame n
	ty1 = ty;
	//tx += width;;
	tx1 = txStart + n*width;
	//tx1 = tx;
	if(tx1 > nTexWidth - width)
	{
		n -= (nTexWidth -tx) / width;
		tx1 = width * (n%ncols);
		ty1 += height * (1 + n/ncols);
	}

	SetTexPos(tx1,ty1);
}
void CAnimationSprite::SetTexturePos(int tx,int ty)
{
	this->tx = tx;
	this->ty = ty;
}
//���þ���ͼƬ
void CAnimationSprite::SetTexture(ID2D1Bitmap *tex)
{
	CSprite::SetTexture(tex);
}
void CAnimationSprite::SetTexture(ID2D1Bitmap *tex,D2D1_POINT_2F &vPos,int w,int h,int tx,int ty)
{
	CSprite::SetTexture(tex);
	this->tx = tx;
	this->ty = ty;
	this->width = w;
	this->height = h;
	this->vPos;
}

CAnimationSprite *CAnimationSprite::Clone()
{
	CAnimationSprite *pAniSpr = new CAnimationSprite(pRenderTarget,pTexture,vPos,nFrames,nFps,width,height,tx,ty,vHotSpot,wsName);
	if (bPlaying)
	{
		pAniSpr->Play();
	}
	return pAniSpr;
}

