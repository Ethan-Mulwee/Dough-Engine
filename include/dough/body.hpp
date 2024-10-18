#ifndef DOUGH_BODY_H
#define DOUGH_BODY_H

#include "core.hpp"
namespace dough {
    class RigidBody {
        private:
        Matrix3 inverseInertiaTensor;

        public:
        void setInteriaTensor(const Matrix3 &interiaTensor);
    };
}

#endif