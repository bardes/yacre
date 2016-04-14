#include "Scene.hh"

#include <glm/glm.hpp>

void yacre::Scene::AddLamp(const std::string& name, yacre::Lamp* l)
{
    auto target = mLamps.find(name);
    if(target != mLamps.end()) {
        delete target->second;
        target->second = l;
    } else {
        mLamps[name] = l;
    }
}

void yacre::Scene::AddPrimitive(const std::string& name, yacre::Primitive* p)
{
    auto target = mPrimitives.find(name);
    if(target != mPrimitives.end()) {
        delete target->second;
        target->second = p;
    } else {
        mPrimitives[name] = p;
    }
}

void yacre::Scene::AddMaterial(const std::string& name, yacre::Material* m)
{
    auto target = mMaterials.find(name);
    if(target != mMaterials.end()) {
        delete target->second;
        target->second = m;
    } else {
        mMaterials[name] = m;
    }
}

const yacre::Lamp* yacre::Scene::GetLamp(const std::string& name) const
{
    auto it = mLamps.find(name);
    return it == mLamps.end() ? NULL : it->second;
}

yacre::Lamp* yacre::Scene::GetLamp(const std::__cxx11::string& name)
{
    auto it = mLamps.find(name);
    return it == mLamps.end() ? NULL : it->second;
}

const yacre::Material*
yacre::Scene::GetMaterial(const std::string& name) const
{
    auto it = mMaterials.find(name);
    return it == mMaterials.end() ? NULL : it->second;
}

yacre::Material* yacre::Scene::GetMaterial(const std::string& name)
{
    auto it = mMaterials.find(name);
    return it == mMaterials.end() ? NULL : it->second;
}

const yacre::Primitive*
yacre::Scene::GetPrimitive(const std::string& name) const
{
    auto it = mPrimitives.find(name);
    return it == mPrimitives.end() ? NULL : it->second;
}

yacre::Primitive* yacre::Scene::GetPrimitive(const std::string& name)
{
    auto it = mPrimitives.find(name);
    return it == mPrimitives.end() ? NULL : it->second;
}

bool yacre::Scene::RemoveLamp(const std::string& name)
{
    auto it = mLamps.find(name);
    if(it != mLamps.end()) {
        delete it->second;
        mLamps.erase(it);
        return true;
    }
    return false;
}

bool yacre::Scene::RemovePrimitive(const std::string& name)
{
    auto it = mPrimitives.find(name);
    if(it != mPrimitives.end()) {
        delete it->second;
        mPrimitives.erase(it);
        return true;
    }
    return false;
}

bool yacre::Scene::RemoveMaterial(const std::string& name)
{
    auto it = mMaterials.find(name);
    if(it != mMaterials.end()) {
        delete it->second;
        mMaterials.erase(it);
        return true;
    }
    return false;
}

yacre::Scene::~Scene()
{
    delete mCamera;
    for(auto pair : mPrimitives) {
        delete pair.second;
        pair.second = nullptr;
    }
    for(auto pair : mLamps) {
        delete pair.second;
        pair.second = nullptr;
    }
    for(auto pair : mMaterials) {
        delete pair.second;
        pair.second = nullptr;
    }
}

glm::vec3
yacre::Scene::Cast(const yacre::Ray& r, unsigned int bouncesLeft) const
{
    // Depth limit reached
    if(!bouncesLeft) return mBackgroundColor;

    glm::vec3 color(0);
    float int_dist; // Intersection distance
    if(auto hit = Trace(r, int_dist)) {
        // Calculates the intersection point
        glm::vec3 point = r.GetOrigin() + r.GetDirection() * int_dist;

        // Reflection and refraction rays
        Ray rflec(point); Ray rfrac(point);

        // Tries to reflec and refract the ray
        if(hit->Reflect(r, rflec)) {
            rflec.GetOrigin() += rflec.GetDirection() * mBias;
            color += Cast(rflec, bouncesLeft - 1);
        }
        if(hit->Reflect(r, rfrac)) {
            rfrac.GetOrigin() += rfrac.GetDirection() * mBias;
            color += Cast(rfrac, bouncesLeft - 1);
        }

        return color;
    }

    // No intersection
    return mBackgroundColor;
}

const yacre::Primitive*
yacre::Scene::Trace(const yacre::Ray& r, float& distance) const
{
    distance = std::numeric_limits<float>::infinity();
    Primitive *hit = nullptr;

    for(auto it : mPrimitives) {
        float int_dist = it.second->CheckInstersection(r);
        if(int_dist > 0 && int_dist < distance) {
            distance = int_dist;
            hit = it.second;
        }
    }
    return hit;
}

unsigned char* yacre::Scene::Render() const
{
    // Creates a ray with the origin at the camera and a null direction
    Ray r(mCamera->GetPosition());

    // Takes the camera resolution and calculates the aspect ratio
    glm::uvec2 res = mCamera->GetResolution();
    float aspect = res.x / (float) res.y;

    // Alloctes the pixel buffer
    unsigned buff_len = res.x * res.y * 3;
    auto fpix_buff = new float[buff_len]();
    auto upix_buff = new unsigned char[buff_len];

    // Calculates the fov aspect correction
    float fov = glm::tan(mCamera->GetFov() / 2);

    // Creates the direction vector
    glm::vec3 direction;

    // Samples each pixel once for every lamp
    for(auto lamp : mLamps) {
        for(unsigned line = 0; line < res.y; ++line) {
            // Calculates ray's y camera coordinate only once per line
            float py = (1.f - 2.f * (line + .5f)) * fov;
            unsigned line_offset = line * res.x * 3;
            for(unsigned col = 0; col < res.x; ++col) {
                // Calculates the x camera coord
                direction.x = (2.f * (col + .5f) - 1.f) * fov * aspect;
                direction.y = py;
                direction.z = -1.f;

                // Converts to world coordinates
                direction = direction * mCamera->GetOrientation();

                // Normalizes and sets the ray direction
                r.SetDirection(glm::normalize(direction));

                glm::vec3 color = Cast(r, 1) * 255.f;
                fpix_buff[line_offset + col + 0] += color.r;
                fpix_buff[line_offset + col + 1] += color.g;
                fpix_buff[line_offset + col + 2] += color.b;
            }
        }
    }

    // Converts the image to 8 bit RGB
    for(unsigned i = 0; i < buff_len; ++i) {
        upix_buff[i] = glm::clamp((unsigned char)(fpix_buff[i] / mLamps.size()),
                                  (unsigned char) 0, (unsigned char) 255);
    }
    delete[] fpix_buff;
    return upix_buff;
}
