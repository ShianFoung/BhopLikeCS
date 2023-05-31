#pragma once

class Shader
{
public:
    Shader(const char* shaderFileName);

    void Use();
    void UnUse();
    void Delete();

    void SetCameraUniform(const float* value);
private:
    GLuint shaderProgram;

    GLint cameraMatrixLocation;

    GLuint loadShader(const char* filePath, GLenum shaderType);
    GLint getUniformLocation(const char* uniformName);
};
