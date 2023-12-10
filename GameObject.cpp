#include "GameObject.hpp"



GameObject::GameObject() : location(Vector3(0, 0, 0)) {}
GameObject::GameObject(int x, int y) : location(Vector3(x, y, 0)) {}
GameObject::GameObject(int x, int y, int z) : location(Vector3(x, y, z)) {}
GameObject::GameObject(Vector3 l) : location(l) {}
GameObject::GameObject(Vector2 l) : location(l) {}
GameObject::GameObject(const GameObject& other) : location(other.location) {}