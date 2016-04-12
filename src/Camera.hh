#ifndef CAMERA_HH_2ZXHHKEM
#define CAMERA_HH_2ZXHHKEM

#include <glm/fwd.hpp>

#include "Object.cc"

namespace yacre
{
    class Camera : Object
    {
    public:
        Camera(unsigned w, unsigned h, float fov = glm::half_pi()):
        mFov(fov), mResolution(w, h) {}

        virtual ~Camera();

        void SetFov(float fov) {mFov = fov;}
        void SetResolution(glm::uvec2 res) {mResolution = res;}
        void SetResolution(unsigned w, unsigned h)
        {
            mResolution.x = w;
            mResolution.y = h;
        }

        float GetFov() const {return mFov;}
        glm::uvec2 GetResolution() const {return mResolution;}

    private:
        float mFov;
        glm::uvec2 mResolution;
    };
} /* yacre */

#endif /* end of include guard: CAMERA_HH_2ZXHHKEM */
