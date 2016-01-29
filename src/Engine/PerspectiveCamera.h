#pragma once

#include "Camera.h"

namespace Symphony
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera();
        PerspectiveCamera(float fov, float aspect);
        PerspectiveCamera(glm::vec4 clearColor, float nPlane, float zPlane, float fov, float aspect);
        ~PerspectiveCamera();
        
        virtual void AdaptToResize(int newWidth, int newHeight) override;
        virtual void Update(float deltaTime) override;

    protected:
        static const float DEFAULT_FOV;
        float fieldOfView, aspectRatio;
    };
}