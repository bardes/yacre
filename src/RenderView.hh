#ifndef RENDERVIEW_HH_MQ0Z2HFU
#define RENDERVIEW_HH_MQ0Z2HFU

#include<glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include "Scene.hh"

namespace yacre
{
class RenderView
{
  public:
    RenderView(const Scene &s);
    virtual ~RenderView();

    sf::Sprite GetRender();
    void RenderPasses(unsigned nPasses = 1);

  private:
    const Scene &mScene;
    sf::Texture mRrenderTexture;
    glm::vec3 *mFloatPixBuff;
    unsigned char *mPixBuff;
    unsigned mTotalPasses;
};
} /* yacre */

#endif /* end of include guard: RENDERVIEW_HH_MQ0Z2HFU */
