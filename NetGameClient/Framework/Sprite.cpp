
#include "Sprite.h"




CSprite::~CSprite(void)
{
}
CSprite::CSprite(ID2D1HwndRenderTarget 	*pRenderTarget,													//RenderTarget													
	ID2D1Bitmap					*pTexture,														//纹理
	D2D1_POINT_2F				&vPos, 															//位置向量
	float							w,																//精灵宽度
	float							h,																//精灵高度
	int							tx,															//纹理x
	int							ty,															//纹理y
	D2D1_POINT_2F				vHotSpot,										//热点
	wstring						wsName
	)
{
	assert(pRenderTarget != NULL);
	assert(pTexture != NULL);
	this->wsName = wsName;
	this->pTexture = pTexture;
	this->pRenderTarget = pRenderTarget;
	this->width = w;
	this->height = h;
	this->bStretch = true;

	D2D1_SIZE_F size=pTexture->GetSize();

	this->nTexWidth =  size.width;
	this->nTexHeight  = size.height;

	ptBoundingBox[0].x = 0;//vPos.x;
	ptBoundingBox[0].y = 0;//vPos.y;
	ptBoundingBox[1].x = 0;//vPos.x;
	ptBoundingBox[1].y = h;//vPos.x + h;
	ptBoundingBox[2].x = w;//vPos.x + w;
	ptBoundingBox[2].y = 0;//vPos.y;
	ptBoundingBox[3].x = w;//vPos.x + w;
	ptBoundingBox[3].y = h;//vPos.y + h;


	this->fRotationAngle = 0;
	this->vPos = vPos;
	this->tx = tx;
	this->ty = ty;
	this->vHotSpot = vHotSpot;
	this->bVisible = true;
	this->bEnabled = true;
	this->bTexPosChanged = false;
	pBackgroundBrush = NULL;

	pRenderTarget->CreateBitmap(D2D1::SizeU(width,height),D2D1::BitmapProperties(pTexture->GetPixelFormat()),&pSpriteBitmap);
	assert(pSpriteBitmap != NULL);
	pSpriteBitmap->CopyFromBitmap(&D2D1::Point2U(0,0),pTexture,&D2D1::RectU(tx,ty,tx + width,ty + height));
	pRenderTarget->CreateBitmapBrush(pSpriteBitmap,&pSpriteBrush);

	matWorld = Matrix3x2F::Identity();
	matScale = Matrix3x2F::Identity();
	matRotation = Matrix3x2F::Identity();
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y);
	matWorld = matScale * matRotation * matTranslation;
	this->ComputerBoundingBox();
	color = D2D1::ColorF(0xff,1.0f);
	pRenderTarget->CreateSolidColorBrush(color,&pBoundingBoxBrush);
	bDrawBoundingBox = false;
	bVisible=true;
}

void CSprite::Render()
{
	if (!pRenderTarget)
	{
		return;
	}
	if (bStretch)
	{
		if (pBackgroundBrush)
		{
			//pBackgroundBrush->SetTransform(matWorld);
			pRenderTarget->FillRectangle(&rtBoundingBox,pBackgroundBrush);
			D2D1_COLOR_F color = pBackgroundBrush->GetColor();
			pRenderTarget->DrawBitmap(pSpriteBitmap,&rtBoundingBox,1-color.a );
		}
		else
		{
			pRenderTarget->SetTransform(matWorld);

			pRenderTarget->DrawBitmap(pSpriteBitmap);
		}
		pRenderTarget->SetTransform(Matrix3x2F::Identity());
		if (bDrawBoundingBox)
		{
			
			pRenderTarget->DrawRectangle(rtBoundingBox,pBoundingBoxBrush,2.0f);
		}
	}
	else
	{
		Render(destRect,bStretch);
	}
}

