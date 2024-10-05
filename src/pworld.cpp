#include "dough/pworld.hpp"
#include <iostream>
#include <string>

using namespace dough;



World::World(dough::real _timeStep, dough::real _Gravity, unsigned maxContacts, unsigned iterations) 
: resolver(iterations), maxContacts(maxContacts) {
    
    contacts = new ParticleContact[maxContacts];

    timeStep = _timeStep;
    dough::Vector3 Gravity = dough::Vector3(0,_Gravity,0);
    for (int i = 0; i < 3; i++) {
        particles.push_back(Particle());
        particles[i].setMass(1);
        particles[i].setAcceleration(Vector3(0,-9.81,0));
        particles[i].setPosition(Vector3(rand()%5, rand()%5, rand()%5));
    }
    // particles[0].setMass(1000);
    // particles[1].setMass(1);
    // particles[0].setVelocity(Vector3(0,0,0));
    // particles[0].setPosition(Vector3(0,7,0));
    // particles[1].setPosition(Vector3(0,2,0));
    // particles[1].setAcceleration(Vector3(0,-9.81,0));
    // particles[2].setMass(2);
    // particles[2].setAcceleration(Vector3(0,-9.81,0));
    // particles[3].setMass(1);
   // particles[3].setAcceleration(Vector3(0,-9.81,0));
    //particles[1].setAcceleration(Vector3(0,-10,0));
    // auto i = particles.begin();
    // for (; i != particles.end(); i++) {
    //     i->setPosition(Vector3((rand()%10)-5, (rand()%10)+5, (rand()%10)-5));
    //     i->setMass(2); //(rand()%3)+1
    //     i->setAcceleration(Vector3(0,-9.81,0));
    //     i->setVelocity(Vector3(rand()%2, rand()%2, rand()%2));
    //     //registry.add(i.base(), gravityFG);
    // }
}

void World::checkCollisions() {
    // auto i = particles.begin();
    // for (; i != particles.end(); i++) {
    //     auto j = particles.begin();
    //     for (; j != particles.end(); j++) {
    //         if (i==j) continue;
    //         Vector3 distance = j->getPosition() - i->getPosition();
    //         if ((real_abs(distance.magnitude())) < 1) {
    //             // std::cout << "collision detected" << std::endl;
    //             ParticleContact contactResolver = ParticleContact();
    //             contactResolver.particle[0] = i.base();
    //             contactResolver.particle[1] = j.base();
    //             contactResolver.restitution = 0.95;
    //             contactResolver.contactNormal = (i->getPosition() - j->getPosition());
    //             contactResolver.resolve(timeStep);
    //         }
    //     } 
    //     if (i->getPosition().y < 0) {
    //         ParticleContact groundResolver = ParticleContact();
    //         groundResolver.particle[0] = i.base();
    //         groundResolver.restitution = 0.95;
    //         groundResolver.contactNormal = Vector3(0,1,0);
    //         groundResolver.resolve(timeStep);
    //     }
    // }
}
void World::updateForces() {
    registry.updateForces(timeStep);
}

void World::step() {
    auto i = particles.begin();
    for (; i != particles.end(); i++) {
        i->integrate(timeStep);
    }
    unsigned usedContacts = generateContacts();
    //std::cout << "used contacts" + std::to_string(usedContacts) << std::endl;
    if (usedContacts) {
        resolver.setIterations(usedContacts*2);
        resolver.resolveContacts(contacts, usedContacts, timeStep);
    }
}

unsigned World::generateContacts() {
    unsigned limit = maxContacts;
    ParticleContact* nextContact = contacts;

    for (auto g = contactGenerators.begin(); g != contactGenerators.end(); g++) {
        unsigned used = (*g)->addContact(nextContact, limit);
        limit -= used;
        nextContact += used;

        if (limit <= 0) {
            std::cout << "contact limit reached" << std::endl;
            break;
        }
    }
    return maxContacts - limit;
}