#include "core.hpp"

namespace dough {
    class Particle {
        protected:
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration; 
        real damping;
        real inverseMass;
        public:
        Particle(Vector3 position, Vector3 velocity, real damping, real Mass)
        : position(position), velocity(velocity), damping(damping) {
            setMass(Mass);
        }
        void setMass(real Mass) {
            inverseMass = (real)1/Mass;
        }
        void integrate(real time);
        
        Vector3 getPosition() {
            return position;
        }
    };
}