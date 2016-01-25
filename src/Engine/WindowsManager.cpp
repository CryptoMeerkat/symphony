#include "WindowManager.h"

#include <iostream>
#include "Screen.h"

namespace Symphony
{
    WindowManager::WindowManager()
    {
        windowHandle = nullptr;
        oglContextHandler = nullptr;
    }

    WindowManager::~WindowManager()
    {
        SDL_DestroyWindow(windowHandle);
        windowHandle = nullptr;

        SDL_GL_DeleteContext(oglContextHandler);
        oglContextHandler = nullptr;
    }

    bool WindowManager::Initialise(const char* windowsName, int initialWidth, int initialHeight, bool fullscreen, bool useVSync, bool trapMouse)
    {
        Screen::SetResolution(initialWidth, initialHeight, fullscreen);

        //Initialization flag
        bool success = true;

        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            //printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            std::cerr << "SDL could not initialize! SDL Error:" << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Use OpenGL 3.3 core
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


            /* Turn on double buffering with a 24bit Z buffer.
            * You may need to change this to 16 or 32 for your system */
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            //Trap the mouse
            if (trapMouse)
                SDL_SetRelativeMouseMode(SDL_TRUE);

            Uint32 windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
            if (fullscreen) windowsFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN; //SDL_WINDOW_FULLSCREEN_DESKTOP

                                                                           //windowsFlags |= SDL_WINDOW_INPUT_GRABBED;
                                                                           //windowsFlags |= SDL_WINDOW_INPUT_FOCUS;
                                                                           //windowsFlags |= SDL_WINDOW_MOUSE_FOCUS;

                                                                           //Create window
            windowHandle = SDL_CreateWindow(windowsName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, initialWidth, initialHeight, windowsFlags);

            if (windowHandle == NULL)
            {
                printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Create context
                oglContextHandler = SDL_GL_CreateContext(windowHandle);

                if (oglContextHandler == NULL)
                {
                    std::cerr << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
                    success = false;
                }
                else
                {
                    //Initialize GLEW
                    glewExperimental = GL_TRUE;

                    //WARNING: https://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW_.28OpenGL_Extension_Wrangler.29
                    //This is triggering a GL_INVALID_ENUM
                    GLenum glewError = glewInit();

                    if (glewError != GLEW_OK)
                    {
                        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
                        success = false;
                    }

                    //Use Vsync
                    if (SDL_GL_SetSwapInterval(useVSync ? 1 : 0) < 0)
                    {
                        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                    }

                    //Initialize OpenGL
                    /*if (!initGL())
                    {
                    printf("Unable to initialize OpenGL!\n");
                    success = false;
                    }*/

                    //print information on screen
                    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
                    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
                    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
                    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
                    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;
                }
            }
        }

        return success;
    }
}