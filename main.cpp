// External includes
#include <SDL2/SDL.h> //SDL
#include <SDL2/SDL_image.h> // Textures
#include <iostream>    // Scanf, printf
#include <math.h>     // Min, Max
#include <string>

// Custom headers
#include "GameObject.hpp"
#include "Player.hpp"
#include "Vectors.hpp"

using namespace std;

int height = 2000;
int width = 3000;

bool run = true;

int SDL_SetRenderDrawColorRGBA(SDL_Renderer * renderer, SDL_Color color);
bool SDL_CompareRendererDrawColor(SDL_Renderer* renderer, SDL_Color& color);
void BlankScreen(SDL_Renderer * renderer);
void SetWindowSize();
void SetWindowSize(int width, int height);

/*
class Player{
    public:
        int width = 80, height = 80;
        float xPos, yPos;
        int speed = 100;
        SDL_Color color = {0, 0, 0, 0};

        SDL_Rect playerTexture = {0, 0, width, height};

        Player() : xPos(width/2), yPos(height/2) {}
        
        void move(float x, float y){
            xPos += x;
            yPos += y;
            playerTexture.x = xPos;
            playerTexture.y = yPos;
        }
};*/



string player_sprite_path ="Sprites/player.png";
string cursor_sprite_path_empty = "Sprites/cursor-empty.png";
string cursor_sprite_path_press = "Sprites/cursor-hold.png";

int main(){
    
    // Initialize SDL and return 1 if failed
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        cout << "Failed to initialize SDL";
        return 1;
    }

    SetWindowSize();
    
    // Create the window and renderer
    // Rendering using surfaces is also a thing but it's kind of outdated
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Create the window
    window = SDL_CreateWindow(
        "Fun Game",             // Title of window
        SDL_WINDOWPOS_CENTERED, // X position of window
        SDL_WINDOWPOS_CENTERED, // Y position of window
        width,                  // width of window
        height,                 // height of window
        0                       // some flags that SDL wants. Only god knows what these are
    );

    // Get the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        // Exit if renderer doesn't exist
        printf("Failed to create renderer\n");
        SDL_Quit();
        return 1;
    } else if (window == nullptr) {
        // Exit if window doesn't exist
        printf("Failed to create window\n");
        SDL_Quit();
        return 1;
    } else printf("Successfully made window and renderer\n");

    // Clear screen
    BlankScreen(renderer);
    
    int maxFramerate = 60;
    //double fps;

    SDL_Event event;
    const Uint8* keyboardState;

    float xMovement, yMovement;

    Uint64 startTime;
    double deltaTime = 1000.0/maxFramerate;
    Uint64 frameTime = deltaTime * 1000;
    
    Player player(80, 80, 160);
    player.location.x = width/2;
    player.location.y = height/2;


    // Main loop
    while (run){
        startTime = SDL_GetTicks64();
        SDL_Delay(std::max(0.0, (1000.0/maxFramerate) - frameTime/2));

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Event processing
        while (SDL_PollEvent(&event) != 0){
            switch (event.type)
            {
            case SDL_QUIT:
                run = false;
                break;
            default:
                break;
            }
        }

        // Player movement stuff
        keyboardState = SDL_GetKeyboardState(NULL);

        // Mouse
        int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        SDL_GetMouseFocus() == window ? SDL_ShowCursor(SDL_DISABLE) : SDL_ShowCursor(SDL_ENABLE);

        string cursor_sprite_path;

        if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) || mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)){
            cursor_sprite_path = cursor_sprite_path_press;
        } else {
            cursor_sprite_path = cursor_sprite_path_empty;
        }

        SDL_Surface* cursor_surface = IMG_Load(cursor_sprite_path.c_str());
        SDL_Texture* cursor_texture;
        bool cursor_image_failed = 0;
        if (cursor_surface == NULL){
            if (!cursor_image_failed) cout << "Failed to get cursor image" << IMG_GetError() << endl;
            cursor_image_failed = 1;
            SDL_Quit();  
        } else {
            cursor_texture = SDL_CreateTextureFromSurface(renderer, cursor_surface);
            SDL_FreeSurface(cursor_surface);
            cursor_image_failed = 0;
        }


        if(keyboardState[SDL_SCANCODE_ESCAPE]){
            run = false;
        }

        if(keyboardState[SDL_SCANCODE_SPACE]) {
            player.setLocation(width/2, height/2);
        }

        xMovement = (keyboardState[SDL_SCANCODE_D] - keyboardState[SDL_SCANCODE_A]) * player.speed * deltaTime; 
        yMovement = (keyboardState[SDL_SCANCODE_S] - keyboardState[SDL_SCANCODE_W]) * player.speed * deltaTime;

        player.move(xMovement, yMovement);

        if(player.setTexture(player_sprite_path, renderer)){
            cerr << "Failed renderCopy - player " << IMG_GetError() << "\n";
            SDL_Quit();
        }
        

        // Player
        SDL_Rect playerRect = {player.location.x + player.width/2, player.location.y + player.height/2, player.width, player.height};
        if (SDL_RenderCopy(renderer, player.texture, NULL, &playerRect)) {
            cout << "Failed RenderCopy (player)\n";
        }
        
        SDL_Rect cursor = {mouseX, mouseY, 20, 20};
        if (SDL_RenderCopy(renderer, cursor_texture, NULL, &cursor)) {
            cout << "Failed RenderCopy (cursor)\n";
        }

        SDL_RenderPresent(renderer);

        // Frame stuff
        frameTime = SDL_GetTicks64() - startTime;
        deltaTime = frameTime/1000.0;
        //printf("%llu, %llu, %llu, %0.3f\n", startTime, SDL_GetTicks(), frameTime, deltaTime);

        //fps = 1000.0/(std::max((int)frameTime, 1));

        //printf("%llu, %llu, %llu\n", SDL_GetTicks64(), startTime, frameTime);
        
        // fflush(stdout);
        // printf("%0.0f, %0.2f, %llu\r", fps, deltaTime, SDL_GetTicks64());
    }


    // Exit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // End program
    return 0;
}

int SDL_SetRenderDrawColorRGBA(SDL_Renderer * renderer, SDL_Color color){
    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

bool SDL_CompareRendererDrawColor(SDL_Renderer* renderer, SDL_Color& color) {
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

    return (r == color.r && g == color.g && b == color.b && a == color.a);
}

void BlankScreen(SDL_Renderer * renderer){
    SDL_Color color = {255, 255, 255, 255};
    if (!SDL_CompareRendererDrawColor(renderer, color)){
        if (!SDL_SetRenderDrawColorRGBA(renderer, color)){
            printf("Set color\n");
        } else {
            printf("Failed to set color, exiting app\n");
            run = false;
        }
    }
}

// Sets the width and height variables to 0.9 * screen size.
void SetWindowSize(){
    SDL_DisplayMode displayMode;
    if ((SDL_GetCurrentDisplayMode(0, &displayMode) != 0)){
        cerr << "Failed to get current display mode " << SDL_GetError() << "\n";
        SDL_Quit();
        exit(1);
    }
    width = displayMode.w * 0.95;
    height = displayMode.h * 0.95;
}
void SetWindowSize(int w, int h){
    width = w;
    height = h;
}
