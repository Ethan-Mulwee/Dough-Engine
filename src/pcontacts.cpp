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
        particle[0]->setVelocity(particle[1]->getVelocity()+impulsePerIMass*particle[1]->getInverseMass());
    }
}

void ParticleContact::resolveInterpenetration(real time) {
    if (penetration <= 0) return;
    real totalInverseMass = particle[0]->getInverseMass();
    if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

    if (totalInverseMass <= 0) return;

    Vector3 movePerIMass = contactNormal * (penetration/totalInverseMass);

    //Add a particle movement array later to accumlate multiple movements
    particle[0]->setPosition(movePerIMass*particle[0]->getInverseMass());
    if (particle[1]) {
        particle[1]->setPosition(movePerIMass * particle[1]->getInverseMass());
    }
}