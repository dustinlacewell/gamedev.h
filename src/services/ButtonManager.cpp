
#include "ButtonManager.h"

ButtonManager::ButtonManager(Adafruit_Arcada* arcada)
: lastButtonState(0), 
  currentButtonState(0),
  arcada(arcada)
{
}

void ButtonManager::update()
{
  // Save the last state
  lastButtonState = currentButtonState;
  // Read the new state
  currentButtonState = arcada->readButtons();
}

bool ButtonManager::pressed(uint32_t buttonMask)
{
  // Check if all specified buttons are pressed this frame and weren't pressed the last frame
  return (currentButtonState & buttonMask) == buttonMask && (lastButtonState & buttonMask) != buttonMask;
}

bool ButtonManager::held(uint32_t buttonMask)
{
  // Check if all specified buttons are pressed this frame and were also pressed the last frame
  return (currentButtonState & buttonMask) == buttonMask && (lastButtonState & buttonMask) == buttonMask;
}

bool ButtonManager::released(uint32_t buttonMask)
{
  // Check if all specified buttons were pressed last frame but not this frame
  return (currentButtonState & buttonMask) != buttonMask && (lastButtonState & buttonMask) == buttonMask;
}