//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once
#define _WINSOCKAPI_  
#include <Windows.h> 
#include <vector>
#include <map>
#include <memory>
#include <XAudio2.h>
#include <string>
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#else
#include <xaudio2.h>
#pragma comment(lib,"ole32.lib")
#endif


using namespace std;


namespace
{
	//
	// Handler for XAudio source voice callbacks to maintain playing state
	//
	class SoundCallbackHander : public IXAudio2VoiceCallback
	{
	public:
		SoundCallbackHander(bool* isPlayingHolder) :
		  m_isPlayingHolder(isPlayingHolder)
		  {
		  }

		  ~SoundCallbackHander()
		  {
			  m_isPlayingHolder = nullptr;
		  }

		  //
		  // Voice callbacks from IXAudio2VoiceCallback
		  //
		  STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 bytesRequired);
		  STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS);
		  STDMETHOD_(void, OnStreamEnd) (THIS);
		  STDMETHOD_(void, OnBufferStart) (THIS_ void* bufferContext);
		  STDMETHOD_(void, OnBufferEnd) (THIS_ void* bufferContext);
		  STDMETHOD_(void, OnLoopEnd) (THIS_ void* bufferContext);
		  STDMETHOD_(void, OnVoiceError) (THIS_ void* bufferContext, HRESULT error);

	private:
		bool* m_isPlayingHolder;
	};

	//
	// Callback handlers, only implement the buffer events for maintaining play state
	//
	void SoundCallbackHander::OnVoiceProcessingPassStart(UINT32 /*bytesRequired*/)
	{
	}
	void SoundCallbackHander::OnVoiceProcessingPassEnd()
	{
	}
	void SoundCallbackHander::OnStreamEnd()
	{
	}
	void SoundCallbackHander::OnBufferStart(void* /*bufferContext*/)
	{
		*m_isPlayingHolder = true;
	}
	void SoundCallbackHander::OnBufferEnd(void* /*bufferContext*/)
	{
		*m_isPlayingHolder = false;
	}
	void SoundCallbackHander::OnLoopEnd(void* /*bufferContext*/)
	{
	}
	void SoundCallbackHander::OnVoiceError(void* /*bufferContext*/, HRESULT /*error*/)
	{
	}
}

//
// Per sound data required to play a sound
//
struct ImplData
{
	ImplData(BYTE *data,size_t size) :
		sourceVoice(NULL),
		playData(data),
		length(size),
		isPlaying(false),
		callbackHander(&isPlaying)
	{
	}

	~ImplData()
	{
		if (sourceVoice)
		{
			sourceVoice->DestroyVoice();
			sourceVoice = NULL;
		}
	}

	IXAudio2SourceVoice		*sourceVoice;	
	BYTE					*playData;
	size_t					length;
	bool                    isPlaying;
	SoundCallbackHander     callbackHander;
};
typedef std::map<string,ImplData*> SoundMap;
class XAudio2SoundPlayer
{
	//struct ImplData;

public:
	XAudio2SoundPlayer();
	~XAudio2SoundPlayer();

	size_t LoadSound(const wchar_t *szfile);
	void   LoadSound(string name,const wchar_t *szfile);
	size_t AddSound(WAVEFORMATEX* format, BYTE *data,size_t size);
	void   AddSound(string name,WAVEFORMATEX* format, BYTE *data,size_t size);
	bool   PlaySound(size_t index,int loopFlag = XAUDIO2_NO_LOOP_REGION);
	bool   PlaySound(string name,int loopFlag = XAUDIO2_NO_LOOP_REGION);
	bool   StopSound(size_t index);
	bool   StopSound(string name);
	bool   IsSoundPlaying(size_t index) const;
	bool   IsSoundPlaying(string name ) ;
	size_t GetSoundCount() const;

	void Suspend();
	void Resume();

private:
	HRESULT CreateDevice();
	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);

	IXAudio2*					audioEngine;
	IXAudio2MasteringVoice*     masteringVoice;

	WAVEFORMATEXTENSIBLE		wfx;
	XAUDIO2_BUFFER				buffer;

	std::vector<ImplData*>		soundList;
	SoundMap					soundMap;
	


};

