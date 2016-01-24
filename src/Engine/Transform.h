#pragma once

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Symphony
{
    class Transform
    {
        //friend class GameObject;
    public:

        Transform();
        ~Transform();
        
        inline void SetPosition(glm::vec3 newPosition)
        {
            localTransformMatrix[3][0] = newPosition.x;
            localTransformMatrix[3][1] = newPosition.y;
            localTransformMatrix[3][2] = newPosition.z;
        }

        inline glm::vec3 Position() const
        {
            //TO-DO: This should use `worldTransformMatrix`
            return glm::vec3(localTransformMatrix[3]);
        }
        
        inline void Translate(glm::vec3 deltaPosition)
        {
            localTransformMatrix = glm::translate(localTransformMatrix, deltaPosition);
        }
        
        inline void Rotate(glm::vec3 axis, float angles)
        {
            localTransformMatrix = glm::rotate(localTransformMatrix, angles, axis);
        }

    protected:
        glm::mat4x4 localTransformMatrix, worldTransformMatrix;
    };
}