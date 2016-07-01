#ifndef SUN_HH_GUMES9A3
#define SUN_HH_GUMES9A3

#include "../Lamp.hh"

#include <glm/glm.hpp>

namespace yacre
{
    class Sun : public Lamp
    {
    public:
        Sun(const glm::vec3 &intensity,
            float dist = std::numeric_limits<float>::infinity()):
            mIntensity(intensity), mDist(dist) {}
        virtual ~Sun() = default;

        virtual glm::vec3 Shine(const glm::vec3&) const
        {
            return mIntensity;
        }

        virtual Ray Shadow(const glm::vec3& point) const
        {
            return Ray(point, glm::vec3(0, 1, 0) * GetOrientation());
        }

        virtual float Distance(const glm::vec3&) const
        {
            return mDist;
        }

    private:
        glm::vec3 mIntensity;
        float mDist;
    };
} /* yacre */

#endif /* end of include guard: SUN_HH_GUMES9A3 */
