#pragma once
#include "../model/Song.hpp";

class IAudioOutputDevice {
    public:
    virtual ~IAudioOutputDevice() {}
    virtual void playAudio(Song* song)=0;
};