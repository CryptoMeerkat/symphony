#pragma once

#include "GameObject.h"
#include "ViewPort.h"
#include "Color.h"

namespace Symphony
{
    class Camera : public GameObject
    {
    public:
        enum FaceCulling { NONE, FRONT, BACK, BOTH };

        Camera();
        Camera(glm::vec4 clearColor, float nPlane, float zPlane, ViewPort vPort = ViewPort::FullScreen());
        virtual ~Camera() {};
        
        virtual void Update(float deltaTime);

        inline float Yaw() { return transform.GetRotation().y; }
        inline float Roll() { return transform.GetRotation().z; }
        inline float Pitch() { return transform.GetRotation().x; }
        
        inline void DisableFaceCulling()
        { typeOfFaceculling = FaceCulling::NONE; }

        inline void SetFaceCulling(FaceCulling typeOfCulling)
        { typeOfFaceculling = typeOfCulling; }

        inline void SetFrustumCulling(bool cull)
        { useFrustumCulling = cull; }
        
        inline void ToggleFrustumCulling()
        { useFrustumCulling = !useFrustumCulling; }

        inline void SetDepthBufferUsage(bool useZBuffer)
        { useDepthBuffer = useZBuffer; }

        inline bool ToggleDepthBuffer()
        {
            useDepthBuffer = !useDepthBuffer;
            return useDepthBuffer;
        }

        virtual void AdaptToResize(int newWidth, int newHeight);
        glm::mat4 BuildViewMatrix();

        glm::mat4& GetProjectionMatrix() { return projectionMatrix; }
        
        void LoadRenderPreferences();

    protected:
        static const glm::vec4 DEFAULT_CLEAR_COLOR;
        static const float DEFAULT_ZNEAR, DEFAULT_ZFAR;
        
        float nearPlane, farPlane;

        glm::vec4 clearColor;
        glm::mat4 projectionMatrix, viewMatrix;

        bool useAlphaBlending, //TO-DO: Add alpha blending
             useDepthBuffer,
             useFrustumCulling;

        int typeOfAlphaBlending;
        FaceCulling typeOfFaceculling = FaceCulling::NONE;

        ViewPort viewPort;
        
        void ResetCulling();
    };
    
}