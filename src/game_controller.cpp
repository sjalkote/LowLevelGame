
#include "game_controller.h"
#include "utils.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"

#include <iostream>
GameController::GameController(int argc, char* argv[], bool debug) : window(SCREEN_WIDTH, SCREEN_HEIGHT){
    this->debug = debug;
    if (argc > 1) this->name = argv[1];
    else this->name = "LowLevelGame";
    
}

bool GameController::init () {
    /** Inits the game
     * Returns whether the game was created properly
    */

    if (this->debug) std::cout << "Starting...\n";
    
    bool success = window.init(this->name, settings);

    if (!success) {
        std::cerr << "Error creating window: " << SDL_GetError() << "\n";
        return false;
    }
    this->isRunning = true;
    return true;
}

void GameController::update () {
    while (SDL_PollEvent(&(this->e))) {
        if (this->e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) this->isRunning = false;
        ImGui_ImplSDL2_ProcessEvent(&e);
    }
}

void GameController::quit () {
    if (this->debug) std::cout << "Exiting...\n";
    this->window.quit();
    
}