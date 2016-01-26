#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
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


        #pragma region Position

        inline glm::vec3 GetPosition() const { return position; }

        inline void SetPosition(glm::vec3 newPosition)
        {
            position = newPosition;
            localTransformNeedsUpdate = true;
        }

        inline void Translate(glm::vec3 deltaPosition)
        {
            position += deltaPosition;
            localTransformNeedsUpdate = true;
        }

        #pragma endregion
        
        
        #pragma region Scale

        inline glm::vec3 GetScale() const { return scale; }

        inline void SetScale(glm::vec3 newScale) 
        {
            scale = newScale;
            localTransformNeedsUpdate = true;
        }

        inline void Scale(glm::vec3 deltaScale)
        {
            scale.x *= deltaScale.x;
            scale.y *= deltaScale.y;
            scale.z *= deltaScale.z;
            localTransformNeedsUpdate = true;
        }
        
        inline void Scale(float scaleFactor)
        {
            scale *= scaleFactor;
            localTransformNeedsUpdate = true;
        }
        
        #pragma endregion


        #pragma region Rotation

        inline glm::vec3 GetRotation()
        {
            return eulerRotation;
        }

        inline void SetRotation(glm::vec3 newRotation)
        {
            eulerRotation = newRotation;
            orientation = glm::quat(eulerRotation);
            localTransformNeedsUpdate = true;
        }

        inline void Rotate(glm::vec3 deltaRotation)
        {
            eulerRotation += deltaRotation;

            if (eulerRotation.x > 360.f) eulerRotation.x -= 360.0f;
            else if (eulerRotation.x < -360.f) eulerRotation.x += 360.0f;

            if (eulerRotation.y > 360.f) eulerRotation.y -= 360.0f;
            else if (eulerRotation.y < -360.f) eulerRotation.y += 360.0f;

            if (eulerRotation.z > 360.f) eulerRotation.z -= 360.0f;
            else if (eulerRotation.z < -360.f) eulerRotation.z += 360.0f;

            orientation = glm::quat(glm::radians(eulerRotation));
            localTransformNeedsUpdate = true;
        }

        #pragma endregion
        
        
        #pragma region Local Transform

        inline const glm::mat4x4& GetLocalTransform()
        {
            if (localTransformNeedsUpdate)
            {
                localTransformMatrix = glm::translate(uniformMatrix, position)
                                     * glm::toMat4(orientation) //* glm::mat4_cast(orientation); //TO-DO: Check which one is better
                                     * glm::scale(uniformMatrix, scale);

                localTransformNeedsUpdate = false;
            }
            return localTransformMatrix;
        }

        #pragma endregion


        #pragma region World Transform
        
        inline const glm::mat4x4& GetWorldMatrix() const { return worldTransformMatrix; }
        
        inline void UpdateWorldMatrix(const glm::mat4x4& parentWorldTransformMatrix)
        {
            worldTransformMatrix = parentWorldTransformMatrix * GetLocalTransform();
        }

        inline void UpdateWorldMatrix()
        {
            worldTransformMatrix = GetLocalTransform();
        }

        #pragma endregion
        
        friend std::ostream& operator<<(std::ostream& os, const Transform& obj);

    protected:
        static const glm::mat4 uniformMatrix;

        glm::mat4x4 localTransformMatrix, worldTransformMatrix;

        glm::vec3 position,
                  scale,
                  eulerRotation;

        glm::quat orientation;

        bool localTransformNeedsUpdate;
    };
}