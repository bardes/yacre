#ifndef DIFFUSE_HH_2STD36KV
#define DIFFUSE_HH_2STD36KV

#include "../Material.hh"

#include <utility>

#include <glm/glm.hpp>

namespace yacre
{
    class Diffuse : public Material {
    public:
        Diffuse(const glm::vec3 &color) : Material(), mColor(color) {}
        virtual ~Diffuse() = default;

        virtual glm::vec3 ComputeColor(const glm::vec3&,
                                       const glm::vec3&) const
        {
            return mColor;
        }

        virtual float Diffusion(const glm::vec3&,
                                const glm::vec3&) const
        {
            return 1.0f;
        }

        virtual float Refraction(const glm::vec3&,
                                 const glm::vec3&,
                                 glm::vec3&) const
        {
            return 0.f;
        }

        virtual float Reflection(const glm::vec3& in,
                                 const glm::vec3& normal,
                                 glm::vec3& out) const;
    private:
        glm::vec3 mColor;
    };
} /* yacre */

#endif /* end of include guard: DIFFUSE_HH_2STD36KV */
