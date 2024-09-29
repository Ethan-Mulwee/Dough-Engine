#include "dough/pfgen.hpp"



class World {
    protected:
    dough::ParticleForceRegistry registry;
    dough::real timeStep;
    public:
    dough::Particle a, b;
    World(dough::real _timeStep, dough::real _Gravity) {
        timeStep = _timeStep;
        dough::Vector3 Gravity = dough::Vector3(0,_Gravity,0);
        a.setAcceleration(Gravity);
        b.setAcceleration(Gravity);
        a.setMass(5);
        b.setMass(5);
        a.setDamping(0.999);
        b.setDamping(0.999);
    };

    void step();
};