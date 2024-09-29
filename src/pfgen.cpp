#include "dough/pfgen.hpp"

using namespace dough;
void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg) {
    ParticleForceRegistry::ParticleForceRegistration registration;
    registration.particle = particle;
    registration.fg = fg;
    registrations.push_back(registration);
}
void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg) {

}
void ParticleForceRegistry::clear() {
    
}
void ParticleForceRegistry::updateForces(real time) {
    Registry::iterator i = registrations.begin();
    for(; i != registrations.end(); i++) {
        i->fg->updateForce(i->particle, time);
    }
}
void ParticleGravity::updateForce(Particle* particle, real time) {
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

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 *anchor, real springConstant, real restLength) 
: anchor(anchor), springConstant(springConstant), restLength(restLength) {}

void ParticleAnchoredSpring::updateForce(Particle *particle, real time) {
    Vector3 force;
    particle->getPosition(&force);
    force -= *anchor;

    real magnitude = force.magnitude();
    magnitude = (restLength-magnitude) * springConstant;

    force.normalize();
    force *= magnitude;
    particle->addForce(force);
}

ParticleBungee::ParticleBungee(Particle *other, real springConstant, real restLength) 
: other(other), springConstant(springConstant), restLength(restLength) {}

void ParticleBungee::updateForce(Particle *particle, real time){
    Vector3 force;
    particle->getPosition(&force);
    force -= other->getPosition();

    real magnitude = force.magnitude();
    if (magnitude <= restLength) return;
    magnitude = springConstant * (restLength - magnitude);

    force.normalize();
    force *= magnitude;
    particle->addForce(force);
}

ParticlesGravity::ParticlesGravity(std::vector<Particle> *particles) 
: particles(particles) {};

void ParticlesGravity::updateForce(Particle *particle, real time){
    auto i = particles->begin();
    for (; i != particles->end(); i++) {
        Vector3 force = (i->getPosition() - particle->getPosition());
        real distance = force.magnitude();
        if (distance == 0) continue;
        distance *= distance;
        force.normalize();
        force *= (particle->getMass()*i->getMass())/distance;
        particle->addForce(force);
    }
}
