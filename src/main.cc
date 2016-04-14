#include <iostream>
#include <glm/glm.hpp>

#include "Scene.hh"

#include "Primitives/Sphere.hh"
#include "Materials/Diffuse.hh"
#include "Lamps/PointLamp.hh"

static void WritePgm(const unsigned char *pixels, unsigned w, unsigned h)
{
    std::cout << "P6\n" << w << " " << h << "\n255\n";
    std::cout.write((const char*) pixels, w * h * 3);
}

int main(int argc, char *argv[])
{
    glm::uvec2 res(512, 270);
    yacre::Scene s(new yacre::Camera(res, glm::radians<float>(70.0f)));
    s.GetCamera()->SetPosition(glm::vec3(0, 2, 3));
    s.GetCamera()->SetOrientation(glm::vec3(1, 0, 0), glm::radians<float>(56.31f));

    s.AddMaterial("Branco", new yacre::Diffuse(glm::vec3(1)));

    auto p = new yacre::Sphere(glm::vec3(0), 2);
    p->SetMaterial(s.GetMaterial("Branco"));
    s.AddPrimitive("Bolota", p);

    auto l = new yacre::PointLamp(glm::vec3(1));
    l->SetPosition(glm::vec3(3, 4, 3));
    s.AddLamp("Lampadinha", l);

    auto buff = s.Render();
    WritePgm(buff, res.x, res.y);
    delete[] buff;

    return 0;
}
