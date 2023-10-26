#include <iostream>
#define SDL_MAIN_HANDLED
#include "game_controller.h"

// TODO: Move to diff file, this is getting messy rq
void handleInput(const Uint8* keyPressed) {
    if (keyPressed[SDL_SCANCODE_UP] || keyPressed[SDL_SCANCODE_W]) { // UP
        std::cout << "UP\n";
    }
    else if (keyPressed[SDL_SCANCODE_DOWN] || keyPressed[SDL_SCANCODE_S]) { // DOWN
        std::cout << "DOWN\n";
    }
    else if (keyPressed[SDL_SCANCODE_LEFT] || keyPressed[SDL_SCANCODE_A]) { // LEFT
        std::cout << "LEFT\n";
    }
    else if (keyPressed[SDL_SCANCODE_RIGHT] || keyPressed[SDL_SCANCODE_D]) { // RIGHT
        std::cout << "RIGHT\n";
    }
    else if (keyPressed[SDL_SCANCODE_SPACE]) { // JUMP
        std::cout << "JUMP\n";
    }
}

/* void update() {
    // TODO: move debug menu to diff file
    // Start ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    // Add settings menu items here
    if (ImGui::Checkbox("VSync", &settings.vsync)) {
        std::cout << "VSync: " << (settings.vsync ? "ON" : "OFF") << "\n";
        SDL_RenderSetVSync(renderer, settings.vsync ? SDL_TRUE : SDL_FALSE);
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
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}
*/

// Usage: ./LowLevelGame [name]
int main(int argc, char* args[]) {


    // Create window
    GameController gc = GameController(argc, args, true);
    if (!gc.init()) {
        return EXIT_FAILURE;
    }
    
    // Keep the window open until the user closes it (we will receive a close event)
    while (gc.isRunning) {
        gc.update();
    }
    
    gc.quit();
    return EXIT_SUCCESS;
}