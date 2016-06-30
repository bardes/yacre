#include "Texture.hh"

yacre::Texture::Texture(const std::string& color, const std::string& normal):
mHasColorMap(false), mHasNormalMap(false), mScale(1.f)
{
    if(!color.empty() && mColorMap.loadFromFile(color))
       mHasColorMap = true;

    if(!normal.empty() && mNormalMap.loadFromFile(normal))
       mHasNormalMap = true;
}

glm::vec3 yacre::Texture::ComputeColor(glm::vec2 uv) const
{
    if(!mHasColorMap) return glm::vec3(0);

    uv = glm::mod(uv / mScale, 1.f);
    if(uv.x < 0) uv.x = 1.f - uv.x;
    if(uv.y < 0) uv.y = 1.f - uv.y;

    unsigned x = (unsigned) std::round(uv.x * mColorMap.getSize().x);
    unsigned y = (unsigned) std::round(uv.y * mColorMap.getSize().y);

    sf::Color col = mColorMap.getPixel(x, y);
    return glm::vec3(col.r, col.g, col.b) / 255.f;
}

glm::vec3 yacre::Texture::ComputeNormal(glm::vec2 uv) const
{
    if(!mHasNormalMap) return glm::vec3(0);

    uv = glm::mod(uv / mScale, 1.f);
    if(uv.x < 0) uv.x = 1.f - uv.x;
    if(uv.y < 0) uv.y = 1.f - uv.y;

    unsigned x = (unsigned) std::round(uv.x * mNormalMap.getSize().x);
    unsigned y = (unsigned) std::round(uv.y * mNormalMap.getSize().y);

    sf::Color col = mNormalMap.getPixel(x, y);
    glm::vec3 normal;
    return (glm::vec3(col.r, col.g, col.b) / 127.5f) - 1.f;
}
