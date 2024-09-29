#include "dough/pfgen.hpp"

using namespace dough;
void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
{
    ParticleForceRegistry::ParticleForceRegistration registration;
    registration.particle = particle;
    registration.fg = fg;
    registrations.push_back(registration);
}
void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg)
{

}
void ParticleForceRegistry::clear()
{
    
}
void ParticleForceRegistry::updateForces(real time)
{
    Registry::iterator i = registrations.begin();
    for(; i != registrations.end(); i++) {
        i->fg->updateForce(i->particle, time);
    }
}
void ParticleGravity::updateForce(Particle* particle, real time)
{
    Vector3 force;
    force = particle->getVelocity();
    if (!particle->hasFiniteMass()) return;
    particle->addForce(gravity*particle->getMass());
}
ParticleSpring::ParticleSpring(Particle* other, real springConstant, real restLength) {
    ParticleSpring::other = other; 
    ParticleSpring::springConstant = springConstant;
    ParticleSpring::restLength = restLength;
}
void ParticleSpring::updateForce(Particle* particle, real time) {
    Vector3 force;
    particle->getPosition(&force);
    force -= other->getPosition();

    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude - restLength);
    magnitude *= springConstant;
    
    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}