#include <iostream>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

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

    static float g_rotation_angle = 0.0f;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    float fov = 45.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;

    float top = zNear * std::tan(fov * 0.5f * 3.14159265f / 180.0f);
    float bottom = -top;
    float right = top * aspectRatio;
    float left = -right;

    glFrustum(left, right, bottom, top, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(g_rotation_angle, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);


    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    g_rotation_angle += 0.5f;

    // Draw

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
    //SDL_RenderPresent(renderer);
}

// Usage: ./LowLevelGame [name]
int main(int argc, char* args[]) {


    // Create window
    GameController gc = GameController(argc, args, true);
    if (!gc.init()) {
        return EXIT_FAILURE;
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
    
    gc.quit();
    return EXIT_SUCCESS;
}