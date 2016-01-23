#pragma once

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Symphony
{
    class Transform
    {
        //friend class GameObject;
    public:

        Transform();
        ~Transform();
        
        glm::vec3 position;
        glm::vec3 scale;
        glm::quat orientation;
        glm::mat3x3 localTransformMatrix, worldTransformMatrix;
    };
}