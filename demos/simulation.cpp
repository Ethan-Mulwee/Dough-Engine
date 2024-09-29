#include "simulation.hpp"

using namespace dough;



World::World(dough::real _timeStep, dough::real _Gravity) {
    timeStep = _timeStep;
    dough::Vector3 Gravity = dough::Vector3(0,_Gravity,0);
    a.setPosition(Vector3(0,0,0));
    a.setAcceleration(Vector3(0,-9.81,0));
    a.setVelocity(Vector3(1,2,-3));
    a.setMass(5);
    b.setMass(5);
    a.setDamping(0.999);
    b.setDamping(0.999);

    // Vector3* anchor = new Vector3(0,0,0);
    // ParticleAnchoredSpring* AnchoredSpringFG = new ParticleAnchoredSpring(anchor, 50, 4);
    // registry.add(&a, AnchoredSpringFG);
    ParticleBungee* bungeeFG = new ParticleBungee(&b, 30, 4);
    registry.add(&a, bungeeFG);

}

void World::step() {
    registry.updateForces(timeStep);
    a.integrate(timeStep);
    b.integrate(timeStep);
}