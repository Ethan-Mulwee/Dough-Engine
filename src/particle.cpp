#include "dough/particle.hpp"
#include "assert.h"

using namespace dough;

void Particle::integrate(real time) {
    if (inverseMass <= 0) return;

    assert(time>0);

    Vector3 resultingAcc = acceleration;
    position += (velocity*time)+(resultingAcc*time*time);
    resultingAcc += (forceAccum*inverseMass);
    velocity += (resultingAcc*time);

    velocity *= real_pow(damping, time);

    clearAccumulator();
}

void Particle::clearAccumulator() {
    forceAccum.clear();
}

Vector3 Particle::getPosition() const {
    return position;
}

void Particle::getPosition(Vector3* position) const {
    *position = Particle::position;
}