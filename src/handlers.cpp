#include <iostream>
#include <cmath>
#include "SDL.h"
#include "SDL_opengl.h"
#include "handlers.h"

void handleInput(const Uint8 *keyPressed) {
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

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (float)w / (float)h;
    float fov = 45.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;

    float top = zNear * std::tan(fov * 0.5f * 3.14159265f / 180.0f);
    float bottom = -top;
    float right = top * aspectRatio;
    float left = -right;

    glFrustum(left, right, bottom, top, zNear, zFar);

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);

}