#pragma once

#include "Header.h"

#include "Camera.h"
#include "Player.h"
#include "Physics.h"
#include "Shader.h"

class Game
{
public:
    Game(const char* title, const int windowWidth, const int windowHeight, bool isFullScrean = false);
    ~Game();

    void Run(int tickrate);
private:
    const char* _title;
    int _windowWidth;
    int _windowHeight;
    bool _isFullScrean;

    GLFWwindow* _window;

    static void _StaticOpenGLErrorCallback(int error, const char* description);

    void _createGLWindow();
    void _render();
};