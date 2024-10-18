#ifndef DOUGH_BODY_H
#define DOUGH_BODY_H

#include "core.hpp"
namespace dough {
    class RigidBody {
        private:
        Vector3 position;
        Quaternion orientation;
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
    };
}

#endif