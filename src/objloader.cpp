#include "objloader.h"
#include "SDL_opengl.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib> 

ObjAsset::ObjAsset(const char* filePath) {
    LoadObjFile(filePath);
    for (size_t i = 0; i < vertices.size(); i += 3) {
        // random colors
        GLfloat r = static_cast<GLfloat>(rand()) / RAND_MAX;
        GLfloat g = static_cast<GLfloat>(rand()) / RAND_MAX;
        GLfloat b = static_cast<GLfloat>(rand()) / RAND_MAX;

        colors.push_back(r);
        colors.push_back(g);
        colors.push_back(b);
    }
}

void ObjAsset::Render() {
    //std::cout << "Vertces: ";
    //for (GLfloat element : vertices) {
    //    std::cout << element << " ";
    //}

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    static float rotationAngle = 0.0f;
    rotationAngle += 1.0f;

    glPushMatrix();
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < indices.size(); ++i) {
        size_t vIndex = indices[i] * 3;

        GLfloat x = vertices[vIndex];
        GLfloat y = vertices[vIndex + 1];
        GLfloat z = vertices[vIndex + 2];
        size_t colorIndex = vIndex;
        GLfloat r = colors[colorIndex];
        GLfloat g = colors[colorIndex + 1];
        GLfloat b = colors[colorIndex + 2];

        glColor3f(r, g, b);
        glVertex3f(x, y, z);
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
}


void ObjAsset::LoadObjFile(const char* filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return;
    }

    std::vector<GLfloat> tempVertices;
    std::vector<GLfloat> tempUVs;
    std::vector<GLfloat> tempNormals;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        iss >> token;

        if (token == "v") {
            GLfloat x, y, z;
            iss >> x >> y >> z;
            tempVertices.push_back(x);
            tempVertices.push_back(y);
            tempVertices.push_back(z);
        }
        else if (token == "vt") {
            GLfloat u, v;
            iss >> u >> v;
            tempUVs.push_back(u);
            tempUVs.push_back(v);
            //std::cout << "U:" << u << "V:" << v;
        }
        else if (token == "vn") {
            GLfloat nx, ny, nz;
            iss >> nx >> ny >> nz;
            tempNormals.push_back(nx);
            tempNormals.push_back(ny);
            tempNormals.push_back(nz);
        }
        else if (token == "f") {
            GLuint vIndex[3], uvIndex[3], nIndex[3];
            for (int i = 0; i < 3; ++i) {
                iss >> vIndex[i];
                // check if UV and normal indices are present
                if (iss.peek() == '/') {
                    iss.ignore(); // Ignore '/'
                    if (iss.peek() != '/') {
                        iss >> uvIndex[i];
                    }
                    if (iss.peek() == '/') {
                        iss.ignore(); // Ignore '/'
                        iss >> nIndex[i];
                    }
                }
                indices.push_back(vIndex[i] - 1);
            }
        }
    }

    for (size_t i = 0; i < indices.size(); ++i) {
        size_t vIndex = indices[i] * 3;
        vertices.push_back(tempVertices[vIndex]);
        vertices.push_back(tempVertices[vIndex + 1]);
        vertices.push_back(tempVertices[vIndex + 2]);
    }

    file.close();
}
