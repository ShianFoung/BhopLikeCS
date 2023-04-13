#include "Shader.h"

Shader::Shader(const char* name)
{
    const std::string vertPath = "Shaders/" + std::string(name) + ".vert";
    const std::string fragPath = "Shaders/" + std::string(name) + ".frag";

    this->_vertID = this->_loadShader(vertPath.c_str(), GL_VERTEX_SHADER);
    this->_fragID = this->_loadShader(fragPath.c_str(), GL_FRAGMENT_SHADER);

    this->_programID = glCreateProgram();

    glAttachShader(this->_programID, this->_vertID);
    glAttachShader(this->_programID, this->_fragID);
    glLinkProgram(this->_programID);

    GLint isLinked;

    glGetProgramiv(this->_programID, GL_LINK_STATUS, &isLinked);

    if (!isLinked)
    {
        GLint logLength;

        glGetShaderiv(this->_programID, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> logMessage = std::vector<GLchar>(logLength);

        glGetShaderInfoLog(this->_programID, logLength, &logLength, logMessage.data());

        std::cerr << logMessage.data() << std::endl;

        this->_programID = 0;

        return;
    }

    this->_cameraMatrixLocation = glGetUniformLocation(this->_programID, "cameraMatrix");
}

Shader::~Shader()
{
    glDetachShader(this->_programID, this->_vertID);
    glDetachShader(this->_programID, this->_fragID);
    glDeleteProgram(this->_programID);
    glDeleteShader(this->_vertID);
    glDeleteShader(this->_fragID);
}

void Shader::Use()
{
    glUseProgram(this->_programID);
}

void Shader::SetCameraUniform(const float* value)
{
    glUniformMatrix4fv(this->_cameraMatrixLocation, 1, GL_FALSE, value);
}

GLuint Shader::_loadShader(const char* fileName, GLenum shaderType)
{
    // 先讀取 .vert 或 .frag 檔案的內容
    std::ifstream fileIn(fileName);
    std::stringstream buffer;

    buffer << fileIn.rdbuf();

    const std::string bufferString = buffer.str();
    const char* shaderSourceCode = bufferString.c_str();
    const GLuint shaderID = glCreateShader(shaderType);

    // 將讀取的程式碼進行編譯
    glShaderSource(shaderID, 1, &shaderSourceCode, 0);
    glCompileShader(shaderID);

    GLint isSuccess;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);

    if (!isSuccess)
    {
        GLint logLength;

        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> logMessage = std::vector<GLchar>(logLength);

        glGetShaderInfoLog(shaderID, logLength, &logLength, logMessage.data());

        std::cerr << logMessage.data() << std::endl;

        return 0;
    }

    return shaderID;
}
