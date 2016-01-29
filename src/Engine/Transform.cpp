#include "Transform.h"

namespace Symphony
{
    const glm::mat4 Transform::uniformMatrix = glm::mat4(1.0f);

    Transform::Transform()
    {
        scale = glm::vec3(1.f);
        SetRotation(glm::vec3());
        localTransformNeedsUpdate = true;
    }

    Transform::~Transform()
    {
    }

    std::ostream& operator <<(std::ostream& os, const Transform& obj)
    {
        os << "Position: (" << obj.position.x << ", " << obj.position.y << ", " << obj.position.z << ")" << std::endl;
        os << "Scale: (" << obj.scale.x << ", " << obj.scale.y << ", " << obj.scale.z << ")" << std::endl;
        os << "Rotation: (" << obj.eulerRotation.x << ", " << obj.eulerRotation.y << ", " << obj.eulerRotation.z << ")" << std::endl;
        return os;
    }
}