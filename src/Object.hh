#ifndef OBJECT_HH_NOMGP0DN
#define OBJECT_HH_NOMGP0DN

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace yacre
{
    /**
     * Basic scene object.
     *
     * Every object in a scene must be a child of this class.
     */
    class Object {
        public:
            virtual ~Object() = default;

            void SetPosition(const glm::vec3 &p) {mPosition = p;}
            void SetOrientation(const glm::quat &o) {mOrientation = o;}
            void SetOrientation(const glm::vec3 &axis, float angle);


            glm::vec3 GetPosition() const {return mPosition;}
            glm::quat GetOrientation() const {return mOrientation;}

        private:
            //Transformations
            glm::vec3 mPosition;
            glm::quat mOrientation;

    };
}

#endif /* end of include guard: OBJECT_HH_NOMGP0DN */
