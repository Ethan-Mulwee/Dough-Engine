#include "simulation.hpp"

using namespace dough;

void World::step() {
    a.integrate(timeStep);
    b.integrate(timeStep);
}