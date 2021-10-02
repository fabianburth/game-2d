#pragma once
#include <xaudio2.h>

/// <summary>
/// Container for the format and buffer of a audiofile
/// </summary>
struct AudioData {
    WAVEFORMATEXTENSIBLE wfx = {0};
    XAUDIO2_BUFFER buffer = {0};
};
