#ifndef SCENE_HH_72UDZNZ5
#define SCENE_HH_72UDZNZ5

#include <memory>
#include <unordered_map>
#include <string>

#include <glm/glm.hpp>

#include "Object.hh"
#include "Material.hh"
#include "Texture.hh"
#include "Primitive.hh"
#include "Camera.hh"
#include "Lamp.hh"
#include "Ray.hh"

namespace yacre
{
    class Scene {
        public:
            Scene(Camera *cam):mCamera(cam), mBackgroundColor(0), mBias(1e-3){}
            virtual ~Scene();

            void AddPrimitive(const std::string &name, Primitive *p);
            void AddLamp(const std::string &name, Lamp* l);
            void AddMaterial(const std::string &name, Material *m);
            void AddTexture(const std::string &name, Texture *m);
            void SetCamera(Camera *cam) {delete mCamera; mCamera = cam;}
            void SetBackgroundColor(glm::vec3 col) {mBackgroundColor = col;}
            void SetBias(float b) {mBias = b;}
            bool SetBackgroundTexture(const std::string& imgPath)
            {
                return mBackgroundTexture.SetColorMap(imgPath);
            }

            Primitive* GetPrimitive(const std::string &name);
            Lamp* GetLamp(const std::string &name);
            Material* GetMaterial(const std::string &name);
            Texture* GetTexture(const std::string &name);
            Camera* GetCamera() {return mCamera;}
            float GetBias() {return mBias;}

            const Primitive* GetPrimitive(const std::string &name) const;
            const Lamp* GetLamp(const std::string &name) const;
            const Material* GetMaterial(const std::string &name) const;
            const Texture* GetTexture(const std::string &name) const;
            const Camera* GetCamera() const {return mCamera;}
            glm::vec3 GetBackgroundColor() const {return mBackgroundColor;}


            bool RemovePrimitive(const std::string &name);
            bool RemoveLamp(const std::string &name);
            bool RemoveMaterial(const std::string &name);
            bool RemoveTexture(const std::string &name);

            /**
             * Renders one pass into the buffer.
             *
             * The buffer must be big enough to contain all the pixels. Note
             * that the pixels are *ADDED* to the buffer, not overlaid!
             */
            void Render(glm::vec3* buffer) const;

        private:
            /**
             * Casts a ray to find the color twards that direction.
             *
             * This method will result in recursive calls until bouncesLeft
             * is 0, in which case the color returned shall be the background
             * color.
             *
             * \param r Ray to be cast.
             * \param bouncesLeft How many bounces (reflection or transmission)
             * there are left.
             * \return Color value generated by the ray
             */
            glm::vec3 Cast(const Ray &r, unsigned bouncesLeft) const;

            /**
             * Traces a ray and finds the nearest intersection with an object.
             *
             * \param[in] r Ray to be traced.
             * \param[out] distance If an intersection is found this will
             * be set to the distance between the ray's origin and the
             * intersection point.
             *
             * \return Pointer to the intersected object or nullptr if no
             * intersection.
             */
            const yacre::Primitive* Trace(const Ray &r, float &distance) const;

            glm::vec2 ComputeBackgroundUV(const glm::vec3 d) const
            {
                float u = .5f + std::atan2(d.x, d.z) / glm::two_pi<float>();
                float v = .5f + std::asin(d.y) / glm::pi<float>();
                return glm::vec2(-u, -v);
            }

            // Basic components of the scene
            std::unordered_map<std::string, Primitive*> mPrimitives;
            std::unordered_map<std::string, Lamp*> mLamps;
            std::unordered_map<std::string, Material*> mMaterials;
            std::unordered_map<std::string, Texture*> mTextures;
            Camera *mCamera;

            glm::vec3 mBackgroundColor;
            float mBias;

            Texture mBackgroundTexture;
    };
}
#endif /* end of include guard: SCENE_HH_72UDZNZ5 */
