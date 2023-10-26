#pragma once
#include "window.h"
#include "SDL.h"

class GameController {
    /**
    Main game class 
    */

    private:
        bool debug;
        char const *name;
        Window window;
        SDL_Event e;
    
    public:
        bool isRunning = false;
    
    public:
        GameController(int argc, char* argv[], bool debug);
        bool init ();
        void update ();
        void quit ();
};