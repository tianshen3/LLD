#pragma once
#include <iostream>
#include "../device/IAudioOutputDevice.hpp"
#include "../device/BluetoothSpeakerAdapter.hpp"
#include "../device/WiredSpeakerAdapter.hpp"
#include "../device/HeadphonesAdapter.hpp"
#include "../enums/DeviceType.hpp"


class DeviceFactory {
public:
    static IAudioOutputDevice* createDevice(DeviceType deviceType) {
        if (deviceType == DeviceType::BLUETOOTH) {
            return new BluetoothSpeakerAdapter(new BluetoothSpeakerAPI());
        }
        else if (deviceType == DeviceType::WIRED) {
            return new WiredSpeakerAdapter(new WiredSpeakerAPI());
        } 
        else { // HEADPHONES
            return new HeadPhonesAdapter(new HeadPhonesAPI());
        }
    }
};