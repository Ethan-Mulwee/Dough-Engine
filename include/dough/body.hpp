#ifndef DOUGH_BODY_H
#define DOUGH_BODY_H

#include "core.hpp"
namespace dough {
    class RigidBody {
        private:
        Vector3 position;
        Quaternion orientation;
        
        Vector3 velocity;
        Vector3 rotation;

        Vector3 acceleration;
        Vector3 lastFrameAcceleration;

        real inverseMass;
        
        real angularDamping;
        real linearDamping;
        Matrix3 inverseInertiaTensor;

        Vector3 forceAccum;
        Vector3 torqueAccum;

        

        bool isAwake;

        public:
        void setInteriaTensor(const Matrix3 &interiaTensor);

        void integrate(real time);

        void clearAccumlators();

        void addForce(const Vector3 &force);

        void addForceAtPoint(const Vector3 &force, const Vector3 &point);

        void addForceAtBodyPoint(const Vector3 &force, const Vector3 &point);

        Vector3 getPosition() {
            return position;
        }

        void setInverseMass(real i) {
            inverseMass = i;
        }
    };
}

#endif