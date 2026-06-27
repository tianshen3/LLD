#pragma once
#include "../model/song.hpp";
#include "IAudioOutputDevice.hpp";
#include "../external/WiredSpeakerAPI.hpp";

using namespace std;

class WiredSpeakerAdapter : public IAudioOutputDevice {
    private:
    WiredSpeakerAPI* wiredspeakerApi;

    public:
    WiredSpeakerAdapter(WiredSpeakerAPI* api){
        wiredspeakerApi = api;
    }

    void playAudio(Song* song) override {
        string payload = song->getTitle() + " by " + song->getArtist();
        wiredspeakerApi->playSoundViaCable(payload);
    }
};
