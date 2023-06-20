#pragma once

class Texture
{
public:
    Texture(const std::string& imagePath);

    void Activate(GLuint unit);
    void Delete();
private:
    GLuint id;
};
