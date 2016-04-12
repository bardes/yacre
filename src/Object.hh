#ifndef OBJECT_HH_NOMGP0DN
#define OBJECT_HH_NOMGP0DN

#include <glm/fwd.hpp>

namespace yacre
{
    /**
     * Basic scene object.
     *
     * Every object in a scene must be a child of this class.
     */
    class Object {
        public:
            void SetPosition(const glm::vec3 &p) {mPosition = p;}
            void SetSacale(float s) {mScale = s;}
            void SetOrientation(const glm::vec3 &axis, float angle)
            {
                mAxis = axis;
                mAngle = angle;
            }

            glm::vec3 GetPosition() const {return mPosition;}
            float GetSacale() const {return mScale;}
            glm::vec3 GetUpVector() const {return mAxis;}
            float GetAngle() const {return mAngle;}
            void GetOrientation(glm::vec3 &axis, float angle) const
            {
                axis = mAxis;
                angle = mAngle;
            }

        private:
            //Transformations
            glm::vec3 mPosition;
            float mScale;
            glm::vec3 mAxis; //Should be normalized
            float mAngle;

    };
}

#endif /* end of include guard: OBJECT_HH_NOMGP0DN */
