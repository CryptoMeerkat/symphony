#pragma once

#include <SDL2\SDL.h>

namespace Symphony
{
    class Keyboard
    {
        friend class SymphonyEngine;

        public:
            Keyboard()
            {
                keystate = nullptr;
                numberOfKeys = 0;
            }

            ~Keyboard() {};

            void Initialise(const Uint8* currentState, unsigned int numberOfKeys);

            void Update();

            inline void Clear()
            {
                for (unsigned int i = 0; i < numberOfKeys; ++i)
                {
                    keystateHold[i] = keystate[i];
                }
            }

            //TO-DO: Could this be optimised and not be O(N)?
            inline bool AnyKey()
            {
                for (unsigned int i = 0; i < numberOfKeys; ++i)
                {
                    if (keystateHold[i])
                        return true;
                }
                return false;
            }

            inline bool GetKey(SDL_Scancode key)
            {
                return keystate[key];
            }

            inline bool GetKeyHold(SDL_Scancode key)
            {
                return keystate[key];
            }

            inline bool GetKeyDown(SDL_Scancode key)
            {
                return keystatePressed[key];
            }

            inline bool GetKeyUp(SDL_Scancode key)
            {
                return keystateLifted[key];
            }

        protected:
            const Uint8* keystate;
            Uint8* keystateHold;
            Uint8* keystatePressed;
            Uint8* keystateLifted;
            unsigned int numberOfKeys;
    };
}