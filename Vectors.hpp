#ifndef VECTORS_HPP
#define VECTORS_HPP

struct Vector3;

struct Vector2{
    int x, y;

    Vector2();
    Vector2(int x, int y);
    Vector2(const Vector2& other);
    Vector2(const Vector3& other);
};

struct Vector3{
    int x, y, z;

    Vector3();
    Vector3(int x, int y);
    Vector3(int x, int y, int z);
    Vector3(const Vector2& other);
    Vector3(const Vector3& other);
};

#endif