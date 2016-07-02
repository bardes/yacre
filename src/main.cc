#include <iostream>

#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include "Scene.hh"
#include "RenderView.hh"
#include "Texture.hh"

#include "Primitives/Sphere.hh"
#include "Primitives/InfinetePlane.hh"

#include "Materials/Diffuse.hh"
#include "Materials/Mirror.hh"
#include "Materials/Transparent.hh"

#include "Lamps/PointLamp.hh"
#include "Lamps/Sun.hh"

int main(int argc, char *argv[])
{
    if(argc < 3) {
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " <width> <height> [output_file]" << std::endl;
        return 1;
    }

    // Takes the resolution from the command line
    auto res = glm::uvec2(std::strtoul(argv[1], nullptr, 10),
                          std::strtoul(argv[2], nullptr, 10));

    // Creates an empty scene with a camera
    float fov = glm::radians<float>(60.0f);
    yacre::Scene s(new yacre::Camera(res, fov));
    s.GetCamera()->SetPosition(glm::vec3(0, 1, 2));
    s.GetCamera()->SetOrientation(glm::vec3(1, 0, 0), glm::radians<float>(5));
    s.SetBackgroundTexture("img/col/garage.png");

    // Creates some materials
    s.AddMaterial("Branco", new yacre::Diffuse(glm::vec3(.9)));
    s.AddMaterial("Transp", new yacre::Transparent(1.5));
    s.AddMaterial("Mirr", new yacre::Mirror(glm::vec3(.97), 0));

    // Creates a texture
    s.AddTexture("Wood", new yacre::Texture("img/col/wood.jpg", "img/nor/wood.jpg"));
    s.AddTexture("Earth", new yacre::Texture("img/col/earth.jpg", "img/nor/earth.jpg"));

    // Create a sphere
    yacre::Primitive *p;
    p = new yacre::Sphere(glm::vec3(-1.5, .3, 0), .3);
    p->SetMaterial(s.GetMaterial("Transp"));
    s.AddPrimitive("Bolota-1", p);
    p = new yacre::Sphere(glm::vec3(-.5, .3, 0), .3);
    p->SetMaterial(s.GetMaterial("Branco"));
    s.AddPrimitive("Bolota-2", p);
    p = new yacre::Sphere(glm::vec3(.5, .3, -.2), .3);
    p->SetMaterial(s.GetMaterial("Mirr"));
    s.AddPrimitive("Bolota-3", p);
    p = new yacre::Sphere(glm::vec3(1.5, .3, 0), .3);
    p->SetMaterial(s.GetMaterial("Branco"));
    p->SetTexture(s.GetTexture("Earth"));
    s.AddPrimitive("Bolota-4", p);

    p = new yacre::InfinetePlane(3);
    p->SetMaterial(s.GetMaterial("Branco"));
    p->SetTexture(s.GetTexture("Wood"));
    s.AddPrimitive("Plano", p);

    // And a few lamps
    yacre::Lamp *l = new yacre::PointLamp(glm::vec3(0,2,5));
    l->SetPosition(glm::vec3(3, 2, 3));
    s.AddLamp("Lampadinha", l);
    l = new yacre::PointLamp(glm::vec3(25, 25, 15));
    l->SetPosition(glm::vec3(-3, 2, 3));
    s.AddLamp("Lampadinha-2", l);
    l = new yacre::PointLamp(glm::vec3(10, 10, 15));
    l->SetPosition(glm::vec3(0, 2, 2));
    s.AddLamp("Lampadinha-3", l);
    l = new yacre::Sun(glm::vec3(.3, .3, .3));
    l->SetOrientation(glm::vec3(.3, 0, 1), glm::radians<float>(45));
    s.AddLamp("El-Sol", l);

    // Creates a render view to manage the scene rendering
    yacre::RenderView rv(s);
    auto RenderSprite = rv.GetRender();

    // Creates a window to show the rendering progress
    sf::RenderWindow w(sf::VideoMode(res.x, res.y), "YACRE - Render View",
                       sf::Style::None);
    w.clear(sf::Color::Black);
    w.display();

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

        // Main loop here: render, display, repeat.
        rv.RenderPasses(1);
        w.draw(RenderSprite);
        w.display();
        n++;
    }

    std::cout << "Passes: " << n << std::endl;

    if(argc > 3)
        RenderSprite.getTexture()->copyToImage().saveToFile(argv[3]);

    return 0;
}
