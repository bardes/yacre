#ifndef LAMP_HH_XHDGXTFQ
#define LAMP_HH_XHDGXTFQ

#include <glm/glm.hpp>

#include "Object.hh"
#include "Ray.hh"

namespace yacre
{
    class Lamp : public Object {
        public:
            virtual ~Lamp() = default;

            /**
             * Calculates the light incidence at a given point.
             */
            virtual glm::vec3 Shine(const glm::vec3 &point) const = 0;

            /**
             * Calculates a shadow ray for the given point.
             */
            virtual Ray Shadow(const glm::vec3 &point) const = 0;

            virtual float Distance(const glm::vec3 &point) const
            {
                return glm::distance(point, GetPosition());
            }
    };
}

#endif /* end of include guard: LAMP_HH_XHDGXTFQ */
