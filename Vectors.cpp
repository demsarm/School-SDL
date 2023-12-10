#include "Vectors.hpp"

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(int x, int y) : x(x), y(y) {}
Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y) {}
Vector2::Vector2(const Vector3& other) : x(other.x), y(other.y) {}

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(int x, int y) : x(x), y(y), z(0) {} 
Vector3::Vector3(int x, int y, int z) : x(x), y(y), z(z) {}
Vector3::Vector3(const Vector2& other) : x(other.x), y(other.y), z(0) {};
Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {};