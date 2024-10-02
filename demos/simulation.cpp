#include <iostream>
#include "simulation.hpp"

using namespace dough;



World::World(dough::real _timeStep, dough::real _Gravity) {
    timeStep = _timeStep;
    dough::Vector3 Gravity = dough::Vector3(0,_Gravity,0);
    ParticlesGravity* gravityFG = new ParticlesGravity(&particles);
    for (int i = 0; i < 50; i++) {
        particles.push_back(Particle());
    }
    auto i = particles.begin();
    for (; i != particles.end(); i++) {
        i->setPosition(Vector3((rand()%10)-5, (rand()%10)+5, (rand()%10)-5));
        i->setMass((rand()%3)+1);
        i->setAcceleration(Vector3(0,-9.81,0));
        i->setVelocity(Vector3(rand()%2, rand()%2, rand()%2));
        //registry.add(i.base(), gravityFG);
    }
}
void World::updateForces() {
    registry.updateForces(timeStep);
}

void World::checkCollisions() {
    auto i = particles.begin();
    for (; i != particles.end(); i++) {
        auto j = particles.begin();
        for (; j != particles.end(); j++) {
            if (i==j) continue;
            Vector3 distance = j->getPosition() - i->getPosition();
            if ((real_abs(distance.magnitude())) < 0.5) {
                // std::cout << "collision detected" << std::endl;
                ParticleContact contactResolver = ParticleContact();
                contactResolver.particle[0] = i.base();
                contactResolver.particle[1] = j.base();
                contactResolver.restitution = 0.9;
                contactResolver.contactNormal = (i->getPosition() - j->getPosition());
                contactResolver.resolve(timeStep);
            }
        } 
        if (i->getPosition().y < 0) {
            ParticleContact groundResolver = ParticleContact();
            groundResolver.particle[0] = i.base();
            groundResolver.restitution = 0.9;
            groundResolver.contactNormal = Vector3(0,1,0);
            groundResolver.resolve(timeStep);
        }
    }
}

void World::step() {
    auto i = particles.begin();
    for (; i != particles.end(); i++) {
        i->integrate(timeStep);
    }
}