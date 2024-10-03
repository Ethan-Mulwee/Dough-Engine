#include "dough/pcontacts.hpp"
#include "dough/pfgen.hpp"
#include "dough/plinks.hpp"
#include <vector>


class World {
    public:
    typedef std::vector<dough::Particle> Particles;
    typedef std::vector<dough::ParticleContactGenerator*> ContactGenerators;

    protected:
    dough::ParticleForceRegistry registry;
    dough::ParticleContactResolver resolver;
    dough::ParticleContact *contacts;
    dough::real timeStep;
    unsigned maxContacts;
    public:
    ContactGenerators contactGenerators;
    Particles particles;
    World(dough::real _timeStep, dough::real _Gravity, unsigned maxContacts, unsigned iterations);
    void updateForces();
    void checkCollisions();
    void step();
    unsigned generateContacts();
    Particles& getParticles();
    ContactGenerators& getContactGenerators();
};