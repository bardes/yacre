#ifndef PLANE_HH_OENJTWAL
#define PLANE_HH_OENJTWAL

#include <glm/fwd.hpp>

#include "../Primitive.hh"

namespace yacre
{
    class Plane : public Primitive {
        public:
            Plane(const glm::vec3 &pos, float radius);

            virtual float CheckInstersection(const yacre::Ray& r, const Vec3f &n, const Vec3f &p0)
	    
	    virtual glm::vec3 GetNormal(const glm::vec3& point) const
            {
                return glm::normalize(point - GetPosition());
            }
            
        private:
             Vec3f &normal;
	     Vec3f &p0;
    };
}
#endif /* end of include guard: PLANE_HH_OENJTWAL */
