#include "window.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <iostream>

Window::Window (int screen_width, int screen_height) {
	this->width = screen_width;
	this->height = screen_height;
}

bool Window::init (char const *name, Settings settings) {
	/*
		* Init window.
		* Will return whether window has been properly created.
	*/

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) return false;

	// Create window
	this->window = SDL_CreateWindow(
		name,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		this->width, this->height,
		SDL_WINDOW_RESIZABLE);
	if (!(this->window)) return false;
	SDL_SetWindowTitle(this->window, name);

	// Create renderer
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | (settings.vsync ? SDL_RENDERER_PRESENTVSYNC : 0));
	if (!(this->renderer)) return false;

	// Create GUI context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO();
	io.DisplaySize = ImVec2(this->width, this->height);
	ImGui_ImplSDLRenderer2_Init(this->renderer);
	ImGui_ImplSDL2_InitForSDLRenderer(this->window, this->renderer);

	if (!ImGui::GetCurrentContext()) {
		std::cout << "Unable to create Context\n";
		return false;
	}
	return true;
}

void Window::quit () {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}
