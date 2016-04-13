#ifndef LAMP_HH_XHDGXTFQ
#define LAMP_HH_XHDGXTFQ

#include <glm/glm.hpp>

#include "Object.hh"

namespace yacre
{
    class Lamp : public Object {
        public:
            virtual ~Lamp() = default;

            /**
             * Calculates the light incidence at a given point.
             */
            virtual glm::vec3 Shine(const glm::vec3 &point) const = 0;
    };
}

#endif /* end of include guard: LAMP_HH_XHDGXTFQ */
