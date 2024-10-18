#include "dough/body.hpp"

using namespace dough;

void RigidBody::setInteriaTensor(const Matrix3 &interiaTensor) {
    inverseInertiaTensor.setInverse(interiaTensor);
}