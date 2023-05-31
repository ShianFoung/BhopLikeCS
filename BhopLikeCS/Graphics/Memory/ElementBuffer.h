#pragma once

class ElementBuffer
{
public:
    ElementBuffer(std::vector<GLuint>& indices);

    void BindToVAO(GLuint vaoID);

    void Delete();
private:
    GLuint id;
};

