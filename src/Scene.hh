#ifndef SCENE_HH_72UDZNZ5
#define SCENE_HH_72UDZNZ5

#include <memory>
#include <unordered_map>

#include <glm/fwd.hpp>

#include "Object.hh"
#include "Primitive.hh"
#include "Camera.hh"
#include "Lamp.hh"

namespace yacre
{
    class Scene {
        public:
            Scene(const Camera &cam): mCamera(cam){}
            virtual ~Scene();

            void AddPrimitive(const std::string &name, const Primitive *p);
            void AddLamp(const std::string &name, const Lamp *l);
            void AddMaterial(const std::string &name, const Material *m);

            bool RemovePrimitive(const std::string &name);
            bool RemoveLamp(const std::string &name);
            bool RemoveMaterial(const std::string &name);

            void SetBackgroundColor(glm::vec3 col) {mBackgroundColor = col;}
            void SetCamera(const Camera &cam) {mCamera = cam;}

            glm::vec3 GetBackgroundColor() const {return mBackgroundColor;}
            const Camera& GetCamera() const {return mCamera;}
            Camera& GetCamera() {return mCamera;}

        private:
            // Basic components of the scene
            std::unordered_map<std::string, Primitive*> mPrimitives;
            std::unordered_map<std::string, Lamp*> mLamps;
            std::unordered_map<std::string, Material*> mMaterials;
            Camera mCamera;

            glm::vec3 mBackgroundColor;
    };
}
#endif /* end of include guard: SCENE_HH_72UDZNZ5 */
