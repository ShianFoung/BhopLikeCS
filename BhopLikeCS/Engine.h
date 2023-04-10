#pragma once

#include "Player.h"
#include "Shader.h"

#include "GLHeader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Engine
{
public:
    static Engine* Instance;

    Engine(int windowWidth, int windowHeight, bool isFullscrean = false);
    ~Engine();

    const int GetWindowWidth() { return this->_windowWidth; }
    const int GetWindowHeight() { return this->_windowHeight; }

    void CreateGLWindow();
    void InitInputEvents();

    void Run();
    void Render();
private:
    const int _openGLVersionMajor = 3;
    const int _openGLVersionMinor = 3;

    int _windowWidth;
    int _windowHeight;
    bool _isFullscrean;

    GLFWwindow* _window;
    Player* _player;
    bool _flag = false;

    double _windowCenterX;
    double _windowCenterY;

    static void _OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void _OnCursorEvent(GLFWwindow* window, double xPos, double yPos);

    void _onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    void _onCursorEvent(GLFWwindow* window, double xPos, double yPos);
};
