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
        void addForce(Vector3 _force) {
            acceleration += _force*inverseMass;
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
            return acceleration*(real)(1/inverseMass);
        }
        Vector3 getAcceleration() {
            return acceleration;
        }

        void clearAccumulator() {
            acceleration = Vector3(0,0,0);
        }

        void integrate(real time);
    };
}