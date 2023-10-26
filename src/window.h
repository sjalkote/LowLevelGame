#pragma once
#include "SDL.h"
#include "utils.h"


class Window {
    /**
	Class to manage all rendering elements of the game.
	*/

    private: 
		int width;
		int height;
		SDL_Window* window;
		SDL_Renderer* renderer;
	
	public:
		// Public attributes

    public:
        Window (int screen_width, int screen_height);
        bool init (char const *name, Settings settings);
		void quit ();
};