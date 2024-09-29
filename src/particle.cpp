#include "dough/particle.hpp"
#include "assert.h"

using namespace dough;

void Particle::integrate(real time)
{
    if (inverseMass <= 0) return;

    assert(time>0);

    position += (velocity*time);
    Vector3 resultingAcc = acceleration;
    resultingAcc += (forceAccum*inverseMass);
    velocity += (resultingAcc*time);

    velocity *= real_pow(damping, time);

    clearAccumulator();
}

void Particle::clearAccumulator()
{
    forceAccum.clear();
}