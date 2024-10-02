#include "pfgen.hpp"


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
}