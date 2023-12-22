#include "Adafruit_Arcada.h"

#include "../globals.h"
#include "Scene.h"
#include "FileSystemManager.h"
#include "Leaderboard.h"
#include "ButtonManager.h"
#include "MuteManager.h"


class Game {
public:
    Adafruit_Arcada arcada;
    GFXcanvas16 *canvas;
    Scene* currentScene;
    FileSystemManager* files;
    Leaderboard* leaderboard;
    ButtonManager* buttons;
    MuteManager* mute;

    Scene* currentScene;

    Game();
    ~Game();
    void setup();
    void loop();
    void switchTo(Scene* scene);
};