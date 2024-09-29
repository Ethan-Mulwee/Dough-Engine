#include "dough/pfgen.hpp"

using namespace dough;
void ParticleForceRegistry::add(Particle *particle, ParticleForceGenerator *fg)
{
    ParticleForceRegistration registration;
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