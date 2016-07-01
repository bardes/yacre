#ifndef INFINETEPLANE_HH_O2SIKJYE
#define INFINETEPLANE_HH_O2SIKJYE

#include "../Primitive.hh"

namespace yacre
{
    class InfinetePlane : public Primitive
    {
    public:
        InfinetePlane(float xScale = 1, float yScale = 0)
        {
            mInvTextureScale.x = xScale;
            mInvTextureScale.y = yScale > 0 ? yScale : xScale;
            mInvTextureScale = 1.f / mInvTextureScale;
        }

        virtual ~InfinetePlane() = default;

        virtual float CheckInstersection(const Ray& r) const
        {
            if(std::fabs(r.GetDirection().y) < 0.00001f || r.GetOrigin().y < 0)
                return -1.f;
            else
                return -r.GetOrigin().y / r.GetDirection().y;
        }

        virtual glm::vec3 ComputeNormal(const glm::vec3&) const
        {
            return glm::vec3(0, 1.f, 0);
        }

        virtual glm::mat3 ComputeTangentSpace(const glm::vec3&) const
        {
            return glm::mat3(1, 0, 0,
                             0, 0, -1,
                             0, 1, 0);
        }

        virtual glm::vec2 ComputeUV(const glm::vec3& point) const
        {
            return glm::vec2(point.x, point.z) * mInvTextureScale;
        }

    private:
        glm::vec2 mInvTextureScale;
    };

} /* yacre */

#endif /* end of include guard: INFINETEPLANE_HH_O2SIKJYE */
