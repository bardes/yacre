#ifndef MATERIAL_HH_1CLXM3YR
#define MATERIAL_HH_1CLXM3YR

#include <random>

#include <glm/fwd.hpp>

namespace yacre
{
    class Material {
        public:
            virtual ~Material() = default;

            virtual glm::vec3 ComputeColor(const glm::vec3 &inc,
                                           const glm::vec3 &normal) const = 0;

            virtual bool Reflection(const glm::vec3 &in,
                                    const glm::vec3 &normal,
                                    glm::vec3 &out) const = 0;

            virtual bool Refraction(const glm::vec3 &in,
                                    const glm::vec3 &normal,
                                    glm::vec3 &out) const = 0;
    };
} /* yacre */

#endif /* end of include guard: MATERIAL_HH_1CLXM3YR */
