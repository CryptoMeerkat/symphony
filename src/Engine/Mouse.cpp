#include "Mouse.h"

#include <SDL2\SDL.h>

namespace Symphony
{
    Mouse::Mouse()
    {
        //A memset might be useful here instead
        for (int i = 0; i < Button::MAX; ++i)
        {
            buttonState[i] = false;
            buttonHoldState[i] = false;
            buttonClickState[i] = false;
        }
    }

    Mouse::~Mouse()
    {
    }

    void Mouse::Update(float deltaTime) //int currentX, int currentY, int deltaX, int deltaY)
    {
        int absoluteX, absoluteY;
        Uint32 currentAbsoluteState = SDL_GetMouseState(&absoluteX, &absoluteY);

        int relativeX, relativeY;
        Uint32 currentRelativeState = SDL_GetRelativeMouseState(&relativeX, &relativeY);

        /*std::cout << "Delta: " << Vector2(relativeX, relativeY) << std::endl;
        std::cout << "Absolute: " << Vector2(absoluteX, absoluteY) << std::endl << std::endl << std::endl;*/
        //std::cout << "Absolute: " << Vector2(absoluteX, absoluteY) << std::endl << std::endl << std::endl;

        buttonState[Button::LEFT] = currentAbsoluteState & SDL_BUTTON(SDL_BUTTON_LEFT);
        buttonState[Button::RIGHT] = currentAbsoluteState & SDL_BUTTON(SDL_BUTTON_RIGHT);
        buttonState[Button::MIDDLE] = currentAbsoluteState & SDL_BUTTON(SDL_BUTTON_MIDDLE);

        for (int i = 0; i < Button::MAX; ++i)
        {
            buttonHoldState[i] &= buttonState[i];
            buttonClickState[i] = buttonState[i] & !buttonHoldState[i];
        }

        //std::cout << "Left state: " << buttonState[Button::LEFT] << std::endl;
        //std::cout << "Left hold state: " << buttonHoldState[Button::LEFT] << std::endl;

        relativePosition.x = relativeX; // -absolutePosition.x;
        relativePosition.y = relativeY; // -absolutePosition.y;
        relativePosition *= sensitivity;

        absolutePosition.x = absoluteX;
        absolutePosition.y = absoluteY;

        //std::cout << "Delta: " << relativePosition << std::endl;

        /*absolutePosition.x = currentX;
        absolutePosition.y = currentY;

        relativePosition.x = deltaX;
        relativePosition.y = deltaY;*/

        /*absolutePosition.x = std::fmaxf(absolutePosition.x, 0.0f);
        absolutePosition.x = std::fminf(absolutePosition.x, Symphony::Screen::Width());

        absolutePosition.y = std::fmaxf(absolutePosition.y, 0.0f);
        absolutePosition.y = std::fminf(absolutePosition.y, Symphony::Screen::Height());*/

        //std::cout << relativePosition << std::endl;

        /*relativePosition.x = (currentX - absolutePosition.x) * sensitivity;
        relativePosition.y = (currentY - absolutePosition.y) * sensitivity;


        absolutePosition += relativePosition;*/
    }
}