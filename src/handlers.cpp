#include <iostream>
#include <cmath>
#include <vector>
#include "SDL.h"
#include "SDL_opengl.h"
#include "handlers.h"

enum class Action {
    Up,
    Down,
    Left,
    Right,
    Jump
};

void handleInput(const Uint8* keyPressed) {
    static const std::vector<std::pair<SDL_Scancode, Action>> keyMappings = {
        {SDL_SCANCODE_UP, Action::Up},
        {SDL_SCANCODE_W, Action::Up},
        {SDL_SCANCODE_DOWN, Action::Down},
        {SDL_SCANCODE_S, Action::Down},
        {SDL_SCANCODE_LEFT, Action::Left},
        {SDL_SCANCODE_A, Action::Left},
        {SDL_SCANCODE_RIGHT, Action::Right},
        {SDL_SCANCODE_D, Action::Right},
        {SDL_SCANCODE_SPACE, Action::Jump}
    };

    for (const auto& [scancode, action] : keyMappings) {
        if (keyPressed[scancode]) {
            std::cout << static_cast<int>(action) << '\n';
        }
    }
}

void handleResize(int w, int h) {
    h = (h != 0) ? h : 1; // prevent div by zero
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = static_cast<float>(w) / static_cast<float>(h);
    constexpr float fov = 45.0f;
    constexpr float zNear = 0.1f;
    constexpr float zFar = 100.0f;

    float top = zNear * std::tan(fov * 0.5f * 3.14159265f / 180.0f);
    float bottom = -top;
    float right = top * aspectRatio;
    float left = -right;

    glFrustum(left, right, bottom, top, zNear, zFar);

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
}
