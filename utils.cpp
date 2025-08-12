#include "utils.h"

#include <math.h>

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::GetLength() {
    return sqrt((*this)*(*this));
}

Vector3 Vector3::operator+(Vector3 other) {
    return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}
Vector3 Vector3::operator-(Vector3 other) {
    return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

float Vector3::operator*(Vector3 other) {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 operator*(Vector3 vec, float mult) {
    return Vector3(vec.x * mult, vec.y * mult, vec.z * mult);
}