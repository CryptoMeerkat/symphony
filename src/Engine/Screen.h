#pragma once

#include <iostream>

namespace Symphony
{
    class Screen
    {
        public:
            static void SetResolution(int newWidth, int newHeight, bool fullscreen)
            {
                fullscreen = fullscreen;
                SetResolution(newWidth, newHeight);
            }

            static void SetResolution(int newWidth, int newHeight)
            {
                if (newHeight == 0)
                {
                    std::cerr << "Invalid value for screen height: Height can't be zero" << std::endl;
                    newHeight = 1;
                }

                width = newWidth;
                height = newHeight;

                halfWidth = width * 0.5f;
                halfHeight = height * 0.5f;
                aspectRatio = halfWidth / halfHeight;
            }

            inline static int Width() { return width; }
            inline static int Height() { return height; }

            inline static float HalfWidth() { return halfWidth; }
            inline static float HalfHeight() { return halfHeight; }
            inline static float AspectRatio() { return aspectRatio; }

        protected:
            static int width;
            static int height;
            static bool fullscreen;

            static float aspectRatio;
            static float halfWidth;
            static float halfHeight;
    };
}