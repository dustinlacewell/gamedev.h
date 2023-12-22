#pragma once

#include <Adafruit_Arcada.h>

class ButtonManager
{
private:
  uint32_t lastButtonState;
  uint32_t currentButtonState;
  Adafruit_Arcada* arcada;

public:
  ButtonManager(Adafruit_Arcada* arcada);

  void update();

  bool pressed(uint32_t buttonMask);

  bool held(uint32_t buttonMask);

  bool released(uint32_t buttonMask);
};
