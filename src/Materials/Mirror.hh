#ifndef MIRROR_HH_YT780D1R
#define MIRROR_HH_YT780D1R

#include "../Material.hh"

#include <utility>

#include <glm/glm.hpp>

namespace yacre
{
    class Mirror : public Material {
    public:
        Mirror(const glm::vec3 &color, float roughness):
        mColor(color), mReflectiveness(1 - roughness) {}

        virtual ~Mirror() = default;

        virtual glm::vec3 ComputeColor(const glm::vec3&,
                                       const glm::vec3&) const
        {
            return mColor;
        }

        virtual float Diffusion(const glm::vec3&,
                                const glm::vec3&) const
        {
            return 1 - mReflectiveness;
        }

        virtual float Refraction(const glm::vec3&,
                                 const glm::vec3&,
                                 glm::vec3&) const
        {
            return 0.f;
        }

        virtual float Reflection(const glm::vec3& in,
                                 const glm::vec3& normal,
                                 glm::vec3& out) const
        {
            out = glm::reflect(in, normal);
            return mReflectiveness;
        }
    private:
        glm::vec3 mColor;
        float mReflectiveness;
    };
} /* yacre */

#endif /* end of include guard: MIRROR_HH_YT780D1R */
