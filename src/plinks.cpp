#include "dough/plinks.hpp"
#include <iostream>
#include <string>

using namespace dough;

real ParticleLink::currentLength() const {
    Vector3 relativePos = particle[0]->getPosition()-particle[1]->getPosition();
    //std::cout << std::to_string((relativePos.magnitude())) << std::endl;
    return relativePos.magnitude();
}

unsigned ParticleCable::addContact(ParticleContact* contact, unsigned limit) const {
    real length = currentLength();
    if (length < maxLength) {
        return 0;
    }

    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
    normal.normalize();
    contact->contactNormal = normal;

    contact->penetration = length-maxLength;
    contact->restitution = restitution;
    return 1;
}

unsigned ParticleRod::addContact(ParticleContact* contact, unsigned limit) const {
    real currentLen = currentLength();

    if (currentLen == length) {
        return 0;
    }

    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
    normal.normalize();

    contact->contactNormal = normal;
    contact->penetration = currentLen - length;
    contact->restitution = 0;

    unsigned used = 1;
    contact += used;

    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    contact->contactNormal = normal * -1;
    contact->penetration = length - currentLen;
    contact->restitution = 0;

    return 2;
}