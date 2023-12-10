// GameObject.hpp

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Vectors.hpp"

class GameObject {
    public:
    Vector3 location;

    GameObject();
    GameObject(int x, int y);
    GameObject(int x, int y, int z);
    GameObject(Vector2 l);
    GameObject(Vector3 l);
    GameObject(const GameObject& other);
};

#endif // GAMEOBJECT_HPP