void CSprite::Render(D2D1_POINT_2F &vPos)
{
	if (!pRenderTarget)
	{
		return;
	}
	this->vPos = vPos;
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y );
	matWorld =  matScale * matRotation * matTranslation;
	this->ComputerBoundingBox();
	Render();
}
void CSprite::Render(D2D1_RECT_F &destRect,bool bStretch,D2D1_EXTEND_MODE extendModeX, D2D1_EXTEND_MODE extendModeY)
{
	if (!pRenderTarget)
	{
		return;
	}
	
	if (bStretch)
	{
		fsx = (destRect.right - destRect.left) / static_cast<float>(width);
		fsy = (destRect.bottom - destRect.top ) / static_cast<float>(height);
		vPos.x = destRect.left;
		vPos.y = destRect.top;
		matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y );
		matScale = D2D1::Matrix3x2F::Scale(fsx,fsy,D2D1::Point2F(vHotSpot.x,vHotSpot.y));
		matWorld =  matScale * matRotation * matTranslation;
		this->ComputerBoundingBox();
		Render();
	}
	else
	{
		HRESULT hr = S_OK;
		pSpriteBrush->SetExtendModeX(extendModeX);
		pSpriteBrush->SetExtendModeY(extendModeY);

		if (this->bTexPosChanged)
		{
			SafeRelease(&pSpriteBrush);
			hr = pRenderTarget->CreateBitmapBrush(pSpriteBitmap,&pSpriteBrush);
			this->bTexPosChanged = false;
		}
		if (SUCCEEDED(hr))
		{
			matWorld = D2D1::Matrix3x2F::Identity();
			pRenderTarget->SetTransform(matWorld);//D2D1::Matrix3x2F::Identity());
			pRenderTarget->FillRectangle(&destRect,pSpriteBrush);
			if (bDrawBoundingBox)
			{
				pRenderTarget->SetTransform(Matrix3x2F::Identity());
				pRenderTarget->DrawRectangle(rtBoundingBox,pBoundingBoxBrush,2.0f);
			}		
		}
	}


}
bool CSprite::CollideWith(RECT &rect)
{
	RECT rtIntersect;

	RECT *rtSprite = reinterpret_cast<RECT*>(&rtBoundingBox);
	return IntersectRect(&rtIntersect,rtSprite,&rect);
}
bool CSprite::CollideWith(CSprite &sprite) 
{
	RECT rtIntersect;

	const RECT *rtSprite = reinterpret_cast<const RECT*>(sprite.GetBoundingBox());
	return IntersectRect(&rtIntersect,rtSprite,reinterpret_cast<const RECT*>(&this->rtBoundingBox));
}

D2D1_POINT_2F &CSprite::GetHotSpot() 
{
	return this->vHotSpot;
}

const D2D1_RECT_F* CSprite::GetBoundingBox()
{
	return &rtBoundingBox;																	;
}																	

void CSprite::SetTexture(ID2D1Bitmap *tex)
{
	this->pTexture = tex;

}
const ID2D1Bitmap *CSprite::GetTexture()
{
	return pTexture;
}
const ID2D1Bitmap *CSprite::GetBitmap()
{
	return pSpriteBitmap;
}
void CSprite::SetHotSpot(D2D1_POINT_2F &vHotSpot)
{
	this->vHotSpot = vHotSpot;
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y );
	matWorld = matScale * matRotation * matTranslation;
	this->ComputerBoundingBox();

}

void CSprite::SetTransform(Matrix3x2F &matTrans)
{
	this->matWorld = matTrans;
	this->ComputerBoundingBox();

}
const Matrix3x2F *CSprite::GetTransform()
{
	return &matWorld;
}

float CSprite::GetWidth()
{
	return width;
}
float CSprite::GetHeight()
{
	return height;
}

