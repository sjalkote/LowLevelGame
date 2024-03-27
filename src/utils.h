#pragma once

// Static variables
const int SCREEN_WIDTH = 1920 / 2;
const int SCREEN_HEIGHT = 1080 / 2;

// Util structs
const struct Settings {
    bool showFPS = true;
    bool vsync = true;
    int fpsLimit = 60;
    bool fullscreen = false;
} settings;

// Util functions