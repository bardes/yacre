#ifndef RAY_HH_P9QUOIE0
#define RAY_HH_P9QUOIE0

#include <glm/glm.hpp>

namespace yacre
{
    class Ray
    {
        public:
            Ray(const glm::vec3 &orign = glm::vec3(0),
                const glm::vec3 &direction = glm::vec3(0)):
                mOrign(orign), mDirection(direction) {}

            glm::vec3& GetOrigin() {return mOrign;}
            glm::vec3& GetDirection() {return mDirection;}

            const glm::vec3& GetOrigin() const {return mOrign;}
            const glm::vec3& GetDirection() const {return mDirection;}

            void SetOrigin(const glm::vec3 &o) { mOrign = o;}
            void SetDirection(const glm::vec3 &d) {mDirection = d;}

        private:
            glm::vec3 mOrign;
            glm::vec3 mDirection;
    };
}

#endif /* end of include guard: RAY_HH_P9QUOIE0 */
