#ifndef PRIMITIVE_HH_YLXZN9G3
#define PRIMITIVE_HH_YLXZN9G3

#include <glm/glm.hpp>

#include "Object.hh"
#include "Material.hh"
#include "Texture.hh"
#include "Ray.hh"

namespace yacre
{
    struct Ray;
    class Primitive : public Object {
        public:
            Primitive(): mMaterial(nullptr), mTexture(nullptr) {}
            virtual ~Primitive() = default;

            virtual float
            CheckInstersection(const Ray &r) const = 0;

            virtual glm::vec2 ComputeUV(const glm::vec3 &point) const = 0;

            glm::vec3 GetNormal(const glm::vec3 &point) const
            {
                if(mTexture && mTexture->HasNormal())
                    return ComputeTangentSpace(point) *
                           mTexture->ComputeNormal(ComputeUV(point));
                else
                    return  ComputeNormal(point);
            }

            virtual glm::vec3 ComputeNormal(const glm::vec3 &point) const = 0;

            virtual glm::mat3
            ComputeTangentSpace(const glm::vec3& point) const = 0;

            glm::vec3
            GetColor(const glm::vec3 &point, const glm::vec3 &incidence) const
            {
                if(mTexture && mTexture->HasColor())
                    return mTexture->ComputeColor(ComputeUV(point));
                else if (mMaterial)
                    return mMaterial->ComputeColor(incidence, GetNormal(point));
                else
                    return glm::vec3(0);
            }

            float Diffuse(const Ray &in, const Ray &out) const
            {
                return !mMaterial ? 0.f :
                        mMaterial->Diffusion(in.GetDirection(),
                                             GetNormal(out.GetOrigin()));
            }

            float Reflect(const Ray &in, Ray &out) const
            {
                return !mMaterial ? 0 :
                        mMaterial->Reflection(in.GetDirection(),
                                              GetNormal(out.GetOrigin()),
                                              out.GetDirection());
            }

            float Refract(const Ray &in, Ray &out) const
            {
                return !mMaterial ? 0 :
                        mMaterial->Refraction(in.GetDirection(),
                                                GetNormal(out.GetOrigin()),
                                                out.GetDirection());
            }

            void SetMaterial(const Material *mat) {mMaterial = mat;}
            void SetTexture(const Texture *tex) {mTexture = tex;}

            const Material* GetMaterial() const {return mMaterial;}
            const Texture* GetTexture() const {return mTexture;}

    private:
        const Material *mMaterial;
        const Texture *mTexture;
    };
}

#endif /* end of include guard: PRIMITIVE_HH_YLXZN9G3 */
