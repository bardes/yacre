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

            virtual glm::vec3 ComputeNormal(const glm::vec3& point) const
            {
                return glm::normalize(point - GetPosition());
            }

            virtual glm::mat3 ComputeTangentSpace(const glm::vec3& point) const
            {
                glm::vec3 T, B, N;
                B = GetPosition() + glm::vec3(0, mRadiusSq, 0) / mRadiusSq;
                B = B - point;
                N = ComputeNormal(point);
                T = glm::cross(B, N);
                B = glm::cross(N, T);
                return glm::mat3(T, B, N);
            }

            virtual glm::vec2 ComputeUV(const glm::vec3& point) const
            {
                glm::vec3 d = glm::normalize(GetPosition() - point);
                float u = .5f + std::atan2(-d.x, -d.z) / glm::two_pi<float>();
                float v = .5f - std::asin(-d.y) / glm::pi<float>();
                return glm::vec2(u, v);
            }

        private:
            float mRadius;
            float mRadiusSq;
    };
}
#endif /* end of include guard: SPHERE_HH_OENJTWAL */
