#pragma once

#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")
#pragma comment(lib, "GLEW/glew32.lib")
#pragma comment(lib, "opengl32.lib")

#include <GLEW\GL\glew.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>

namespace Symphony
{
    class WindowManager
    {
    public:
        WindowManager();
        ~WindowManager();

        bool Initialise(const char* windowsName, int initialWidth, int initialHeight, bool fullscreen = false, bool useVSync = false, bool trapMouse = false);

        inline void SwapBuffers()
        {
            SDL_GL_SwapWindow(windowHandle);
        }

        inline void SetWindowTitle(const char* title)
        {
            SDL_SetWindowTitle(windowHandle, title);
        }
        
    protected:
        //The window we'll be rendering to
        SDL_Window* windowHandle;

        //OpenGL context
        SDL_GLContext oglContextHandler;
    };
}