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
        void setPosition(Vector3 _position) {
            position = _position;
        }
        void setVelocity(Vector3 _velocity) {
            velocity = _velocity;
        }
        void setAcceleration(Vector3 _acceleration) {
            acceleration = _acceleration;
        }
        void setDamping(real _damping) {
            damping = _damping;
        }
        void setMass(real Mass) {
            inverseMass = (real)1/Mass;
        }
        
        Vector3 getPosition() {
            return position;
        }
        Vector3 getVeloicty() {
            return velocity;
        }

        void clearAcceleration() {
            acceleration = Vector3(0,0,0);
        }

        void integrate(real time);
    };
}