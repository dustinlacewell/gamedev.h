#include "Leaderboard.h"

Leaderboard::Leaderboard(FileSystemManager* files, String filename, int maxScores)
: files(files), filename(filename), maxScores(maxScores)
{
    highscores = new int[maxScores];
    for (int i = 0; i < maxScores; ++i)
    {
        highscores[i] = 0;
    }
}

Leaderboard::~Leaderboard()
{
    delete[] highscores;
}

int Leaderboard::submitScore(int newScore)
{
    bool isHighScore = false;
    int pos;
    for (pos = 0; pos < maxScores; pos++)
    {
        if (newScore > highscores[pos])
        {
            isHighScore = true;
            break;
        }
    }

    if (isHighScore)
    {
        for (int i = maxScores - 1; i > pos; --i)
        {
            highscores[i] = highscores[i - 1];
        }
        Serial.println("Inserting new score" + String(newScore) + " at position " + String(pos));
        highscores[pos] = newScore;
        saveScores();
    } else {
        pos = -1;
    }

    return pos;
}

void Leaderboard::resetScores()
{
    for (int i = 0; i < maxScores; ++i)
    {
        highscores[i] = 0;
    }
    Serial.println("Highscores reset.");
    Serial.println("Highscores:");
    for (int i = 0; i < maxScores; ++i)
    {
        Serial.println(highscores[i]);
    }
    saveScores();
}

const int* Leaderboard::getHighScores() const
{
    return highscores;
}

void Leaderboard::loadScores()
{
    if (files->readBinaryFile(filename, (uint8_t*)highscores, maxScores * sizeof(int)))
    {
        Serial.println("High scores:");
        for (int i = 0; i < maxScores; ++i)
        {
            Serial.println(highscores[i]);
        }
    } else {
        Serial.println("Failed to load high scores!");
    }
}

void Leaderboard::saveScores()
{
    if (files->writeBinaryFile(filename, (uint8_t*)highscores, maxScores * sizeof(int)))
    {
        Serial.println("Highscores saved.");
    } else {
        Serial.println("Failed to save high scores!");
    }
}