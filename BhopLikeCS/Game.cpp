#include "Game.h"

Game* Game::Instance = nullptr;

Game::Game(int windowWidth, int windowHeight, bool isFullScrean)
{
    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;
    this->_isFullScrean = isFullScrean;
    this->_aspectRatio = (float) this->_windowWidth / this->_windowHeight;
    this->_windowCenterX = this->_windowWidth / 2;
    this->_windowCenterY = this->_windowHeight / 2;

    this->_createGLWindow();
    this->_initInputEvents();
}

Game::~Game()
{
    Game::Instance = nullptr;
    this->_window = nullptr;
}

void Game::Run()
{
    while (!glfwWindowShouldClose(this->_window))
    {
        // 先行做事件偵測，後再繪製
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO

        glfwSwapBuffers(this->_window);
    }

    glfwDestroyWindow(this->_window);
}

void Game::Destory()
{

}

// ===================================== Private Static =====================================

void Game::_StaticOpenGLErrorCallback(int error, const char* description)
{
    std::cerr << "OpenGL Error: " << error << "(" << description << ")" << std::endl;
}

void Game::_StaticOnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Game::Instance->_onKeyEvent(window, key, action);
}

void Game::_StaticOnCursorEvent(GLFWwindow* window, double xPos, double yPos)
{
    Game::Instance->_onCursorEvent(window, xPos, yPos);
}

// ===================================== Private =====================================

void Game::_createGLWindow()
{
    glfwSetErrorCallback(Game::_StaticOpenGLErrorCallback);

    glfwInit();

    // 設定OpenGL版本，這邊指定OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = nullptr;

    if (this->_isFullScrean)
    {
        monitor = glfwGetPrimaryMonitor();

        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    }

    this->_window = glfwCreateWindow(this->_windowWidth, this->_windowHeight, "Bhop Like CS", monitor, NULL);

    if (!this->_window)
    {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(this->_window);

    // 如果有支援滑鼠原始輸入，就開啟
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glewExperimental = GL_TRUE;
    glewInit();
}

void Game::_initInputEvents()
{
    glfwSetKeyCallback(this->_window, Game::_StaticOnKeyEvent);
    glfwSetCursorPosCallback(this->_window, Game::_StaticOnCursorEvent);
}

void Game::_onKeyEvent(GLFWwindow* window, int key, int action)
{

}

void Game::_onCursorEvent(GLFWwindow* window, float xPos, float yPos)
{

}
