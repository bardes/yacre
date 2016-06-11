#include "Diffuse.hh"

#include <glm/gtc/random.hpp>

bool yacre::Diffuse::Reflection(const glm::vec3& in, const glm::vec3& normal,
                                glm::vec3& out) const
{
    out = glm::sphericalRand(1.0f);
    if(glm::dot(out, normal) < 0) out *= -1;
    return true;
}
