#include "pfgen.hpp"


namespace dough {
    class ParticleContact {
        public:
        Particle* particle[2];
        real restitution;
        Vector3 contactNormal;
        protected:
        void resolve(real time);
        real calculateSeparatingVelocity() const;
        private:
        void resolveVelocity(real time);
    };
}