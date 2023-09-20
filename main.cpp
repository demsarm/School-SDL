#include <SDL2/SDL.h> //SDL
#include <stdio.h>    // Scanf, printf
#include <math.h>     // Min, Max

#define HEIGHT 600
#define WIDTH 800

bool run = true;

int SDL_SetRenderDrawColorRGBA(SDL_Renderer * renderer, SDL_Color color);
bool SDL_CompareRendererDrawColor(SDL_Renderer* renderer, SDL_Color& color);
void BlankScreen(SDL_Renderer * renderer);

class Player{
    public:
        int width = 50, height = 50;
        float xPos = WIDTH/2, yPos = HEIGHT/2;
        int speed = 100;
        SDL_Color color = {0, 0, 0, 0};

        
        void move(float x, float y){
            xPos += x;
            yPos += y;
        }
};

class Player player;

int main(){
    // Initialize SDL and return 1 if failed
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        return 1;
    }

    // Create the window and renderer
    // Rendering using surfaces is also a thing but it's kind of outdated
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Create the window
    window = SDL_CreateWindow(
        "Fun Game",             // Title of window
        SDL_WINDOWPOS_CENTERED, // X position of window
        SDL_WINDOWPOS_CENTERED, // Y position of window
        WIDTH,                  // width of window
        HEIGHT,                 // height of window
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
    double fps;

    SDL_Event event;
    const Uint8* keyboardState;

    float xMovement, yMovement;

    Uint64 startTime;
    double deltaTime = 1000.0/maxFramerate;
    Uint64 frameTime = deltaTime * 1000;
    
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
        
        if(keyboardState[SDL_SCANCODE_ESCAPE]){
            run = false;
        }

        if(keyboardState[SDL_SCANCODE_SPACE]) {
            player.xPos = WIDTH/2;
            player.yPos = HEIGHT/2;
        }

        xMovement = (keyboardState[SDL_SCANCODE_D] - keyboardState[SDL_SCANCODE_A]) * player.speed * deltaTime; 
        yMovement = (keyboardState[SDL_SCANCODE_S] - keyboardState[SDL_SCANCODE_W]) * player.speed * deltaTime;

        player.move(xMovement, yMovement);

        SDL_Rect playerRect = {(int)player.xPos + player.width/2, (int)player.yPos + player.height/2, player.width, player.height};

        SDL_SetRenderDrawColorRGBA(renderer, player.color);
        SDL_RenderFillRect(renderer, &playerRect);

        SDL_RenderPresent(renderer);

        // Frame stuff
        frameTime = SDL_GetTicks64() - startTime;
        deltaTime = frameTime/1000.0;
        //printf("%llu, %llu, %llu, %0.3f\n", startTime, SDL_GetTicks(), frameTime, deltaTime);

        fps = 1000.0/(std::max((int)frameTime, 1));

        //printf("%llu, %llu, %llu\n", SDL_GetTicks64(), startTime, frameTime);
        fflush(stdout);
        
        printf("%0.0f, %0.2f, %llu\r", fps, deltaTime, SDL_GetTicks64());
        
        
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