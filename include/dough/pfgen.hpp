#include "particle.hpp"
#include <vector>

namespace dough {
    class ParticleForceGenerator {
        public:
        virtual void updateForce(Particle* particle, real time) = 0;
    };

    class ParticleForceRegistry {
        protected:
            struct ParticleForceRegistration {
                Particle* particle;
                ParticleForceGenerator* fg;
            };

            typedef std::vector<ParticleForceRegistration> Registry;
            Registry registrations;

        public:
            void add(Particle* particle, ParticleForceGenerator* fg);

            void remove(Particle* particle, ParticleForceGenerator* fg);

            void clear();

            void updateForces(real time);
    };

    class ParticleGravity : public ParticleForceGenerator {
        Vector3 gravity;
        public:
        ParticleGravity(const Vector3& gravity)
        : gravity(gravity) {};
        virtual void updateForce(Particle* particle, real time);
    };
}