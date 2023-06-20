#pragma once

#include "../Data/Vertex.h"

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(std::vector<Vertex>& vertices);
    VertexBuffer(std::vector<float>& vertices);
    VertexBuffer(std::vector<float>& vertices, GLsizei sizePerVertex);
    VertexBuffer(const float* vertices, int count);
    VertexBuffer(const float* vertices, int count, GLsizei sizePerVertex);
    VertexBuffer(GLsizei totalSize);

    void BindToVAO(GLuint vaoID);
    void UpdateData(GLintptr offset, GLsizeiptr size, const void* data);

    void Delete();
private:
    GLuint id;
    GLsizei sizePerVertex;
};
