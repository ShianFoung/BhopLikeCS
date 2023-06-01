#pragma once

class Shader
{
public:
    Shader(const char* shaderFileName);

    void Activate();
    void Delete();

    void SetCameraUniform(glm::mat4& cameraMatrix);
    void SetUniform(const char* uniformName, const void* value);
protected:

private:
    GLuint shaderProgram;

    GLint cameraMatrixUniformLocation;

    GLuint loadShader(const char* filePath, GLenum shaderType);
    GLint getUniformLocation(const char* uniformName);
};
