#pragma once
#define _WINSOCKAPI_  
#include <Windows.h> 
#include <map>
#include <string>
#include <D2D1.h>
#include <wincodec.h>   //创建WIC位图文件需要的
#include "Helper.h"
#define MAXRESCHARS	255
using namespace std;
using namespace D2D1;

enum ResourceType		//资源类型
{
	RES_TEX
};
struct tagResDesc				//资源节点
{	
	tagResDesc()
	{
		wsName = TEXT("");
		wsPath = TEXT("");
		//nResGroup = 0;
		pTexture = NULL;
		resourceType = RES_TEX;
	}
	wstring		wsName;					//资源名
	wstring		wsPath;					//资源路径
//	int			nResGroup;				//资源组
	ID2D1Bitmap	*pTexture;				//资源文理指针
	ResourceType resourceType;			//资源类型
};
typedef tagResDesc ResDesc,*PResDesc;

/************************************************
	资源管理器，用map管理所有的资源
	目前只管理位图
************************************************/

class CResourcesPool
{
private:
	CResourcesPool(){}
	CResourcesPool(const CResourcesPool&){}
	CResourcesPool &operator =(const CResourcesPool&){}
public:
	static CResourcesPool *instance;
	static CResourcesPool *GetInstance()
	{
		if (instance == NULL)
		{
			instance = new CResourcesPool();
		}
		return instance;
	}
	
	~CResourcesPool(void);
public:	
	void init(IWICImagingFactory *pWICImagingFactory,ID2D1HwndRenderTarget *pRenderTarget);
	//HRESULT LoadTextureFromFile(const wstring sName,const wstring sFile);				//根据文件名装载图片资源
	HRESULT AddTexture(const wstring wsName,const wstring  wsFile,ID2D1Bitmap **ppTexture = NULL);
	const PResDesc GetResource(const wstring sResName);		//根据资源名得到资源节点

	void ClearResourcesPool();

protected:
	typedef map<wstring,PResDesc> ResMap;
	ResMap					resMap;
	ID2D1HwndRenderTarget	*pRenderTarget;
	IWICImagingFactory		*pWICImagingFactory;

	void Release();
	


	HRESULT LoadBitmapFromFile(						//从文件中读取位图
		const wstring		sName,
		const wstring		sFile,
		ID2D1Bitmap			**ppTexture,
		int					destinationWidth = 0,
		int					destinationHeight =0
		
	);

};






