#ifndef TEXTURE_HH_FGAPJU95
#define TEXTURE_HH_FGAPJU95

#include <string>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

namespace yacre
{
    class Texture
    {
    public:
        Texture (const std::string &color, const std::string &normal = "");
        ~Texture () = default;

        glm::vec3 ComputeColor(glm::vec2 uv) const;
        glm::vec3 ComputeNormal(glm::vec2 uv) const;

        void SetScale(float s) {mScale = s;}
        float GetScale() const {return mScale;}

        bool HasColor() const {return mHasColorMap;}
        bool HasNormal() const {return mHasNormalMap;}

    private:
        bool mHasColorMap;
        bool mHasNormalMap;
        sf::Image mColorMap;
        sf::Image mNormalMap;
        float mScale;
    };
} /* yacre */

#endif /* end of include guard: TEXTURE_HH_FGAPJU95 */
