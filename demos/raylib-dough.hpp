#include "dough/core.hpp"
#include "raylib.h"

namespace RaytoDoh {
    Vector3 ConvertToRay(dough::Vector3 vector) {
        return Vector3{vector.x, vector.y, vector.z};
    }
    dough::Vector3 ConvertToDoh(Vector3 vector) {
        return dough::Vector3(vector.x, vector.y, vector.z);
    }
};