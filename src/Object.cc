#include "Object.hh"

#include <glm/glm.hpp>

static glm::quat AxisAngleToQuat(const glm::vec3 &axis, float angle)
{
    float half_angle = angle / 2;
    float half_sin = glm::sin(half_angle);

    glm::quat q;
    q.x = axis.x * half_sin;
    q.y = axis.y * half_sin;
    q.z = axis.z * half_sin;
    q.w = glm::cos(half_angle);
    return q;
}

void yacre::Object::SetOrientation(const glm::vec3& axis, float angle)
{
    mOrientation = AxisAngleToQuat(axis, angle);
}
