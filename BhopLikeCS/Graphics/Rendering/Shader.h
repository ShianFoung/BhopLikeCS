#pragma once

class Shader
{
public:
    Shader(const char* shaderFileName);

    void Activate();
    void Delete();

    void SetCameraUniform(glm::mat4& cameraMatrix);
    void SetUniform1i(const char* uniformName, const int value);
protected:

private:
    GLuint shaderProgram;

    GLint cameraMatrixUniformLocation;

    GLuint loadShader(const char* filePath, GLenum shaderType);
    GLint getUniformLocation(const char* uniformName);
};
