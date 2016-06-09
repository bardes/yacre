#include "Disk.hh"

#include <cmath>
#include <utility>

#include <glm/glm.hpp>

yacre::Disk::Disk(const glm::vec3& pos, const Vec3f &n, const Vec3f &p0) : Primitive()
{
    normal = n;
    p = p0;
    SetPosition(pos);
}

