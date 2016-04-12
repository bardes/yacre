#include <iostream>
#include <glm/glm.hpp>
#include "Sphere.hh"

int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;
    yacre::Sphere Banana(glm::vec3(0), 2);
    return 0;
}
