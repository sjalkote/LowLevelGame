#include <iostream>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

using std::cout;
using std::endl;
using std::string;

// Screen dimension constants
int SCREEN_WIDTH = 1920 / 2;
int SCREEN_HEIGHT = 1080 / 2;

// Window and Renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// User settings
struct Settings {
    bool showFPS = true;
    bool vsync = true;
} settings;

// TODO: Move to diff file, this is getting messy rq
void handleInput(const Uint8* keyPressed)
{
    if (keyPressed[SDL_SCANCODE_UP] || keyPressed[SDL_SCANCODE_W]) { // UP
        cout << "UP" << endl;
    }
    else if (keyPressed[SDL_SCANCODE_DOWN] || keyPressed[SDL_SCANCODE_S]) { // DOWN
        cout << "DOWN" << endl;
    }
    else if (keyPressed[SDL_SCANCODE_LEFT] || keyPressed[SDL_SCANCODE_A]) { // LEFT
        cout << "LEFT" << endl;
    }
    else if (keyPressed[SDL_SCANCODE_RIGHT] || keyPressed[SDL_SCANCODE_D]) { // RIGHT
        cout << "RIGHT" << endl;
    }
    else if (keyPressed[SDL_SCANCODE_SPACE]) { // JUMP
        cout << "JUMP" << endl;
    }
}

void update() {

    // TODO: move debug menu to diff file
    // Start ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    // Add settings menu items here
    if (ImGui::Checkbox("VSync", &settings.vsync))
    {
        std::cout << "VSync: " << (settings.vsync ? "ON" : "OFF") << std::endl;
        SDL_RenderSetVSync(renderer, settings.vsync ? SDL_TRUE : SDL_FALSE);
    }
    ImGui::Checkbox("Show FPS", &settings.showFPS);
    ImGui::End();

    if (settings.showFPS) {
        ImGui::SetNextWindowPos(ImVec2(5, 5));
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
    }

    const Uint8* keyPressed = SDL_GetKeyboardState(nullptr);
    handleInput(keyPressed);

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
        SDL_RenderDrawLine(renderer, x - i, 0, x - i, SCREEN_HEIGHT);
    }
    x = x > SCREEN_WIDTH ? 0 : x + 1;

    // Draw
    ImGui::Render();
    SDL_RenderClear(renderer); // Clear the SDL renderer before rendering ImGui
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer); // Present the rendered ImGui frame
}

void quit()
{
    cout << "Exiting...\n";
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

// Usage: ./LowLevelGame
int main(int argc, char* args[]) {
    cout << "Starting...\n";

    // Initialize SDL, window, renderer, etc.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    cout << "SDL init successful.\n";

    // Create window
    window = SDL_CreateWindow(
        "LowLevelGame",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    SDL_SetWindowTitle(window, "LowLevelGame");

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | (settings.vsync ? SDL_RENDERER_PRESENTVSYNC : 0));
    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    cout << "Window and renderer init successful.";


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);
    ImGui_ImplSDLRenderer2_Init(renderer);
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);

    if (!ImGui::GetCurrentContext()) {
        cout << "Unable to create Context";
    }

    // Keep the window open until the user closes it (we will receive a close event)
    SDL_Event e;
    bool shouldQuit = false;
    while (!shouldQuit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) shouldQuit = true;
            ImGui_ImplSDL2_ProcessEvent(&e);
        }
        update();
    }
    quit();
    return EXIT_SUCCESS;
}