#include "Plane.hh"
#include "Disk.hh"

#include <cmath>
#include <utility>

#include <glm/glm.hpp>

yacre::Plane::Plane(const glm::vec3& pos, const Vec3f &n, const Vec3f &p) : Primitive()
{
    normalPlane = n;
    p0 = p;
    SetPosition(pos);
}

float yacre::Plane::CheckInstersection(const yacre::Ray& r)
{
  float denom = dotProduct(normal, r.GetDirection());
  float t = 0.0f;
  if (denom > 1e-6) {
    Vec3f pl = p0 - r.GetOrigin();
    t = dotProduct(pl, normal) / denom;
  }

  return t;
}

float yacre::Disk::CheckInstersection(const yacre::Ray& r, const float &radius)
{
  float t = intersectPlane(r);
  if (t!=0) {
    Vec3f p = r.GetOrigin() + r.GetDirection() * t;
    Vec3f v = p - p0;
    float d2 = dot(v, v);
    if (sqrtf(d2) <= radius)
      return t;
  }
  return 0.0f;
} 
