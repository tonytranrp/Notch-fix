#pragma once
#include <iostream>
#include <xaudio2.h>
#include "Network.h"
#include "FileSystem.h"
#include "../../Utils/Logger.h"
#ifdef _XBOX
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif
class AudioSystem {
private:
    HRESULT hr;
    IXAudio2* pXAudio2;
    IXAudio2MasteringVoice* pMasterVoice;
    HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);
public:
    AudioSystem();
    static AudioSystem getInstance() {
        AudioSystem audio;
        return audio;
    }
    int play(std::string file, float volume = 1, bool ShouldLoop = false);
    std::string BasePath;
};