#include "dough/pfgen.hpp"

using namespace dough;
void ParticleForceRegistry::add(Particle *particle, ParticleForceGenerator *fg)
{

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