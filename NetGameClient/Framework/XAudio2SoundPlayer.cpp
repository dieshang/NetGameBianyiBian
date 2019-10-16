//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved


#include "XAudio2SoundPlayer.h"


#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif






//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer constructor
// Desc: Setup common XAudio2 objects:
//          XAudio2Engine
//          Mastering Voice
//--------------------------------------------------------------------------------------
XAudio2SoundPlayer::XAudio2SoundPlayer() 
{
	// Create the XAudio2 Engine
	HRESULT hr;
	if (hr = FAILED(this->CreateDevice()))
	{
			// Set a breakpoint on this line to catch DX API errors.
		std::exception e("error",hr);
		throw e;
	}


}

//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer destructor
// Desc: Stop all playing sounds, cleanup per sound data, and destroy XAudio object.
//          XAudio2Engine
//          Mastering Voice
//--------------------------------------------------------------------------------------
XAudio2SoundPlayer::~XAudio2SoundPlayer()
{
	for(SoundMap::iterator ite = soundMap.begin();ite!=soundMap.end();++ite)
	{
		ImplData *data = ite->second;
		delete []data->playData;
		data->sourceVoice->DestroyVoice();
	}
	if (masteringVoice != NULL)
	{
		masteringVoice->DestroyVoice();
	}

	if (audioEngine != NULL)
	{
		audioEngine->Release();
		audioEngine = NULL;
	}
}

HRESULT XAudio2SoundPlayer::CreateDevice()
{
	HRESULT hr = S_OK;
	if (FAILED(hr = XAudio2Create( &audioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR ) ) )
	{
		return hr;
	}
	if ( FAILED(hr = audioEngine->CreateMasteringVoice( &masteringVoice) ) )
	{
		return hr;
	}

	return hr;
}


HRESULT XAudio2SoundPlayer::FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if( 0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );

		if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );

		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if( 0 == ReadFile( hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL ) )
				hr = HRESULT_FROM_WIN32( GetLastError() );
			break;

		default:
			if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT ) )
				return HRESULT_FROM_WIN32( GetLastError() );            
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;

	}

	return S_OK;
}

HRESULT XAudio2SoundPlayer::ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, bufferoffset, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	DWORD dwRead;
	if( 0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL ) )
		hr = HRESULT_FROM_WIN32( GetLastError() );
	return hr;
}
size_t XAudio2SoundPlayer::LoadSound(const wchar_t *szfile)
{
	HANDLE hFile = CreateFile(
		szfile,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL );

	if( INVALID_HANDLE_VALUE == hFile )
		return -1;//HRESULT_FROM_WIN32( GetLastError() );

	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return -1;//HRESULT_FROM_WIN32( GetLastError() );

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile,fourccRIFF,dwChunkSize, dwChunkPosition );
	DWORD filetype;
	ReadChunkData(hFile,&filetype,sizeof(DWORD),dwChunkPosition);
	if (filetype != fourccWAVE)
		return S_FALSE;
	FindChunk(hFile,fourccFMT, dwChunkSize, dwChunkPosition );
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition );

	FindChunk(hFile,fourccFMT, dwChunkSize, dwChunkPosition );
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition );
	
	FindChunk(hFile,fourccDATA,dwChunkSize, dwChunkPosition );
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	return this->AddSound((WAVEFORMATEX*)&wfx,pDataBuffer,dwChunkSize);
	//buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	//buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	//buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer


}

void XAudio2SoundPlayer::LoadSound(string name ,const wchar_t *szfile)
{
	HANDLE hFile = CreateFile(
		szfile,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL );

	if( INVALID_HANDLE_VALUE == hFile )
		return ;//HRESULT_FROM_WIN32( GetLastError() );

	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return ;//HRESULT_FROM_WIN32( GetLastError() );

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile,fourccRIFF,dwChunkSize, dwChunkPosition );
	DWORD filetype;
	ReadChunkData(hFile,&filetype,sizeof(DWORD),dwChunkPosition);
	if (filetype != fourccWAVE)
		return ;
	FindChunk(hFile,fourccFMT, dwChunkSize, dwChunkPosition );
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition );

	FindChunk(hFile,fourccFMT, dwChunkSize, dwChunkPosition );
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition );
	
	FindChunk(hFile,fourccDATA,dwChunkSize, dwChunkPosition );
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	AddSound(name,(WAVEFORMATEX*)&wfx,pDataBuffer,dwChunkSize);
	//buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	//buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	//buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer


}
//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::AddSound
// Desc: Create data, create voice, store data
//--------------------------------------------------------------------------------------
size_t XAudio2SoundPlayer::AddSound(
		WAVEFORMATEX*  format,
		BYTE	*data,
		size_t	size
	)
{
	//
	// Allocate the implementation data
	//
	//std::shared_ptr<ImplData> implData(new ImplData(data));
	ImplData *implData = new ImplData(data,size);
	//
	// Create the source voice
	//
	audioEngine->CreateSourceVoice(
		&implData->sourceVoice,
		format,
		0,
		XAUDIO2_DEFAULT_FREQ_RATIO,
		reinterpret_cast<IXAudio2VoiceCallback*>(&implData->callbackHander),
		nullptr,
		nullptr
		);


	//
	// Add to the list and return its index
	//
	soundList.push_back(implData);
	return (soundList.size() - 1);
}


