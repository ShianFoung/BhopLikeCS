#pragma once

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

    void init();
    void createOpenGLWindow();

private:
    static void staticOpenGLErrorCallback(int error, const char* description);
};
