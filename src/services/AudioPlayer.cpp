#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() : patchCord(player, 0, audioOut, 0) {
    AudioMemory(10);
}

void AudioPlayer::play(const unsigned int *sample) {
    if (player.isPlaying()) {
        player.stop();
    }

    player.play(sample);
}

void AudioPlayer::stop() {
    player.stop();
}