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
            void add(Particle* particle, ParticleForceGenerator *fg);

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

    class ParticleSpring : public ParticleForceGenerator {
        protected:
        Particle *other;
        real springConstant;
        real restLength;
        public:
        ParticleSpring(Particle* other, real springConstant, real restLength);
        virtual void updateForce(Particle* particle, real time);
    };

    class ParticleAnchoredSpring : public ParticleForceGenerator {
        protected:
        Vector3* anchor;
        real springConstant;
        real restLength;
        public:
        ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength);
        virtual void updateForce(Particle* particle, real time);
    };

    class ParticleBungee : public ParticleForceGenerator {
        protected:
        Particle *other;
        real springConstant;
        real restLength;
        public:
        ParticleBungee(Particle* other, real springConstant, real restLength);
        virtual void updateForce(Particle* particle, real time);
    };
}