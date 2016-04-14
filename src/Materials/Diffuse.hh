#ifndef DIFFUSE_HH_2STD36KV
#define DIFFUSE_HH_2STD36KV

#include "../Material.hh"

#include <utility>

#include <glm/glm.hpp>

namespace yacre
{
    class Diffuse : public Material {
    public:
        Diffuse(glm::vec3 &&color) : mColor(std::move(color)) {}
        Diffuse(const glm::vec3 &color) : mColor(color) {}
        virtual ~Diffuse() = default;

        virtual glm::vec3 ComputeColor(const glm::vec3& inc,
                                       const glm::vec3& normal) const
        {
            return mColor;
        }

        virtual bool Refraction(const glm::vec3& in,
                                const glm::vec3& normal,
                                glm::vec3& out) const
        {
            return false;
        }

        virtual bool Reflection(const glm::vec3& in,
                                const glm::vec3& normal,
                                glm::vec3& out) const;
    private:
        glm::vec3 mColor;
    };
} /* yacre */

#endif /* end of include guard: DIFFUSE_HH_2STD36KV */
