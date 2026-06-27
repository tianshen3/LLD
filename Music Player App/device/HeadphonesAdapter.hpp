#pragma once
#include "../model/song.hpp";
#include "IAudioOutputDevice.hpp";
#include "../external/HeadPhonesAPI.hpp";

using namespace std;

class HeadPhonesAdapter : public IAudioOutputDevice {
    private:
    HeadPhonesAPI* headphonesApi;

    public:
    HeadPhonesAdapter(HeadPhonesAPI* api){
        headphonesApi = api;
    }

    void playAudio(Song* song) override {
        string payload = song->getTitle() + " by " + song->getArtist();
        headphonesApi->playSoundViaJack(payload);
    }
};
