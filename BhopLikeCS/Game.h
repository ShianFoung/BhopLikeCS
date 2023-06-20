#pragma once

#include "Map/Map.h"
#include "Player.h"
#include "Physics.h"

#include "Graphics/Rendering/Shader.h"
#include "Graphics/Memory/VertexArray.h"
#include "Graphics/Memory/VertexBuffer.h"
#include "Graphics/Memory/ElementBuffer.h"

class Game
{
public:
    Game(const char* title, const int windowWidth, const int windowHeight, bool fullscreen = false);
    ~Game();

    void Run(int tickrate);
private:
    const char* title;
    int windowWidth;
    int windowHeight;
    bool fullscreen;

    GLFWwindow* window;

    void createOpenGLWindow();
};
