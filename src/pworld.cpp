#include "dough/pworld.hpp"
#include <iostream>
#include <string>

using namespace dough;



World::World(dough::real _timeStep, dough::real _Gravity, unsigned maxContacts, unsigned iterations, unsigned particleCount) 
: resolver(iterations), maxContacts(maxContacts) {
    
    contacts = new ParticleContact[maxContacts];

    timeStep = _timeStep;
    dough::Vector3 Gravity = dough::Vector3(0,_Gravity,0);
    for (int i = 0; i < particleCount; i++) {
        particles.push_back(Particle());
        particles[i].setMass(1);
        //particles[i].setAcceleration(Vector3(0,-9.81,0));
        particles[i].setPosition(Vector3(rand()%5+((rand()%10)*0.1), rand()%10+((rand()%10)*0.1), rand()%5+((rand()%10)*0.1)));
        particles[i].setDamping(0.999);
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

ParticleForceRegistry& World::getForceRegistry() {
    return registry;
}