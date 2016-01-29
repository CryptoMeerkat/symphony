#include "PerspectiveCamera.h"

#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SymphonyEngine.h"


namespace Symphony
{
    const float PerspectiveCamera::DEFAULT_FOV = 60.0f;

    PerspectiveCamera::PerspectiveCamera()
        : PerspectiveCamera(DEFAULT_FOV, 1.f)
    {
    }

    PerspectiveCamera::PerspectiveCamera(float fov, float aspect)
        : Camera()
    {
        fieldOfView = fov;
        aspectRatio = aspect;

        projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    }

    PerspectiveCamera::PerspectiveCamera(glm::vec4 clearColor, float nPlane, float zPlane, float fov, float aspect)
        : Camera(clearColor, nPlane, zPlane)
    {
        fieldOfView = fov;
        aspectRatio = aspect;
        
        projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    }

    Symphony::PerspectiveCamera::~PerspectiveCamera()
    {
    }

    void PerspectiveCamera::AdaptToResize(int newWidth, int newHeight)
    {
        Camera::AdaptToResize(newWidth, newHeight);
        
        aspectRatio = viewPort.AspectRatio();
        projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    }

    void PerspectiveCamera::Update(float deltaTime)
    {
        //transform.Rotate(glm::vec3(0, 1, 0) * (1.f * deltaTime));
        float speed = 90.f; // *deltaTime;
        if (SymphonyEngine::GetKeyboard()->GetKeyDown(SDL_SCANCODE_RIGHT))
        {
            glm::vec3 r = glm::vec3(0, -speed, 0);
            transform.Rotate(r);
        }
        else if (SymphonyEngine::GetKeyboard()->GetKeyDown(SDL_SCANCODE_LEFT))
        {
            glm::vec3 r = glm::vec3(0, speed, 0);
            transform.Rotate(r);
        }
        if (SymphonyEngine::GetKeyboard()->GetKeyDown(SDL_SCANCODE_UP))
        {
            glm::vec3 r = glm::vec3(speed, 0, 0);
            transform.Rotate(r);
        }
        else if (SymphonyEngine::GetKeyboard()->GetKeyDown(SDL_SCANCODE_DOWN))
        {
            glm::vec3 r = glm::vec3(-speed, 0, 0);
            transform.Rotate(r);
        }
        std::cout << "===" << std::endl;
        std::cout << "Quat: " << glm::to_string(transform.GetOrientation()) << std::endl;
        std::cout << "Euler: " << glm::to_string(glm::degrees(glm::eulerAngles(transform.GetOrientation()))) << std::endl;
    }
}

