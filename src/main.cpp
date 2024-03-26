#define SDL_MAIN_HANDLED
#include <iostream>
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "SDL_opengl.h"
#include "handlers.h"
#include "objloader.h"

// Screen dimension constants
int SCREEN_WIDTH = 1920 / 2;
int SCREEN_HEIGHT = 1080 / 2;

// Window and Renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// executable is in ./cmake-build-debug
ObjAsset asset = ObjAsset("../src/assets/monkey.obj");

// User settings
struct Settings {
    bool showFPS = true;
    bool vsync = true;
    int fpsLimit = 60;
    bool fullscreen = false;
} settings;


void update() {
    // TODO: move debug menu to diff file
    // Start ImGui frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    ImGui_ImplSDL2_NewFrame(window);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    // Add settings menu items here
    if (ImGui::Checkbox("VSync", &settings.vsync)) {
        std::cout << "VSync: " << (settings.vsync ? "ON" : "OFF") << "\n";
        SDL_GL_SetSwapInterval(static_cast<int>(settings.vsync));
    }
    ImGui::Checkbox("Show FPS", &settings.showFPS);
    ImGui::SliderInt("FPS Limit", &settings.fpsLimit, 1, 250);
    ImGui::Checkbox("Fullscreen", &settings.fullscreen);
    ImGui::End();

    static Uint32 lastFrame = 0;
    Uint32 currentFrame = SDL_GetTicks();
    float deltaTime = (currentFrame - lastFrame) / 1000.0f;
    lastFrame = currentFrame;

    float frameTime = 1.0f / settings.fpsLimit;
    if (deltaTime < frameTime) {
        SDL_Delay((Uint32)((frameTime - deltaTime) * 1000.0f));
        currentFrame = SDL_GetTicks();
        deltaTime = (currentFrame - lastFrame) / 1000.0f;
        lastFrame = currentFrame;
    }

    if (settings.showFPS) {
        ImGui::SetNextWindowPos(ImVec2(5, 5));
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
    }

    SDL_SetWindowFullscreen(window, settings.fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

    const Uint8* keyPressed = SDL_GetKeyboardState(nullptr);
    handleInput(keyPressed);
    asset.Render();

    // Draw
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
    //SDL_RenderPresent(renderer);
}

void quit() {
    std::cout << "Exiting...\n";
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

// Usage: ./LowLevelGame
int main(int argc, char* args[]) {
    std::cout << "Starting...\n";

    // Initialize SDL, window, renderer, etc.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    std::cout << "SDL init successful.\n";

    // Create window
    window = SDL_CreateWindow(
        "LowLevelGame",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Error creating OpenGL context: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    SDL_GL_MakeCurrent(window, glContext);

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
    std::cout << "Window and renderer init successful.\n";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();

    if (!ImGui::GetCurrentContext()) {
        std::cout << "Unable to create Context\n";
    }

    // Keep the window open until the user closes it (we will receive a close event)
    SDL_Event e;
    bool shouldQuit = false;
    while (!shouldQuit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) shouldQuit = true;
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
                SCREEN_WIDTH = e.window.data1;
                SCREEN_HEIGHT = e.window.data2;
                handleResize(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            ImGui_ImplSDL2_ProcessEvent(&e);
        }
        update();
    }
    quit();
    return EXIT_SUCCESS;
}