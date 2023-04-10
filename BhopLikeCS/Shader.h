#pragma once

#include "GLHeader.h"

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
    void SetUniform(const float* model, const float* view, const float* projection);
    void SetTemp(const float* value);
private:
    GLuint _loadShader(const char* fileName, GLenum shaderType);

    GLuint _vertID;
    GLuint _fragID;
    GLuint _programID;

    GLint _modelLocation;
    GLint _viewLocation;
    GLint _projectionLocation;
};
