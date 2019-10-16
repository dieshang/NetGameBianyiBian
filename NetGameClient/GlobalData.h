#pragma once
class GlobalData
{
private:
	static GlobalData *instance;
	
public:
	GlobalData();
	~GlobalData();

	static GlobalData *GetInstance()
	{
		if (!instance)
		{
			instance = new GlobalData();
		}
		return instance;
	}
	wchar_t username[30];
	wchar_t password[30];
};

