#pragma once

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;

    Vertex() = default;

    Vertex(const glm::vec3& position, const glm::vec3& color)
        : position(position), color(color) {  }
};

class Mesh
{
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices);

    void Draw();

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    std::vector<Vertex> vertices;
    std::vector<int> indices;

    void createVAO();
    void createVBO();
    void createEBO();
    void bindObjects();
};

