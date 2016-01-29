/******************************************************************************
Original Author: Rich Davison
Description: Wraps Windows PerformanceCounter. GameTimers keep track of how much
             time has passed since they were last polled.
TO-DO: Find an alternative for non-Windows contexts
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <io.h>
#include <stdio.h>

namespace Symphony
{
    class GameTimer
    {
        public:
            GameTimer();
            ~GameTimer() {}

            //How many milliseconds have passed since the GameTimer was created
            float GetMS();

            //How many milliseconds have passed since GetTimedMS was last called
            float GetTimedMS();

            inline float GetDeltaTime()
            {
                return GetTimedMS() / 1000.0f;
            }

        protected:
            LARGE_INTEGER    start;            //Start of timer
            LARGE_INTEGER    frequency;        //Ticks Per Second

            float lastTime;                    //Last time GetTimedMS was called
            double div1000ByFreq;              //Caches a common operation over `frequency`
    };
}