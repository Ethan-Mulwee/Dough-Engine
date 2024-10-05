#include "dough/pcontacts.hpp"
#include "dough/pfgen.hpp"
#include "dough/plinks.hpp"
#include <vector>

namespace dough {
    class World {
        public:
        typedef std::vector<dough::Particle> Particles;
        typedef std::vector<dough::ParticleContactGenerator*> ContactGenerators;

        protected:
        ParticleForceRegistry registry;
        ParticleContactResolver resolver;
        ParticleContact *contacts;
        real timeStep;
        unsigned maxContacts;
        public:
        ContactGenerators contactGenerators;
        Particles particles;
        World(real _timeStep, real _Gravity, unsigned maxContacts, unsigned iterations, unsigned particleCount);
        void updateForces();
        void step();
        unsigned generateContacts();
        Particles& getParticles();
        ContactGenerators& getContactGenerators();
        ParticleForceRegistry& getForceRegistry();
    };
}
