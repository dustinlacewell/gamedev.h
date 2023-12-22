#include <stdint.h>

#include "MuteManager.h"

MuteManager::MuteManager(
    Adafruit_Arcada* arcada,
    FileSystemManager* files, 
    ButtonManager* buttons
) {
    this->files = files;
    this->buttons = buttons;
    this->muted = false;
}

void MuteManager::toggle() {
    this->setMute(!muted);
}

bool MuteManager::getMute() {
    return muted;
}

void MuteManager::setMute(bool muted) {
    this->muted = muted;
    arcada->enableSpeaker(muted);
    this->persistMute();
}

void MuteManager::update() {
    if (buttons->pressed(ARCADA_BUTTONMASK_SELECT)) {
        toggle();
    }
}

void MuteManager::loadMute() {
    uint8_t mutedArray[1];

    if (files->readBinaryFile("/mute.bin", mutedArray, sizeof(mutedArray))) {
        this->setMute(mutedArray[0] == 1 ? true : false);
    } else {
        Serial.println("Failed to load mute state!");
    }
}

void MuteManager::persistMute() {
    uint8_t t = 1;
    uint8_t f = 0;
    uint8_t mutedArray[1] = { this->muted ? t : f };

    if (files->writeBinaryFile("/mute.bin", mutedArray, sizeof(mutedArray))) {
        Serial.println("Mute state saved.");
    } else {
        Serial.println("Failed to save mute state!");
    }
}