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

        void operator*=(const real value) {
            x *= value; y *= value; z *= value; 
        }
        Vector3 operator*(const real value) {
            return Vector3(x*value,y*value,z*value); 
        }
        void operator+=(const Vector3 vector) {
            x += vector.x; y += vector.y; z += vector.z;
        }
        Vector3 operator+(const Vector3 vector) {
            return Vector3(x+vector.x, y+vector.y, z+vector.z);
        }
        void operator-=(const Vector3 vector) {
            x -= vector.x; y -= vector.y; z -= vector.z;
        }
        Vector3 operator-(const Vector3 vector) {
            return Vector3(x-vector.x, y-vector.y, z-vector.z);
        }
        
        void invert() {
            x = -x;
            y = -y;
            z = -z;
        }
        real magnitude() const {
            return real_sqrt(x*x+y*y+z*z);
        }
        real squareMagnitude() const {
            return (x*x+y*y+z*z);
        }
        void normalize() {
            real length = magnitude();
            if (length > 0) {
                (*this) *= ((real)1)/length;
            }
        }
    };
}