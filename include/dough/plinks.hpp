#ifndef DOUGH_PLINKS_H
#define DOUGH_PLINKS_H

#include "pcontacts.hpp"

namespace dough {
    class ParticleLink : public ParticleContactGenerator {
        public:
        Particle* particle[2];

        protected:
        real currentLength() const;

        public:
        virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;
    };

    class ParticleCable : public ParticleLink {
        public:
        real maxLength;
        real restitution;

        virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
    };

    class ParticleRod : public ParticleLink {
        public:
        real length;

        virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
    };
}

#endif