#ifndef MATERIAL_HH_1CLXM3YR
#define MATERIAL_HH_1CLXM3YR

#include <glm/fwd.hpp>

#include "Ray.hh"

namespace yacre
{
    class Material
    {
        public:
            virtual glm::vec3 ComputeColor(const glm::vec3 &inc,
                                           const glm::vec3 &normal) const = 0;

            virtual bool Reflection(Ray &r) const = 0;
            virtual bool Refraction(Ray &r) const = 0;
        private:
    };
} /* yacre */

#endif /* end of include guard: MATERIAL_HH_1CLXM3YR */
