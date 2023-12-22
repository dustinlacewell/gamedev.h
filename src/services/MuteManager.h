#include "Adafruit_Arcada.h"
#include "FileSystemManager.h"
#include "ButtonManager.h"

// MuteManager.h
class MuteManager {
private:
    bool muted;
    FileSystemManager* files;
    ButtonManager* buttons;
    Adafruit_Arcada* arcada;

public:
    MuteManager(Adafruit_Arcada* arcada, FileSystemManager* files, ButtonManager* buttons);
    void toggle();
    bool getMute();
    void setMute(bool muted);
    void update();
    void loadMute();
    void persistMute();
};
