#include "simulation.hpp"

using namespace dough;



World::World(dough::real _timeStep, dough::real _Gravity) {
    timeStep = _timeStep;
    dough::Vector3 Gravity = dough::Vector3(0,_Gravity,0);
    ParticlesGravity* gravityFG = new ParticlesGravity(&particles);
    for (int i = 0; i < 100; i++) {
        particles.push_back(Particle());
    }
    auto i = particles.begin();
    for (; i != particles.end(); i++) {
        i->setPosition(Vector3((rand()%10)-5, (rand()%10)-5, (rand()%10)-5));
        i->setMass((rand()%3)+1);
        registry.add(i.base(), gravityFG);
    }
}
void World::updateForces() {
    registry.updateForces(timeStep);
}

void World::step() {
    auto i = particles.begin();
    for (; i != particles.end(); i++) {
        i->integrate(timeStep);
    }
}