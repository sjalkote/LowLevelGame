#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
using std::cout;
using std::endl;
using std::string;

// Screen dimension constants
int SCREEN_WIDTH = 1920 / 2;
int SCREEN_HEIGHT = 1080 / 2;

// Window and Renderer
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void update() {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) {          // UP
        cout << "UP" << endl;
    } else if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S]) { // DOWN
        cout << "DOWN" << endl;
    } else if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) { // LEFT
        cout << "LEFT" << endl;
    } else if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {// RIGHT
        cout << "RIGHT" << endl;
    } else if (keystates[SDL_SCANCODE_SPACE]) {                             // JUMP
        cout << "JUMP?" << endl;
    }

    // RENDERING STUFF
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Update screen size variables if the window was resized
    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    const int region1 = SCREEN_WIDTH / 3;
    const int region2 = region1 * 2;
    const int region3 = SCREEN_WIDTH;

    // slowly draw a line across the screen
    static int x = 0;
    // Cycle through RGB colors on each render
    static int r, g, b = 0;
    if (x == 0) r = g = b = 0;
    else if (x < region1) r += r >= 255 ? 0 : 1;
    else if (x < region2) g += g >= 255 ? 0 : 1;
    else if (x < region3) b += b >= 255 ? 0 : 1;
    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
    
    // Draw a new line every render.
    for (int i = 1; i <= x; i++) {
        SDL_RenderDrawLine(renderer, x-i, 0, x-i, SCREEN_HEIGHT);
    }
    x = x > SCREEN_WIDTH ? 0 : x+1;

    // Draw
    SDL_RenderPresent(renderer);
}

// Usage: ./LowLevelGame
int main(int argc, char* args[]) {
    cout << "Starting..." << endl;

#pragma region Initialize SDL, window, renderer, etc.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl; return EXIT_FAILURE;
    }
    cout << "SDL init successful.\n";

    // Create window
    window = SDL_CreateWindow(
        "LowLevelGame", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (window == NULL) {
        cout << "Error creating window: " << SDL_GetError() << endl; return EXIT_FAILURE;
    }
    SDL_SetWindowTitle(window, "LowLevelGame");

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "Error creating renderer: " << SDL_GetError() << endl; return EXIT_FAILURE;
    }

    cout << "Window and renderer init successful.\n";
#pragma endregion

    // Keep the window open until the user closes it (we will receive a close event)
    SDL_Event e;
    bool shouldQuit = false;
    while (!shouldQuit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) shouldQuit = true;
        }
        update();
    }
    
    // TODO: Move exit tasks to their own Quit() function?
    cout << "Exiting..." << endl;
    SDL_DestroyRenderer(renderer); renderer = NULL;
    SDL_DestroyWindow(window); window = NULL;
    SDL_Quit();
    return EXIT_SUCCESS;
}
