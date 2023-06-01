#pragma once

class ElementBuffer
{
public:
    ElementBuffer(std::vector<int>& indices);
    ElementBuffer(const int* indices, int count);

    void BindToVAO(GLuint vaoID);

    void Delete();
private:
    GLuint id;
};

