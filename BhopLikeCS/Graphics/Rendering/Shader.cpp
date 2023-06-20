#include "../Header.h"

#include "Shader.h"

std::string getFileContents(const char* filePath)
{
    std::ifstream shaderFileStream(filePath, std::ios::binary);

    if (!shaderFileStream.is_open())
    {
        std::string errorMessage = std::format("Cannot Open Shader File ({}).", filePath);
        std::cout << errorMessage << std::endl;
        throw std::exception(errorMessage.c_str());
    }

    std::string contents;

    shaderFileStream.seekg(0, std::ios::end);
    contents.resize(shaderFileStream.tellg());
    shaderFileStream.seekg(0, std::ios::beg);
    shaderFileStream.read(&contents[0], contents.size());
    shaderFileStream.close();

    return contents;
}

Shader::Shader(const char* shaderFileName)
{
    const std::string vertPath = std::format("Assets/Shaders/{}.vert", shaderFileName);
    const std::string fragPath = std::format("Assets/Shaders/{}.frag", shaderFileName);

    GLuint vertexShader = this->loadShader(vertPath.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = this->loadShader(fragPath.c_str(), GL_FRAGMENT_SHADER);
    this->shaderProgram = glCreateProgram();

    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    glLinkProgram(this->shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    this->cameraMatrixUniformLocation = this->getUniformLocation("cameraMatrix");
}

void Shader::Activate()
{
    glUseProgram(this->shaderProgram);
}

void Shader::Delete()
{
    glDeleteProgram(this->shaderProgram);
}

void Shader::SetCameraUniform(glm::mat4& cameraMatrix)
{
    glUniformMatrix4fv(this->cameraMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Shader::SetUniform1i(const char* uniformName, const int value)
{
    glUniform1i(glGetUniformLocation(this->shaderProgram, uniformName), value);
}

GLuint Shader::loadShader(const char* filePath, GLenum shaderType)
{
    std::string fileContents = getFileContents(filePath);
    const char* shaderCode = fileContents.c_str();
    const GLuint shaderID = glCreateShader(shaderType);

    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);

    GLint isSuccess;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);

    if (!isSuccess)
    {
        GLint logLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> logMessage(logLength);
        glGetShaderInfoLog(shaderID, logLength, &logLength, logMessage.data());

        std::cout << logMessage.data() << std::endl;
        return 0;
    }

    return shaderID;
}

GLint Shader::getUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(this->shaderProgram, uniformName);
}
