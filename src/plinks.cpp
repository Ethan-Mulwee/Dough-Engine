#include "dough/plinks.hpp"

using namespace dough;

real ParticleLink::currentLength() const {
    Vector3 relativePos = particle[0]->getPosition()-particle[1]->getPosition();
    return relativePos.magnitude();
}

unsigned ParticleCable::addContact(ParticleContact* contact, unsigned limit) const {
    
}