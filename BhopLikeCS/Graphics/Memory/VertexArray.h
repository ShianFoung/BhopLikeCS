#pragma once

class VertexArray
{
public:
    VertexArray();

    void AddAttribute(GLuint attributeIndex, GLuint dataCount, GLenum type, GLboolean normalized, GLuint offset);
    void BindToBuffers(VertexBuffer vbo, ElementBuffer ebo);

    void Delete();
private:
    GLuint id;
};

