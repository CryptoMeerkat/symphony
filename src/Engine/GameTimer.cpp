#include "GameTimer.h"

namespace Symphony
{
    GameTimer::GameTimer()
    {
        QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);

        lastTime = GetMS();
        div1000ByFreq = 1000.0 / (double)frequency.QuadPart;
    }

    /*
    Returns the Milliseconds since timer was started
    */
    float GameTimer::GetMS()
    {
        LARGE_INTEGER t;
        QueryPerformanceCounter(&t);
        return (float)((t.QuadPart - start.QuadPart) * div1000ByFreq); // 1000.0 / frequency.QuadPart);
    }

    float GameTimer::GetTimedMS()
    {
        float a = GetMS();
        float b = a - lastTime;
        lastTime = a;
        return b;
    }
}