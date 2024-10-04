#include "dough/pcontacts.hpp"

using namespace dough;

void ParticleContact::resolve(real time) {
    resolveVelocity(time);
    resolveInterpenetration(time);
}

real ParticleContact::calculateSeparatingVelocity() const {
    Vector3 relativeVelocity = particle[0]->getVelocity();
    // if particle two exists,
    // otherwise the other object probably doesn't move so we assume it's velocity is 0
    if (particle[1]) relativeVelocity -= particle[1]->getVelocity();
    //dot product
    return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(real duration) {
    real separatingVelocity = calculateSeparatingVelocity();
    if (separatingVelocity > 0) return;
    real newSepVelocity = -separatingVelocity * restitution;
    //IF restitution = 0 then delta velocity = -sepVelo which will cancel the existing separating velocity
    real deltaVelocity = newSepVelocity-separatingVelocity;
    real totalInverseMass = particle[0]->getInverseMass();
    if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

    if (totalInverseMass <= 0) return;

    real impluse = deltaVelocity / totalInverseMass;

    Vector3 impulsePerIMass = contactNormal * impluse;

    particle[0]->setVelocity(particle[0]->getVelocity()+impulsePerIMass*particle[0]->getInverseMass());

    if (particle[1]) {
        particle[1]->setVelocity(particle[1]->getVelocity()+impulsePerIMass*-particle[1]->getInverseMass());
    }
}

void ParticleContact::resolveInterpenetration(real time) {
    if (penetration <= 0) return;
    real totalInverseMass = particle[0]->getInverseMass();
    if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

    if (totalInverseMass <= 0) return;

    Vector3 movePerIMass = contactNormal * (penetration/totalInverseMass);

    //Add a particle movement array later to accumlate multiple movements
    particleMovement[0] = movePerIMass * particle[0]->getInverseMass();
    if (particle[1]) {
        particleMovement[1] = movePerIMass * -particle[1]->getInverseMass();
    } else {
        particleMovement[1].clear();
    }
    // Apply the penetration resolution
    particle[0]->setPosition(particle[0]->getPosition() + particleMovement[0]);
    if (particle[1]) {
        particle[1]->setPosition(particle[1]->getPosition() + particleMovement[1]);
    }
}

ParticleContactResolver::ParticleContactResolver(unsigned iterations) {
    iterations = iterations;
}

void ParticleContactResolver::setIterations(unsigned iterations) {
    ParticleContactResolver::iterations = iterations;
}

void ParticleContactResolver::resolveContacts(ParticleContact *contactArray, unsigned numContacts, real time) {
    //std::cout << "resolveContacts called" << std::endl;
    unsigned i;
    iterationsUsed = 0;
    while(iterationsUsed < iterations) {
        real max = REAL_MAX;
        unsigned maxIndex = numContacts;
        for (i = 0; i < numContacts; i++) {
            real sepVel = contactArray[i].calculateSeparatingVelocity();
            //keep in mind sepVel is negative when two objects are coming together
            if (sepVel < max && (sepVel < 0 || contactArray[i].penetration > 0)) {
                max = sepVel;
                maxIndex = i;
            }
        }
        if (maxIndex == numContacts) break;
        //std::cout << "Attempting to resolve" << std::endl;
        contactArray[maxIndex].resolve(time);

        // Update the interpenetrations for all particles
        Vector3 *move = contactArray[maxIndex].particleMovement;
        for (i = 0; i < numContacts; i++)
        {
            if (contactArray[i].particle[0] == contactArray[maxIndex].particle[0])
            {
                contactArray[i].penetration -= move[0] * contactArray[i].contactNormal;
            }
            else if (contactArray[i].particle[0] == contactArray[maxIndex].particle[1])
            {
                contactArray[i].penetration -= move[1] * contactArray[i].contactNormal;
            }
            if (contactArray[i].particle[1])
            {
                if (contactArray[i].particle[1] == contactArray[maxIndex].particle[0])
                {
                    contactArray[i].penetration += move[0] * contactArray[i].contactNormal;
                }
                else if (contactArray[i].particle[1] == contactArray[maxIndex].particle[1])
                {
                    contactArray[i].penetration += move[1] * contactArray[i].contactNormal;
                }
            }
        }

        iterationsUsed++;
    }
}

unsigned ParticleGroundCollision::addContact(ParticleContact* contact, unsigned limit) const {
    if (particle->getPosition().y > 0) return 0;
    contact->particle[0] = particle;

    Vector3 normal = Vector3(0,1,0);
    contact->contactNormal = normal;
    contact->penetration = -particle->getPosition().y;
    contact->restitution = 0.9;
    return 1;
}

unsigned ParticleParticleCollison::addContact(ParticleContact* contact, unsigned limit) const {
    
}