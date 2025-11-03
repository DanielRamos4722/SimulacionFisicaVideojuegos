#pragma once

#include <cmath>

class Vector3D {
    float x, y, z;
public:
    Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    Vector3D(const Vector3D& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3D(const physx::PxVec3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3D& operator=(const Vector3D& v) {
        if (this != &v) { x = v.x; y = v.y; z = v.z; }
        return *this;
    }
    inline float getX() const { return x; }
    inline float getY() const { return y; }
    inline float getZ() const { return z; }
    float magnitude() const { return std::sqrt(x * x + y * y + z * z); }
    Vector3D normalize() const { float m = magnitude(); return m == 0 ? *this : Vector3D(x / m, y / m, z / m); }

    Vector3D operator+(const Vector3D& v) const { return Vector3D(x + v.x, y + v.y, z + v.z); }
    Vector3D operator-(const Vector3D& v) const { return Vector3D(x - v.x, y - v.y, z - v.z); }
    Vector3D operator*(float esc) const { return Vector3D(x * esc, y * esc, z * esc); }
    Vector3D operator/(float esc) const { return Vector3D(x / esc, y / esc, z / esc); }

    Vector3D& operator+=(const Vector3D& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3D& operator-=(const Vector3D& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3D& operator*=(float esc) { x *= esc; y *= esc; z *= esc; return *this; }
    Vector3D& operator/=(float esc) { x /= esc; y /= esc; z /= esc; return *this; }

    float dot(const Vector3D& v) const { return x * v.x + y * v.y + z * v.z; }
    Vector3D cross(const Vector3D& v) const {
        return Vector3D(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }
    operator physx::PxVec3() const {
        return physx::PxVec3(x, y, z);
    }
};