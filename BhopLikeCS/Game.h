#pragma once

#include "GameHeader.h"

#include "Camera.h"
#include "Player.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Game
{
public:
    Game(int windowWidth, int windowHeight, bool isFullScrean = false);
    ~Game();

    void Run(int tickrate);
private:
    int _windowWidth;
    int _windowHeight;
    bool _isFullScrean;

    GLFWwindow* _window;
    Player* _player;

    static void _StaticOpenGLErrorCallback(int error, const char* description);

    void _createGLWindow();
    void _render();
};