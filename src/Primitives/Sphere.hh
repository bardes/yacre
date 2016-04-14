#ifndef SPHERE_HH_OENJTWAL
#define SPHERE_HH_OENJTWAL

#include <glm/fwd.hpp>

#include "../Primitive.hh"

namespace yacre
{
    class Sphere : public Primitive {
        public:
            Sphere(const glm::vec3 &pos, float radius);

            virtual float CheckInstersection(const Ray& r) const;

            virtual glm::vec3 GetNormal(const glm::vec3& point) const
            {
                return point - GetPosition();
            }

        private:
            float mRadiusSq;
    };
}
#endif /* end of include guard: SPHERE_HH_OENJTWAL */
