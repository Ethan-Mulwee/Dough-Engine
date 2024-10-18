#ifndef DOUGH_CORE_H
#define DOUGH_CORE_H

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
        real operator*(const Vector3 vector) const {
            return x*vector.x + y*vector.y + z*vector.z;
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
        void clear() {
            x = 0; y = 0; z = 0;
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

    class Matrix3 {
    public:
        real data[9];

        Matrix3() {
            data[0] = data[1] = data[2] = data[3] = data[4] = data[5] =
                data[6] = data[7] = data[8] = 0;
        }

        Matrix3(real c0, real c1, real c2, real c3, real c4, real c5,
            real c6, real c7, real c8) {
            data[0] = c0; data[1] = c1; data[2] = c2;
            data[3] = c3; data[4] = c4; data[5] = c5;
            data[6] = c6; data[7] = c7; data[8] = c8;
        }

        Vector3 operator*(const Vector3 &vector) const {
            return Vector3(
                vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
                vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
                vector.x * data[6] + vector.y * data[7] + vector.z * data[8]
            );
        }

        Vector3 transform(const Vector3 &vector) const {
            return (*this) * vector;
        }

        Matrix3 operator*(const Matrix3 &o) const {
            return Matrix3(
                data[0]*o.data[0] + data[1]*o.data[3] + data[2]*o.data[6],
                data[0]*o.data[1] + data[1]*o.data[4] + data[2]*o.data[7],
                data[0]*o.data[2] + data[1]*o.data[5] + data[2]*o.data[8],

                data[3]*o.data[0] + data[4]*o.data[3] + data[5]*o.data[6],
                data[3]*o.data[1] + data[4]*o.data[4] + data[5]*o.data[7],
                data[3]*o.data[2] + data[4]*o.data[5] + data[5]*o.data[8],

                data[6]*o.data[0] + data[7]*o.data[3] + data[8]*o.data[6],
                data[6]*o.data[1] + data[7]*o.data[4] + data[8]*o.data[7],
                data[6]*o.data[2] + data[7]*o.data[5] + data[8]*o.data[8]
                );
        }

        void operator*=(const Matrix3 &o) {
            real t1;
            real t2;
            real t3;

            t1 = data[0]*o.data[0] + data[1]*o.data[3] + data[2]*o.data[6];
            t2 = data[0]*o.data[1] + data[1]*o.data[4] + data[2]*o.data[7];
            t3 = data[0]*o.data[2] + data[1]*o.data[5] + data[2]*o.data[8];
            data[0] = t1;
            data[1] = t2;
            data[2] = t3;

            t1 = data[3]*o.data[0] + data[4]*o.data[3] + data[5]*o.data[6];
            t2 = data[3]*o.data[1] + data[4]*o.data[4] + data[5]*o.data[7];
            t3 = data[3]*o.data[2] + data[4]*o.data[5] + data[5]*o.data[8];
            data[3] = t1;
            data[4] = t2;
            data[5] = t3;

            t1 = data[6]*o.data[0] + data[7]*o.data[3] + data[8]*o.data[6];
            t2 = data[6]*o.data[1] + data[7]*o.data[4] + data[8]*o.data[7];
            t3 = data[6]*o.data[2] + data[7]*o.data[5] + data[8]*o.data[8];
            data[6] = t1;
            data[7] = t2;
            data[8] = t3;
        }

        void setInverse(const Matrix3 &m) {
            real t4 = m.data[0]*m.data[4];
            real t6 = m.data[0]*m.data[5];
            real t8 = m.data[1]*m.data[3];
            real t10 = m.data[2]*m.data[3];
            real t12 = m.data[1]*m.data[6];
            real t14 = m.data[2]*m.data[6];

            // Calculate the determinant
            real t16 = (t4*m.data[8] - t6*m.data[7] - t8*m.data[8]+
                        t10*m.data[7] + t12*m.data[5] - t14*m.data[4]);

            // Make sure the determinant is non-zero.
            if (t16 == (real)0.0f) return;
            real t17 = 1/t16;

            data[0] = (m.data[4]*m.data[8]-m.data[5]*m.data[7])*t17;
            data[1] = -(m.data[1]*m.data[8]-m.data[2]*m.data[7])*t17;
            data[2] = (m.data[1]*m.data[5]-m.data[2]*m.data[4])*t17;
            data[3] = -(m.data[3]*m.data[8]-m.data[5]*m.data[6])*t17;
            data[4] = (m.data[0]*m.data[8]-t14)*t17;
            data[5] = -(t6-t10)*t17;
            data[6] = (m.data[3]*m.data[7]-m.data[4]*m.data[6])*t17;
            data[7] = -(m.data[0]*m.data[7]-t12)*t17;
            data[8] = (t4-t8)*t17;
        }

        Matrix3 inverse() const {
            Matrix3 result;
            result.setInverse(*this);
            return result;
        }

        void invert() {
            setInverse(*this);
        }
    };

    class Matrix4 {
    public:
        real data[12];

        Vector3 operator*(const Vector3 &vector) const {
            return Vector3(
                vector.x*data[0]+
                vector.y*data[1]+
                vector.z*data[2] + data[3],

                vector.x*data[4] +
                vector.y*data[5] +
                vector.z*data[6]+data[7],

                vector.x*data[8]+
                vector.y*data[9]+
                vector.z*data[10]+data[11]
            );
        }

        Vector3 transform( const Vector3 &vector) const {
            return (*this) * vector;
        }

        Matrix4 operator*(const Matrix4 &o) const {
            Matrix4 result;
            result.data[0] = (o.data[0]*data[0]) + (o.data[4]*data[1]) + (o.data[8]*data[2]);
            result.data[4] = (o.data[0]*data[4]) + (o.data[4]*data[5]) + (o.data[8]*data[6]);
            result.data[8] = (o.data[0]*data[8]) + (o.data[4]*data[9]) + (o.data[8]*data[10]);

            result.data[1] = (o.data[1]*data[0]) + (o.data[5]*data[1]) + (o.data[9]*data[2]);
            result.data[5] = (o.data[1]*data[4]) + (o.data[5]*data[5]) + (o.data[9]*data[6]);
            result.data[9] = (o.data[1]*data[8]) + (o.data[5]*data[9]) + (o.data[9]*data[10]);

            result.data[2] = (o.data[2]*data[0]) + (o.data[6]*data[1]) + (o.data[10]*data[2]);
            result.data[6] = (o.data[2]*data[4]) + (o.data[6]*data[5]) + (o.data[10]*data[6]);
            result.data[10] = (o.data[2]*data[8]) + (o.data[6]*data[9]) + (o.data[10]*data[10]);

            result.data[3] = (o.data[3]*data[0]) + (o.data[7]*data[1]) + (o.data[11]*data[2]) + data[3];
            result.data[7] = (o.data[3]*data[4]) + (o.data[7]*data[5]) + (o.data[11]*data[6]) + data[7];
            result.data[11] = (o.data[3]*data[8]) + (o.data[7]*data[9]) + (o.data[11]*data[10]) + data[11];

            return result;
        }

        real getDeterminant() const;

        void setInverse(const Matrix4 &m);

        Matrix4 inverse() const {
            Matrix4 result;
            result.setInverse(*this);
            return result;
        }

        void invert() {
            setInverse(*this);
        }
    };
}

#endif