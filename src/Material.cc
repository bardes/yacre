#include "Material.hh"

std::mt19937 yacre::Material::sRandGen = std::mt19937();

void yacre::Material::SetSeed(unsigned int seed)
{
    if(seed == 0) {
        std::random_device rd;
        seed = (rd());
    }
   sRandGen.seed(seed);
}
