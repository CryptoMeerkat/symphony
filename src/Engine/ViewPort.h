#pragma once

#include "Screen.h"

namespace Symphony
{
    //TO-DO: https://www.khronos.org/opengles/sdk/docs/man/xhtml/glScissor.xml
    struct ViewPort
    {
        int startX, startY;

        int width, height;

        ViewPort() : ViewPort(0, 0, 1, 1) {}

        ViewPort(ViewPort& vp) : ViewPort(vp.startX, vp.startY, vp.width, vp.height) {}

        ViewPort(int x, int y, int w, int h)
        {
            startX = x;
            startY = y;
            width = w;
            height = h;
        }

        inline float AspectRatio() const { return (float)width / (float)height; }

        inline static ViewPort FullScreen() { return ViewPort(0, 0, Screen::Width(), Screen::Height()); }
    };
}