//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::AddSound
// Desc: Create data, create voice, store data
//--------------------------------------------------------------------------------------
void XAudio2SoundPlayer::AddSound(
		string			name,
		WAVEFORMATEX	*format,
		BYTE			*data,
		size_t			size
	)
{
	//
	// Allocate the implementation data
	//
	SoundMap::iterator ite = soundMap.find(name);
	if (ite != soundMap.end())
	{
		return;
	}

	ImplData *implData = new ImplData(data,size);
	//
	// Create the source voice
	//
	audioEngine->CreateSourceVoice(
		&implData->sourceVoice,
		format,
		0,
		XAUDIO2_DEFAULT_FREQ_RATIO,
		reinterpret_cast<IXAudio2VoiceCallback*>(&implData->callbackHander),
		nullptr,
		nullptr
		);


	//
	// Add to the list and return its index
	//
	//soundList.push_back(implData);
	soundMap[name] = implData;
	
}
//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::PlaySound
// Desc: Stop if already playing, setup XAudio2 Sound buffer and play
//--------------------------------------------------------------------------------------
bool XAudio2SoundPlayer::PlaySound(size_t index,int loopFlag)
{
	//
	// Setup buffer
	//

	XAUDIO2_BUFFER playBuffer = { 0 };
	ImplData *soundData = soundList[index];
	playBuffer.AudioBytes = soundData->length;
	playBuffer.pAudioData = soundData->playData;
	playBuffer.Flags = XAUDIO2_END_OF_STREAM;
	playBuffer.LoopCount = loopFlag;

	//
	// In case it is playing, stop it and flush the buffers.
	//
	HRESULT hr = soundData->sourceVoice->Stop();
	if (SUCCEEDED(hr))
	{
		hr = soundData->sourceVoice->FlushSourceBuffers();
	}

	//
	// Submit the sound buffer and (re)start (ignore any 'stop' failures)
	//
	hr = soundData->sourceVoice->SubmitSourceBuffer(&playBuffer);
	if (SUCCEEDED(hr))
	{
		hr = soundData->sourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
	}

	return SUCCEEDED(hr);
}


//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::PlaySound
// Desc: Stop if already playing, setup XAudio2 Sound buffer and play
//--------------------------------------------------------------------------------------
bool XAudio2SoundPlayer::PlaySound(string name,int loopFlag)
{
	//
	// Setup buffer
	//
	SoundMap::iterator ite = soundMap.find(name);
	if (ite == soundMap.end())
	{
		return false;
	}
	XAUDIO2_BUFFER playBuffer = { 0 };

	ImplData *soundData = ite->second;
	playBuffer.AudioBytes = soundData->length;
	playBuffer.pAudioData = soundData->playData;
	playBuffer.Flags = XAUDIO2_END_OF_STREAM;
	playBuffer.LoopCount = loopFlag;

	//
	// In case it is playing, stop it and flush the buffers.
	//
	HRESULT hr = soundData->sourceVoice->Stop();
	if (SUCCEEDED(hr))
	{
		hr = soundData->sourceVoice->FlushSourceBuffers();
	}

	//
	// Submit the sound buffer and (re)start (ignore any 'stop' failures)
	//
	hr = soundData->sourceVoice->SubmitSourceBuffer(&playBuffer);
	if (SUCCEEDED(hr))
	{
		hr = soundData->sourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
	}

	return SUCCEEDED(hr);
}
//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::StopSound
// Desc: Stop if playing
//--------------------------------------------------------------------------------------
bool XAudio2SoundPlayer::StopSound(size_t index)
{
	ImplData *soundData = soundList[index];

	HRESULT hr = soundData->sourceVoice->Stop();
	if (SUCCEEDED(hr))
	{
		hr = soundData->sourceVoice->FlushSourceBuffers();
	}

	return SUCCEEDED(hr);
}
//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::StopSound
// Desc: Stop if playing
//--------------------------------------------------------------------------------------
bool XAudio2SoundPlayer::StopSound(string name)
{

	SoundMap::iterator ite = soundMap.find(name);
	if (ite == soundMap.end())
	{
		return false;
	}
	ImplData *soundData =ite->second;

	HRESULT hr = soundData->sourceVoice->Stop();
	if (SUCCEEDED(hr))
	{
		hr = soundData->sourceVoice->FlushSourceBuffers();
	}

	return SUCCEEDED(hr);
}



//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::IsSoundPlaying
// Desc: Returns the playing state of the sound at sent index
//--------------------------------------------------------------------------------------
bool XAudio2SoundPlayer::IsSoundPlaying(size_t index) const
{
	return soundList[index]->isPlaying;
}


//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::IsSoundPlaying
// Desc: Returns the playing state of the sound at sent index
//--------------------------------------------------------------------------------------
bool XAudio2SoundPlayer::IsSoundPlaying(string name) 
{

	SoundMap::iterator ite = soundMap.find(name);
	if (ite == soundMap.end())
	{
		return false;
	}
	return ite->second->isPlaying;
}


//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::GetSoundCount
// Desc: Returns the number of sounds in the sound list
//--------------------------------------------------------------------------------------
size_t XAudio2SoundPlayer::GetSoundCount() const
{
	return soundMap.size();//soundList.size();
}

//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::Suspend
// Desc: Stops the XAudio2 Engine
//--------------------------------------------------------------------------------------
void XAudio2SoundPlayer::Suspend()
{
	audioEngine->StopEngine();
}

//--------------------------------------------------------------------------------------
// Name: XAudio2SoundPlayer::Resume
// Desc: Start the XAudio2 engine
//--------------------------------------------------------------------------------------
void XAudio2SoundPlayer::Resume()
{
	audioEngine->StartEngine();

}
