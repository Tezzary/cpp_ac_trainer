#pragma once

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);

    float GetLength();

    Vector3 operator+(Vector3 other);
    Vector3 operator-(Vector3 other);
    float operator*(Vector3 other);
};