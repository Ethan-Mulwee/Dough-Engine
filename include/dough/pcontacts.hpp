#ifndef DOUGH_PCONTACTS_H
#define DOUGH_PCONTACTS_H

#include "particle.hpp"

namespace dough {
    class PraticleContactResolver;

    class ParticleContact {
        friend class ParticleContactResolver;

        public:
        Particle* particle[2];
        real restitution;
        real penetration;
        Vector3 contactNormal;
        Vector3 particleMovement[2];

        public: //should be protected is public temporarily
        void resolve(real time);
        real calculateSeparatingVelocity() const;
        
        private:
        void resolveVelocity(real time);
        void resolveInterpenetration(real time);
    };

    class ParticleContactResolver {
        protected:
        unsigned iterations;
        unsigned iterationsUsed;

        public:
        ParticleContactResolver(unsigned iterations);
        void setIterations(unsigned iterations);
        void resolveContacts(ParticleContact* contactArray, unsigned numContacts, real time);
    };

    class ParticleContactGenerator {
        public:
        virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;
    };

    class ParticleParticleCollison : ParticleContactGenerator {
        public:
        real radius;
        virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;
    };

    class ParticleGroundCollision : ParticleContactGenerator {
        public:
        real radius;
        virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;
    };
}

#endif