// Player.hpp

#ifndef PLAYER
#define PLAYER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "GameObject.hpp"
#include "Vectors.hpp"

class Player : public GameObject{
    public:
    int speed;

    int width, height;

    SDL_Texture* texture;

    int setTexture(char * path, SDL_Renderer* r);
    int setTexture(std::string path, SDL_Renderer* r);
    Player& move(int x, int y);
    Player& move(Vector2 dir);

    Vector3 GetLocation();
    void setLocation(int x, int y);
    void setLocation(Vector2 loc);
    void setLocation(int x, int y, int z);
    void setLocation(Vector3 loc);

    Player();
    Player(int speed);
    Player(int w, int h);
    Player(int w, int h, int speed);
};

#endif // PLAYER