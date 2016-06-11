#include "RenderView.hh"

yacre::RenderView::RenderView(const Scene &s): mScene(s), mTotalPasses(0)
{
    mRrenderTexture.create(s.GetCamera()->GetResolution().x,
                           s.GetCamera()->GetResolution().y);
    mRrenderTexture.setSmooth(false);

    auto res = s.GetCamera()->GetResolution();
    mFloatPixBuff = new glm::vec3[res.x * res.y]();
    mPixBuff = new unsigned char[res.x * res.y * 4];
}

yacre::RenderView::~RenderView()
{
    delete[] mFloatPixBuff;
    delete[] mPixBuff;
}

sf::Sprite yacre::RenderView::GetRender()
{
    return sf::Sprite(mRrenderTexture);
}

void yacre::RenderView::RenderPasses(unsigned nPasses)
{
    for(unsigned i = 0; i < nPasses; ++i)
        mScene.Render(mFloatPixBuff);
    mTotalPasses += nPasses;

    // Converts the rendered passes to an 8 bit RGBA texture
    auto res = mScene.GetCamera()->GetResolution();
    for(unsigned i = 0; i < res.x * res.y * 4; i += 4) {
        // Takes the average of all samples 'till now
        glm::vec3 pix = mFloatPixBuff[i/4] / (float) mTotalPasses;

        // Gamma correction
        pix = glm::pow(pix, glm::vec3(1/2.2f));

        // Clamps the pixel's chanels between [0, 255]
        pix = glm::clamp(pix * 255.f, 0.f, 255.f);

        // Writes the data into the 24bit (RGBA) buffer
        mPixBuff[i + 0] = (unsigned char) pix.r;
        mPixBuff[i + 1] = (unsigned char) pix.g;
        mPixBuff[i + 2] = (unsigned char) pix.b;
        mPixBuff[i + 3] = (unsigned char) 0xFF;
    }
    mRrenderTexture.update(mPixBuff);
}