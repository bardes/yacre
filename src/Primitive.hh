#ifndef PRIMITIVE_HH_YLXZN9G3
#define PRIMITIVE_HH_YLXZN9G3

#include <glm/glm.hpp>

#include "Object.hh"
#include "Material.hh"
#include "Ray.hh"

namespace yacre
{
    struct Ray;
    class Primitive : public Object {
        public:
            Primitive(const Material *mat = nullptr):
            Object(), mMaterial(mat) {}
            virtual ~Primitive() = default;

            virtual float
            CheckInstersection(const Ray &r) const = 0;

            virtual glm::vec3 GetNormal(const glm::vec3 &point) const = 0;

            glm::vec3
            GetColor(const glm::vec3 &point, const glm::vec3 &incidence) const
            {
                return mMaterial ?
                       mMaterial->ComputeColor(incidence, GetNormal(point)):
                       glm::vec3(0);
            }

            bool Reflect(const Ray &in, Ray &out) const
            {
                return !mMaterial ? false :
                        mMaterial->Reflection(in.GetDirection(),
                                              GetNormal(out.GetOrigin()),
                                              out.GetDirection());
            }

            bool Refract(const Ray &in, Ray &out) const
            {
                return !mMaterial ? false :
                        mMaterial->Refraction(in.GetDirection(),
                                              GetNormal(out.GetOrigin()),
                                              out.GetDirection());
            }

            void SetMaterial(const Material *mat) {mMaterial = mat;}

            const Material* GetMaterial() const {return mMaterial;}
    private:
        const Material *mMaterial;
    };
}

#endif /* end of include guard: PRIMITIVE_HH_YLXZN9G3 */
