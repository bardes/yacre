#include <iostream>
#include <glm/glm.hpp>

#include "Scene.hh"
#include "Sphere.hh"
#include "Materials/Diffuse.hh"

int main(int argc, char *argv[])
{
    yacre::Scene s(new yacre::Camera(1024, 540));
    s.AddPrimitive("Bolota", new yacre::Sphere(glm::vec3(0), 2));
    s.AddMaterial("Yay", new yacre::Diffuse(glm::vec3(1, 0, 0)));

    return 0;
}
