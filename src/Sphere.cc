#include "Sphere.hh"

#include <cmath>
#include <utility>

#include <glm/glm.hpp>

yacre::Sphere::Sphere(const glm::vec3& pos, float radius)
{
    mRadiusSq = radius * radius;
    SetPosition(pos);
}

// Assumes a = 1
static bool solveQuadratic(float b, float c, float &x0, float &x1)
{
    float delta = b * b - 4 * c;

    if (delta <= 0) {
        return false;
    } else {
        x0 = -(b + std::copysign(1.0, b) * std::sqrt(delta)) / 2;
        x1 = c / x0;
    }
    if (x0 > x1) std::swap(x0, x1);

    return true;
}

bool
yacre::Sphere::CheckInstersection(const yacre::Ray& r, glm::vec3& point) const
{
    glm::vec3 L = r.GetOrigin() - GetPosition();
    float b = 2.0f * glm::dot(r.GetDirection(), L);
    float c = glm::dot(L, L) - mRadiusSq;

    float x0, x1;
    if(!solveQuadratic(b, c, x0, x1)) return false;

    if(x0 > 0) {
        point = r.GetDirection() * x0;
        return true;
    } else if (x1 > 0) {
        point = r.GetDirection() * x1;
        return true;
    }

    return false;
}
