#ifndef PRIMITIVE_HH_YLXZN9G3
#define PRIMITIVE_HH_YLXZN9G3

#include <glm/glm.hpp>

#include "Object.hh"
#include "Ray.hh"
#include "Material.hh"

namespace yacre
{
    class Primitive : public Object {
        public:
            virtual bool CheckInstersection(const Ray &r,
                                            glm::vec3 &point) const = 0;

            virtual glm::vec3 GetNormal(const glm::vec3 &point) const = 0;

            glm::vec3 GetColor(const glm::vec3 &point,
                               const glm::vec3 &incidence) const
            {
                return mMaterial ?
                       mMaterial->ComputeColor(incidence, GetNormal(point)):
                       glm::vec3(0);
            }

            void SetMaterial(const Material *mat) {mMaterial = mat;}
    private:
        const Material *mMaterial;
    };
}

#endif /* end of include guard: PRIMITIVE_HH_YLXZN9G3 */
