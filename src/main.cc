#include <iostream>

#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include "Scene.hh"
#include "RenderView.hh"

#include "Primitives/Sphere.hh"
#include "Materials/Diffuse.hh"
#include "Lamps/PointLamp.hh"

int main(int argc, char *argv[])
{
    auto res = glm::vec2(sf::VideoMode::getDesktopMode().width,
                         sf::VideoMode::getDesktopMode().height);
    res /= (float) atof(argv[1]);

    float fov = glm::radians<float>(60.0f);
    yacre::Scene s(new yacre::Camera(res, fov));
    s.GetCamera()->SetPosition(glm::vec3(0, 0, 3));

    s.SetBackgroundColor(glm::vec3(0, 0, 0));

    s.AddMaterial("Branco", new yacre::Diffuse(glm::vec3(.8)));
    s.AddMaterial("Vermelho", new yacre::Diffuse(glm::vec3(.8,0,0)));

    auto p = new yacre::Sphere(glm::vec3(0), 1);
    p->SetMaterial(s.GetMaterial("Branco"));
    s.AddPrimitive("Bolota", p);
    p = new yacre::Sphere(glm::vec3(-.7, 0, 1), .25);
    p->SetMaterial(s.GetMaterial("Vermelho"));
    s.AddPrimitive("Bolota-2", p);
    p = new yacre::Sphere(glm::vec3(0, -1001, 0), 1000);
    p->SetMaterial(s.GetMaterial("Branco"));
    s.AddPrimitive("Bolota-3", p);

    auto l = new yacre::PointLamp(glm::vec3(0,0,5));
    l->SetPosition(glm::vec3(3, 2, 3));
    s.AddLamp("Lampadinha", l);
    l = new yacre::PointLamp(glm::vec3(25, 25, 15));
    l->SetPosition(glm::vec3(-3, 2, 3));
    s.AddLamp("Lampadinha-2", l);
    l = new yacre::PointLamp(glm::vec3(10, 10, 15));
    l->SetPosition(glm::vec3(0, 2, 2));
    s.AddLamp("Lampadinha-3", l);

    yacre::RenderView rv(s);
    auto RenderSprite = rv.GetRender();

    sf::RenderWindow w(sf::VideoMode(res.x, res.y), "YACRE - Render View");

    unsigned n = 0;
    while(w.isOpen()) {
        // Process events
        sf::Event event;
        while (w.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                w.close();
            else if(event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape)
                w.close();
        }

        rv.RenderPasses(1);
        w.draw(RenderSprite);
        w.display();
        n++;
    }

    std::cout << "Passes: " << n << std::endl;

    if(argc > 2)
        RenderSprite.getTexture()->copyToImage().saveToFile(argv[2]);

    return 0;
}
