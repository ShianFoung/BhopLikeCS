#pragma once

#include "../Data/Vertex.h"

class VertexBuffer
{
public:
    VertexBuffer(std::vector<Vertex>& vertices);
    VertexBuffer(std::vector<float>& vertices);
    VertexBuffer(const float* vertices, int count, int sizePerData);
    VertexBuffer(GLsizei size);

    void BindToVAO(GLuint vaoID);
    void UpdateData(GLintptr offset, GLsizeiptr size, const void* data);

    void Delete();
private:
    GLuint id;
    GLsizei sizePerData;
};
