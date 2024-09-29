#include "simulation.hpp"

using namespace dough;

World::World(dough::real _timeStep, dough::real _Gravity) {
    timeStep = _timeStep;
    dough::Vector3 Gravity = dough::Vector3(0,_Gravity,0);
    a.setAcceleration(Gravity);
    b.setAcceleration(Gravity);
    a.setMass(5);
    b.setMass(5);
    a.setDamping(0.999);
    b.setDamping(0.999);

    ParticleSpring psA(&b, 1.0f, 2.0f);
    registry.add(&a, &psA);
}

void World::step() {
    registry.updateForces(timeStep);
    a.integrate(timeStep);
    b.integrate(timeStep);
}