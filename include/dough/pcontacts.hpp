#ifndef DOUGH_PCONTACTS_H
#define DOUGH_PCONTACTS_H

#include "particle.hpp"

namespace dough {
    class ParticleContact {
        public:
        Particle* particle[2];
        real restitution;
        real penetration;
        Vector3 contactNormal;
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
        void resolveContacts(ParticleContact *contactArray, unsigned numContacts, real time);
    };
}

#endif