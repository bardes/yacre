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

unsigned char* yacre::Scene::Render() const
{
    return nullptr;
}