void CSprite::SetPos(D2D1_POINT_2F &vPos)
{
	this->vPos = vPos;
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y );
	matWorld =  matScale * matRotation * matTranslation;
	this->ComputerBoundingBox();



}
D2D1_POINT_2F &CSprite::GetPos()
{
	return vPos;
}
void CSprite::SetDestRect(float x1,float y1,float w,float h,bool bStretch) 
{

	fsx = (float)w / (float)width;
	fsy = (float)h / (float)height;
	vPos.x = x1  ;
	vPos.y = y1 ;
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y );
	SetScaleFactor(fsx,fsy);
	this->bStretch = bStretch;
	destRect.left = x1;
	destRect.top = y1;
	destRect.right = x1+w;
	destRect.bottom = y1 + h;
	if(!bStretch)
	{
		rtBoundingBox  = destRect;

	}

}
void CSprite::SetTexPos(float x,float y)
{
	assert(pSpriteBitmap != NULL);
	D2D1_SIZE_F size = pTexture->GetSize();
	if (x<0 || x>=size.width || y<0 || y >= size.height)
	{
		return ;
	}
	HRESULT hr = pSpriteBitmap->CopyFromBitmap(&D2D1::Point2U(0,0),pTexture,&D2D1::RectU(x,y,x + width,y + height));
	tx = x;
	ty = y;
	this->bTexPosChanged = true;
}
void CSprite::Release()
{
	SafeRelease(&pSpriteBitmap);
	SafeRelease(&pSpriteBrush);
	SafeRelease(&pBoundingBoxBrush);
}



void CSprite::SetVisible(bool bVal)
{
	this->bVisible = bVal;
}
bool CSprite::IsVisible()
{
	return bVisible;
}

void CSprite::SetRotationAngle(float fAngle)															//设置旋转角度					
{
	fRotationAngle = fAngle;
	matRotation = D2D1::Matrix3x2F::Rotation(fRotationAngle,D2D1::Point2F(vHotSpot.x,vHotSpot.y));
	matWorld =  matScale * matRotation * matTranslation;
	this->ComputerBoundingBox();
}
float CSprite::GetRotationAngle()
{
	return fRotationAngle;
}
void CSprite::SetScaleFactor(float sx,float sy)
{
	fsx = sx;
	fsy = sy;

	matScale = D2D1::Matrix3x2F::Scale(fsx,fsy,Point2F(vHotSpot.x,vHotSpot.y));
	matWorld =  matScale * matRotation * matTranslation;
	ComputerBoundingBox();
}

const wstring &CSprite::GetSpriteName()
{
	return wsName;
}

void CSprite::ComputerBoundingBox()
{
	D2D1_POINT_2F	ptTmp[4];
	for(int i=0;i<4;++i)
	{
		ptTmp[i] = matWorld.TransformPoint(ptBoundingBox[i]);
	}
	float fMinX = ptTmp[0].x;
	float fMaxX = ptTmp[0].x;
	float fMinY = ptTmp[0].y;
	float fMaxY = ptTmp[0].y;
	for(int i=1;i<4;++i)
	{
		if (fMinX > ptTmp[i].x)
		{
			fMinX = ptTmp[i].x;
		}
		if (fMaxX < ptTmp[i].x)
		{
			fMaxX = ptTmp[i].x;
		}

		if (fMinY > ptTmp[i].y)
		{
			fMinY = ptTmp[i].y;
		}
		if (fMaxY < ptTmp[i].y)
		{
			fMaxY = ptTmp[i].y;
		}

	}
	rtBoundingBox.left = fMinX;
	rtBoundingBox.top = fMinY;
	rtBoundingBox.right = fMaxX;
	rtBoundingBox.bottom = fMaxY;


}

bool CSprite::IsSelected(int x,int y)
{

	bool bRet = false;
	
	if (x>=rtBoundingBox.left && x <= rtBoundingBox.right  && y >= rtBoundingBox.top && y <= rtBoundingBox.bottom)
	{
		return true;
	}
	
	return bRet;

}
//void CSprite::SetColor(D3DXCOLOR color)
//{
//	SetColor((DWORD)color);
//}
//void CSprite::SetColor(DWORD dwColor)
//{
//	
//}
//D2D1_COLOR_F CSprite::GetColor()
//{
//	return color;
//}
CSprite *CSprite::Clone()
{
	CSprite *pSprite = new CSprite(pRenderTarget,pTexture,vPos,width,height,tx,ty,vHotSpot,wsName);
	return pSprite;
}
void CSprite::SetEnabled(bool bVal)
{
	this->bEnabled = bVal;

}
bool CSprite::IsEnabled()
{
	return bEnabled;
}

void CSprite::SetColor(const D2D1_COLOR_F &color)
{
	if (pBackgroundBrush)
	{
		SafeRelease(&pBackgroundBrush);
	}
	pRenderTarget->CreateSolidColorBrush(color,&pBackgroundBrush);
}


