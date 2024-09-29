#include "dough/pfgen.hpp"
#include <vector>


class World {
    protected:
    dough::ParticleForceRegistry registry;
    dough::real timeStep;
    public:
    std::vector<dough::Particle> particles;
    World(dough::real _timeStep, dough::real _Gravity);

    void step();
};