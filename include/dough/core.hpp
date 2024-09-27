#include "precision.hpp"

namespace dough {
    class Vector3 {
        public:
        real x, y, z;
        private:
        real pad;
        public:
        Vector3() : x(0), y(0), z(0) {}

        Vector3(const real x, const real y, const real z)
        : x(x), y(y), z(z) {};
        void invert() {
            x = -x;
            y = -y;
            z = -z;
        }
    };
}