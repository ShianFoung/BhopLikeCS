#pragma once

#include "GameHeader.h"

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

    void Run();
private:
    int _windowWidth;
    int _windowHeight;
    bool _isFullScrean;
    int _windowCenterX;
    int _windowCenterY;

    GLFWwindow* _window;
    Player* _player;

    static void _StaticOpenGLErrorCallback(int error, const char* description);
    static void _StaticOnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void _StaticOnCursorEvent(GLFWwindow* window, double xPos, double yPos);

    void _createGLWindow();
    void _initInputEvents();
    void _render();
    void _onKeyEvent(GLFWwindow* window, int key, int action);
    void _onCursorEvent(GLFWwindow* window, float xPos, float yPos);
};