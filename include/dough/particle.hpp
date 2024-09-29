#include "core.hpp"

namespace dough {
    class Particle {
        protected:
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration; 
        real damping;
        real inverseMass;
        Vector3 forceAccum;
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
        void addForce(Vector3 _force) {
            forceAccum += _force;
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
        Vector3 getVelocity() {
            return velocity;
        }
        real getMass() {
            return (real)1/inverseMass;
        }
        Vector3 getAccumulatedForce() {
            return forceAccum;
        }
        Vector3 getAcceleration() {
            return acceleration;
        }

        void clearAccumulator();

        void integrate(real time);

        bool hasFiniteMass() {
            return (inverseMass != 0);
        }
    };
}