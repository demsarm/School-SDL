// Player.cpp

#include "Player.hpp"

Player::Player() : GameObject(), speed(80) {}// location.x(0), location.y(0) {}
Player::Player(int speed) : GameObject(), speed(speed) {}
Player::Player(int w, int h) : GameObject(), speed(80), width(w), height(h) {}
Player::Player(int w, int h, int speed) : GameObject(), speed(speed), width(w), height(h) {}

int Player::setTexture(char * path, SDL_Renderer* r){
    SDL_Surface* player_surface = IMG_Load(path);
    if (player_surface == NULL){
        std::cerr << "Failed to get player image" << IMG_GetError() << std::endl;
        return -1;
        // SDL_Quit();  
    } else {
        texture = SDL_CreateTextureFromSurface(r, player_surface);
        SDL_FreeSurface(player_surface);
        std::cout << "Loaded player image\n";
        return 0;
    }
}

int Player::setTexture(std::string path, SDL_Renderer* r){
    SDL_Surface* player_surface = IMG_Load(path.c_str());
    if (player_surface == NULL){
        // std::cerr << "Failed to get player image" << IMG_GetError() << std::endl;
        SDL_FreeSurface(player_surface);
        return -1;
    } else {
        texture = SDL_CreateTextureFromSurface(r, player_surface);
        SDL_FreeSurface(player_surface);
        // std::cout << "Loaded player image\n";
        return 0;
    }
}

void Player::setLocation(int x, int y){
    location.x = x;
    location.y = y;
}

void Player::setLocation(int x, int y, int z){
    location.x = x;
    location.y = y;
    location.z = z;
}

void Player::setLocation(Vector2 loc){
    location.x = loc.x;
    location.y = loc.y;
}

void Player::setLocation(Vector3 loc){
    location.x = loc.x;
    location.y = loc.y;
    location.z = loc.z;
}

Vector3 Player::GetLocation(){
    return location;
}

Player& Player::move(Vector2 dir){
    location.x += dir.x;
    location.y += dir.x;

    return *this;
}

Player& Player::move(int x, int y){
    location.x += x;
    location.y += y;

    return *this;
}