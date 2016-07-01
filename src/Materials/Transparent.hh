#ifndef TRANSPARENT_HH_LZQN0XBW
#define TRANSPARENT_HH_LZQN0XBW

#include "../Material.hh"

#include <glm/glm.hpp>

namespace yacre
{
    class Transparent : public Material
    {
    public:
        Transparent(float ior): mIor(ior) {}
        virtual ~Transparent() = default;

        virtual glm::vec3 ComputeColor(const glm::vec3&,
                                       const glm::vec3&) const
        {
            return glm::vec3(1);
        }

        virtual float Diffusion(const glm::vec3&, const glm::vec3&) const
        {
            return 0;
        }

        virtual float Reflection(const glm::vec3&,
                                 const glm::vec3&,
                                 glm::vec3&) const
        {
            return 0;
        }

        virtual float Refraction(const glm::vec3& in,
                                 const glm::vec3& normal,
                                 glm::vec3& out) const
        {
            if(glm::dot(in, normal) > 0) { // Inside to outside
                out = glm::refract(in, -normal, mIor);
                if(out == glm::vec3(0)) // Total reflection.
                    out = glm::reflect(in, -normal);
            } else { // Outside to inside
                out = glm::refract(in, normal, 1/mIor);
            }
            return 1.f;
        }

    private:
        float mIor;
    };
} /* yacre */

#endif /* end of include guard: TRANSPARENT_HH_LZQN0XBW */
