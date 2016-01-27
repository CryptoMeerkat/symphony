#include "Camera.h"

#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "SymphonyEngine.h"

namespace Symphony
{
    const float Camera::DEFAULT_ZNEAR = 0.1f;
    const float Camera::DEFAULT_ZFAR = 1000.0f;
    const glm::vec4 Camera::DEFAULT_CLEAR_COLOR = Color::Grey();

    Camera::Camera()
        : Camera(DEFAULT_CLEAR_COLOR, DEFAULT_ZNEAR, DEFAULT_ZFAR, ViewPort::FullScreen())
    {
    }

    Camera::Camera(glm::vec4 clearColor, float nPlane, float zPlane, ViewPort vPort)
    {
        nearPlane = DEFAULT_ZNEAR;
        farPlane = DEFAULT_ZFAR;
        clearColor = DEFAULT_CLEAR_COLOR;
        viewPort = vPort;

        useAlphaBlending = false;
        useDepthBuffer = false;
        useFrustumCulling = false;
        typeOfAlphaBlending = 0;
    }

    void Camera::AdaptToResize(int newWidth, int newHeight)
    {
        //Set the camera's local viewport variable
        viewPort.width = newWidth;
        viewPort.height = newHeight;

        //set the GL viewport size
        glViewport(viewPort.startX, viewPort.startY, viewPort.width, viewPort.height);
    }

    //TO-DO: If the view doesn't change, it could be cached instead of generating it everytime
    /*
    Generates a view matrix for the camera's viewpoint. This matrix can be sent
    straight to the shader...it's already an 'inverse camera' matrix.
    */
    glm::mat4 Camera::BuildViewMatrix()
    {
        //Why do a complicated matrix inversion, when we can just generate the matrix
        //using the negative values ;). The matrix multiplication order is important!
        return glm::rotate(-Pitch(), glm::vec3(1.f, 0.f, 0.f))
             * glm::rotate(-Yaw(), glm::vec3(0.f, 1.f, 0.f))
             * glm::translate(-transform.GetPosition());
    }

    void Camera::LoadRenderPreferences()
    {
        //Set background color
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);

        //clear the colour and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        useDepthBuffer ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

        //useAlphaBlending ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
        /*switch (typeOfAlphaBlending)
        {
            case 0: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
            case 1: glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR); break;
            case 2: glBlendFunc(GL_ONE, GL_ZERO); break;
            case 3: glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
        }*/
        
        ResetCulling();
    }

    void Camera::ResetCulling()
    {
        switch (typeOfFaceculling)
        {
            case FaceCulling::NONE:
                glDisable(GL_CULL_FACE);
                break;
            case FaceCulling::FRONT:
                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT);
                break;
            case FaceCulling::BACK:
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                break;
            case FaceCulling::BOTH:
                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT_AND_BACK);
                break;
        }
    }
    
    void Camera::Update(float deltaTime)
    {
        transform.Rotate(glm::vec3(-1, 0, 0) * SymphonyEngine::GetMouse()->RelativePosition().y);
        transform.Rotate(glm::vec3(0, -1, 0) * SymphonyEngine::GetMouse()->RelativePosition().x);
    }
}