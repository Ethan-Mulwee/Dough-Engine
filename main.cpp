#include <iostream>
#include "dough/particle.hpp"

using namespace dough;
int main() {
    Particle particle = Particle(Vector3(1,1,1), Vector3(2,5,0), 0.999, 3);
    std::cout << particle.getPosition().x << std::endl;
    particle.integrate(1);
    std::cout << particle.getPosition().x << std::endl;
}