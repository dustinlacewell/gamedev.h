#pragma once

class Scene {
public:
    virtual void setup(void) = 0; // Pure virtual function
    virtual void loop(unsigned long dt) = 0;   // Pure virtual function
};