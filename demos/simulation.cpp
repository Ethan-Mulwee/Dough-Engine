#include "simulation.hpp"

using namespace dough;



World::World(dough::real _timeStep, dough::real _Gravity) {
    timeStep = _timeStep;
    dough::Vector3 Gravity = dough::Vector3(0,_Gravity,0);
    particles.push_back(Particle());
    particles.push_back(Particle());
    particles.push_back(Particle());
    auto i = particles.begin();
    for (; i != particles.end(); i++) {
        i->setMass(5);
    }
    particles[0].setPosition(Vector3(-4,-1,0));
    particles[1].setPosition(Vector3(-1,-2,-2));
    particles[2].setPosition(Vector3(1,2,-1));

    ParticlesGravity* gravityFG = new ParticlesGravity(&particles);
    registry.add(&(particles[0]), gravityFG);
    registry.add(&(particles[1]), gravityFG);
    registry.add(&(particles[2]), gravityFG);
}

void World::step() {
    registry.updateForces(timeStep);
    auto i = particles.begin();
    for (; i != particles.end(); i++) {
        i->integrate(timeStep);
    }
}