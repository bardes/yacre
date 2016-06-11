#include "PointLamp.hh"

#include <glm/gtc/constants.hpp>

glm::vec3 yacre::PointLamp::Shine(const glm::vec3& point) const
{
    float r = glm::length<float>(GetPosition() - point);
    float s = (4 * glm::pi<float>() * r );
    return mIntensity * (1/s);
}
