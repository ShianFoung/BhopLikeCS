#pragma once

#include "../Data/Vertex.h"

class VertexBuffer
{
public:
    VertexBuffer(std::vector<Vertex>& vertices);
    VertexBuffer(GLsizei size);

    void BindToVAO(GLuint vaoID);
    void UpdateData(GLintptr offset, GLsizeiptr size, const void* data);

    void Delete();
private:
    GLuint id;
    GLsizei size;
};
