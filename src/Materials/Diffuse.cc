#include "Diffuse.hh"
#include<glm/gtc/constants.hpp>

bool yacre::Diffuse::Reflection(const glm::vec3& in, const glm::vec3& normal,
                                glm::vec3& out) const
{
    float u = yacre::Material::GetRandomNumber();
    float r = glm::sqrt(u);
    float t = glm::two_pi<float>() * yacre::Material::GetRandomNumber();

    out.x = r * glm::cos(t);
    out.y = r * glm::sin(t);
    out.z = glm::sqrt(1.0f - u);
    return true;
}
