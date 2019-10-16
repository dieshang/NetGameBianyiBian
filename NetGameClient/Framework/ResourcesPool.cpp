
#include "ResourcesPool.h"


void CResourcesPool::init(IWICImagingFactory *pWICImagingFactory,ID2D1HwndRenderTarget *pRenderTarget)
{
	this->pRenderTarget = pRenderTarget;
	this->pWICImagingFactory = pWICImagingFactory;
}


CResourcesPool::~CResourcesPool(void)
{
	Release();
}
void CResourcesPool::ClearResourcesPool()
{
	Release();
	resMap.clear();
}
void CResourcesPool::Release()
{
	for(ResMap::iterator ite = resMap.begin();ite!=resMap.end();++ite)
	{
		PResDesc pRes = ite->second;
		SafeRelease(&pRes->pTexture);
	}
}
HRESULT CResourcesPool::AddTexture(const wstring wsName,const wstring  wsFile,ID2D1Bitmap **ppTexture)
{
	HRESULT hr = S_OK;
	ResMap::iterator iteRes = resMap.find(wsName);
	if (iteRes != resMap.end())
	{
		PResDesc pRes = iteRes->second;
		*ppTexture = pRes->pTexture;
	}
	else
	{
		PResDesc pRes = new ResDesc;
		hr = LoadBitmapFromFile(wsName,wsFile,&pRes->pTexture);
		if (hr == S_OK)
		{
			pRes->wsName = wsName;
			pRes->wsPath = wsFile;
			resMap.insert(ResMap::value_type(wsName,pRes));
		}
	}
	return hr;
}

const PResDesc CResourcesPool::GetResource(const wstring wsResName)
{
	ResMap::iterator iter = resMap.find(wsResName);
	if (iter != resMap.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

HRESULT CResourcesPool::LoadBitmapFromFile(
	//从文件中读取位图
	const wstring		sName,
	const wstring		sFile,
	ID2D1Bitmap			**ppTexture,
	int					destinationWidth ,
	int					destinationHeight
	)
{
	if (pRenderTarget == NULL || pWICImagingFactory ==NULL)
	{
		return !S_OK;
	}
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	HRESULT hr = pWICImagingFactory->CreateDecoderFromFilename(
		sFile.c_str(),
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pWICImagingFactory->CreateFormatConverter(&pConverter);

	}


	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pWICImagingFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
						);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
						);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
				);
		}
	}
	if (SUCCEEDED(hr))
	{

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppTexture
			);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;

}
