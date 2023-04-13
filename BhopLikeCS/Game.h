#pragma once

#include "GLHeader.h"

#include <glm/glm.hpp>

#include <iostream>

class Game
{
public:
    static Game* Instance;

    Game(int windowWidth, int windowHeight, bool isFullScrean = false);
    ~Game();

    void Run();
    void Destory();
private:
    int _windowWidth;
    int _windowHeight;
    bool _isFullScrean;
    float _aspectRatio;
    int _windowCenterX;
    int _windowCenterY;

    GLFWwindow* _window;

    static void _StaticOpenGLErrorCallback(int error, const char* description);
    static void _StaticOnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void _StaticOnCursorEvent(GLFWwindow* window, double xPos, double yPos);

    void _createGLWindow();
    void _initInputEvents();
    void _onKeyEvent(GLFWwindow* window, int key, int action);
    void _onCursorEvent(GLFWwindow* window, float xPos, float yPos);
};