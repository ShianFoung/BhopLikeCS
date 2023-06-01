#pragma once

#include "VertexBuffer.h"
#include "ElementBuffer.h"

class VertexArray
{
public:
    VertexArray();

    void AddAttribute(GLuint attributeIndex, GLuint dataCount, GLenum type, GLboolean normalized, GLuint offset);
    void BindBuffer(VertexBuffer& vbo);
    void BindBuffers(VertexBuffer& vbo, ElementBuffer& ebo);

    void Bind();
    void Unbind();
    void Delete();
private:
    GLuint id;
};

