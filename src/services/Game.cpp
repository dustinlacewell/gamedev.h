#include "Game.h"

Game::Game()
{
    this->arcada = Adafruit_Arcada();
    this->files = new FileSystemManager();
    this->leaderboard = new Leaderboard(this->files, "/leaderboard.bin", 5);
    this->buttons = new ButtonManager(&this->arcada);
    this->mute = new MuteManager(&this->arcada, this->files, this->buttons);
}

Game::~Game()
{
    delete this->leaderboard;
    delete this->files;
}

void Game::setup()
{
    Serial.begin(9600);

    delay(100);

    Serial.println("Game initializing...");

    if (!arcada.arcadaBegin())
    {
        Serial.print("Arcada failed to begin!");
        while (1)
            delay(10);
    }

    arcada.displayBegin();
    arcada.setBacklight(255);
    arcada.enableSpeaker(true);

    files->begin();

    if (arcada.createFrameBuffer(g_width, g_height))
    {
        canvas = arcada.getCanvas();
    }

    mute->loadMute();

    if (arcada.readButtons() & ARCADA_BUTTONMASK_SELECT)
    {
        leaderboard->resetScores();
    }
    else
    {
        leaderboard->loadScores();
    }
}

void Game::switchTo(Scene *scene)
{
    currentScene = scene;
    currentScene->setup();
}
