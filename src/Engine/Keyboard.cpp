#include "Keyboard.h"

#include <iostream>

namespace Symphony
{
    void Keyboard::Initialise(const Uint8* currentState, unsigned int numberOfKeys)
    {
        this->keystate = currentState;
        this->numberOfKeys = numberOfKeys;

        keystateHold = new Uint8[numberOfKeys];
        keystatePressed = new Uint8[numberOfKeys];
        keystateLifted = new Uint8[numberOfKeys];

        memset(keystateHold, 0, numberOfKeys);
        memset(keystatePressed, 0, numberOfKeys);
        memset(keystateLifted, 0, numberOfKeys);
    }

    void Keyboard::Update()//unsigned int numKeys)
    {
        /*delete[] keystate;
        keystate = new Uint8[numKeys];
        memcpy(keystate, currentState, numKeys);
        return;*/

        for (unsigned int i = 0; i < numberOfKeys; ++i)
        {
            keystateLifted[i] = !keystate[i] & keystateHold[i];
            keystateHold[i] &= keystate[i];
            keystatePressed[i] = keystate[i] & !keystateHold[i];
        }
    }
}