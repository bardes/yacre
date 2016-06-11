#include "Scene.hh"

#include <iostream>
#include <omp.h>

#include <glm/glm.hpp>

#include <glm/gtc/random.hpp>

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

    float int_dist; // Intersection distance
    if(auto hit = Trace(r, int_dist)) {
        // Calculates the intersection point
        glm::vec3 point = r.GetOrigin() + r.GetDirection() * int_dist;

        glm::vec3 obj_color = hit->GetColor(point, r.GetDirection());
        glm::vec3 color(0);
        for(auto it : mLamps) {
            const Lamp* lamp = it.second;
            Ray shadow(point, glm::normalize(lamp->GetPosition() - point));
            shadow.GetOrigin() += shadow.GetDirection() * mBias;
            float distance;
            if(!Trace(shadow, distance)) {
                color += obj_color * lamp->Shine(point) *
                        glm::dot(shadow.GetDirection(), hit->GetNormal(point));
            }
        }

        // Reflection and refraction rays
        Ray rflec(point); Ray rfrac(point);

        // Tries to reflec and refract the ray
        if(hit->Reflect(r, rflec)) {
            rflec.GetOrigin() += rflec.GetDirection() * mBias;
            color += obj_color * Cast(rflec, bouncesLeft - 1);
        }
        if(hit->Reflect(r, rfrac)) {
            rfrac.GetOrigin() += rfrac.GetDirection() * mBias;
            color += obj_color * Cast(rfrac, bouncesLeft - 1);
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

void yacre::Scene::Render(glm::vec3 *buffer) const
{
    // Takes the camera resolution and calculates the aspect ratio
    glm::uvec2 res = mCamera->GetResolution();
    float aspect = res.x / (float) res.y;

    // Calculates the fov aspect correction
    float fov = glm::tan(mCamera->GetFov() / 2);

    // Samples each pixel once
    #pragma omp parallel for schedule(static, 64)
    for(unsigned line = 0; line < res.y; ++line) {
        for(unsigned col = 0; col < res.x; ++col) {
            // Used to sample randomly within each pixel's area
            float rx = glm::linearRand<float>(0.f, 1.f);
            float ry = glm::linearRand<float>(0.f, 1.f);
           
            // Calculates the ray direction in camera coordinates
            glm::vec3 direction;
            direction.x = (2.f * ((col + rx) / res.x) - 1.f) * fov * aspect;
            direction.y = (1.f - 2.f * (line + ry) / res.y) * fov;
            direction.z = -1.f;

            // Converts to world coordinates
            direction = direction * mCamera->GetOrientation();

            // Creates the ray with a normalized direction
            Ray r(mCamera->GetPosition(), glm::normalize(direction));

            buffer[line * res.x + col] += Cast(r, 3);
        }
    }
}
