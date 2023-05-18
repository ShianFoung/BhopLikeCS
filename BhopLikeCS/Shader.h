#pragma once

#include "Header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Shader
{
public:
    Shader(const char* name);
    ~Shader();

    void Use();
    void SetCameraUniform(const float* value);
private:
    GLuint _vertID;
    GLuint _fragID;
    GLuint _programID;

    GLint _cameraMatrixLocation;

    GLuint _loadShader(const char* fileName, GLenum shaderType);
};
