#include "dough/pfgen.hpp"



class World {
    protected:
    dough::ParticleForceRegistry registry;
    dough::real timeStep;
    public:
    dough::Particle a, b;
    World(dough::real _timeStep, dough::real _Gravity);

    void step();
};