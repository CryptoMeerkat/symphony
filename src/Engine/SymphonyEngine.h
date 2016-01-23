#pragma once

#include "WindowManager.h"
#include "GameTimer.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Symphony
{
    class SymphonyEngine
    {
        public:
            bool InitialiseWindow(const char* windowsName, int initialWidth, int initialHeight,
                                  bool isFullscreen = false, bool useVSync = true);
            
            void Run();

            static SymphonyEngine* Instance()
            {
                if (instance)
                    return instance;

                instance = new SymphonyEngine();
            }
            
            //Provide global access to release/delete this class
            static void Release()
            {
                if (instance)
                {
                    delete instance;
                    instance = nullptr;
                }
            }


            static inline Mouse*        GetMouse()      { return mouse;     }
            static inline Keyboard*     GetKeyboard()   { return keyboard;  }
            static inline GameTimer*    GetGameTimer()  { return gameTimer; }
            
        protected:
            bool gameLoopIsActive;
            WindowManager* windowManager;

            void Update(float deltaTime);
            void Render();
                        
            void Shutdown();
            
            SymphonyEngine();
            ~SymphonyEngine();

        //Protected static
        protected:
            static SymphonyEngine*  instance;
            static GameTimer*       gameTimer;
            static Keyboard*        keyboard;
            static Mouse*           mouse;
    };
}