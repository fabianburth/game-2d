#pragma once
#include "AudioData.h"

#include <map>
#include <string>
#include <tchar.h>
#include <xaudio2.h>


class SoundManager {
  private:
    // Storing the instance
    static SoundManager *soundManager;

    
    // Private Constructor to prevent instancing
    SoundManager();

    HRESULT hr = 0;

    // XAudio2 Engine
    IXAudio2 *pXAudio2 = nullptr;
    // Mastering Voice */
    IXAudio2MasteringVoice *pMasterVoice = nullptr;

    std::map<std::string, AudioData> audios;
    std::map<std::string, IXAudio2SourceVoice *> soundeffect;

    HRESULT findChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition);
    HRESULT readChunkData(HANDLE hFile, void *buffer, DWORD buffersize, DWORD bufferoffset);


  public:
    /// <summary>
    /// Returns a pointer to the singleton instance
    /// </summary>
    /// <returns>pointer to the sound manager instance</returns>
    static SoundManager *getInstance();

    /// <summary>
    /// Loads the data of a .wav file into buffer
    /// </summary>
    /// <param name="filePath">filepath to a .wav file</param>
    /// <param name="name">name for the sound to retrieve it later</param>
    /// <param name="loop">determines whether the sound loops once it is started which
    /// is suitable for background music</param>
    /// <returns>error code</returns>
    HRESULT loadAudioData(const TCHAR *filePath, std::string name, bool loop);

    /// <summary>
    /// Plays a sound
    /// </summary>
    /// <param name="name">name of the sound</param>
    /// <returns>error code</returns>
    HRESULT play(std::string name);

    /// <summary>
    /// Stops a sound
    /// </summary>
    /// <param name="name">name of the sound</param>
    /// <returns>error code</returns>
    HRESULT stop(std::string name);
};