#pragma once

#include <queue>
#include "WindowManager.h"
#include "GameTimer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Scene.h"

namespace Symphony
{
    class SymphonyEngine
    {
        public:
            bool InitialiseWindow(const char* windowsName, int initialWidth, int initialHeight,
                                  bool isFullscreen = false, bool useVSync = true);
            
            void Run();

            void AddScene(Scene* newScene)
            {
                if (newScene)
                {
                    newScene->SetID(scenes.size());
                    scenes.push(newScene);
                }
            }

            void NextScene()
            {
                //TO-DO: The current scene should be deleted
                
                delete currentScene;
                
                if (scenes.empty())
                {
                    std::cout << "No more scenes in the queue" << std::endl;
                    currentScene = nullptr;
                    gameLoopIsActive = false;
                    return;
                }

                currentScene = scenes.front();
                scenes.pop();
                
                std::cout << "Loading scene #" << currentScene->GetID() << std::endl;
                std::cout << scenes.size() << " scenes remaining" << std::endl;
            }

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

            void LoadDefaultShaders();
            
            SymphonyEngine();
            ~SymphonyEngine();

        //Protected static
        protected:            
            Scene* currentScene;
            std::queue<Scene*> scenes;

            static SymphonyEngine*  instance;
            static GameTimer*       gameTimer;
            static Keyboard*        keyboard;
            static Mouse*           mouse;
    };
}