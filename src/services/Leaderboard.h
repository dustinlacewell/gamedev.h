#pragma once

#include <Arduino.h>
#include "FileSystemManager.h"

class Leaderboard
{
private:
    int *highscores;
    FileSystemManager *files;
    String filename;
    int maxScores;

    void saveScores();

public:
    Leaderboard(FileSystemManager *files, String filename, int maxScores);
    ~Leaderboard();
    int submitScore(int newScore);
    void resetScores();
    const int *getHighScores() const;
    void loadScores();
};