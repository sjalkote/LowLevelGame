#pragma once

#include <vector>
#include "SDL_opengl.h"

class ObjAsset {
public:
    ObjAsset(const char* filePath);
    void Render();

private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> colors;

    void LoadObjFile(const char* filePath);
};
