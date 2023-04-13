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
    void UnUse();
private:
    GLuint _vertID;
    GLuint _fragID;
    GLuint _programID;

    GLint _modelLocation;
    GLint _viewLocation;
    GLint _projectionLocation;

    GLuint _loadShader(const char* fileName, GLenum shaderType);
};
