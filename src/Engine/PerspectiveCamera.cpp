#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Symphony
{
    const float PerspectiveCamera::DEFAULT_FOV = 45.0f;

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
}

