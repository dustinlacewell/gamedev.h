#pragma once

#include <Audio.h>

class AudioPlayer {
private:
    AudioPlayMemory player;
    AudioOutputAnalogStereo audioOut;
    AudioConnection patchCord;

public:
    AudioPlayer();
    void play(const unsigned int *sample);
    void stop();
};
