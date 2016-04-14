#ifndef POINTLIGHT_HH_FHCG3V0R
#define POINTLIGHT_HH_FHCG3V0R

#include <utility>

#include <glm/glm.hpp>

#include "../Lamp.hh"

namespace yacre
{
    class PointLamp : public Lamp
    {
        public:
            PointLamp(const glm::vec3 &intensity): mIntensity(intensity) {}
            PointLamp(glm::vec3 &&intensity):mIntensity(std::move(intensity)){}
            virtual ~PointLamp() = default;
    
            virtual glm::vec3 Shine(const glm::vec3& point) const;

        private:
            glm::vec3 mIntensity;
    };
} /* yacre */

#endif /* end of include guard: POINTLIGHT_HH_FHCG3V0R */
