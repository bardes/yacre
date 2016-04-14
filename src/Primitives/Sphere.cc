#include "Sphere.hh"

#include <cmath>
#include <utility>

#include <glm/glm.hpp>

yacre::Sphere::Sphere(const glm::vec3& pos, float radius) : Primitive()
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

float yacre::Sphere::CheckInstersection(const yacre::Ray& r) const
{
    glm::vec3 L = r.GetOrigin() - GetPosition();
    float b = 2.0f * glm::dot(r.GetDirection(), L);
    float c = glm::dot(L, L) - mRadiusSq * GetSacale();

    if(b > 1) b*=2;
    if(c > 1) b*=2;

    float x0, x1;
    if(!solveQuadratic(b, c, x0, x1)) return 0.f;

    return x0 > 0 ? x0 : x1;
}
