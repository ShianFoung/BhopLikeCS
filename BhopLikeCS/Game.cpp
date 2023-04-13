#include "Game.h"

Game* g_GameInstance = nullptr;
float g_aspectRatio = 0.0f;

Game::Game(int windowWidth, int windowHeight, bool isFullScrean)
{
    g_GameInstance = this;

    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;
    this->_isFullScrean = isFullScrean;
    this->_windowCenterX = this->_windowWidth / 2;
    this->_windowCenterY = this->_windowHeight / 2;

    g_aspectRatio = (float) this->_windowWidth / this->_windowHeight;

    this->_createGLWindow();
    this->_initInputEvents();
}

Game::~Game()
{
    g_GameInstance = nullptr;
    this->_window = nullptr;
    delete this->_player;
    this->_player = nullptr;
}

void Game::Run()
{
    this->_player = new Player();

    //GLfloat vertices[] =
    //{
    //    -0.5f, 0.0f,  0.5f,
    //    -0.5f, 0.0f, -0.5f,
    //     0.5f, 0.0f, -0.5f,
    //     0.5f, 0.0f,  0.5f,
    //     0.0f, 0.8f,  0.0f,
    //};

    //GLuint indices[] =
    //{
    //    0, 1, 2,
    //    0, 2, 3,
    //    /*0, 1, 4,
    //    1, 2, 4,
    //    2, 3, 4,
    //    3, 0, 4*/
    //};

    GLfloat vertices[] =
    {
        -1000.0f, 0.0f,  1000.0f,
        -1000.0f, 0.0f, -1000.0f,
         1000.0f, 0.0f, -1000.0f,
         1000.0f, 0.0f,  1000.0f
    };

    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader shader = Shader("default");

    //glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(this->_window))
    {
        // 先行做事件偵測，後再繪製
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->_player->Temp(this->_window);

        glm::mat4 viewProjectionMatrix = this->_player->GetViewProjectionMatrix();

        // TODO
        shader.Use();
        shader.SetCameraUniform(glm::value_ptr(viewProjectionMatrix));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(this->_window);
    }

    glfwDestroyWindow(this->_window);
}

// ===================================== Private Static =====================================

void Game::_StaticOpenGLErrorCallback(int error, const char* description)
{
    std::cerr << "OpenGL Error: " << error << "(" << description << ")" << std::endl;
}

void Game::_StaticOnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    g_GameInstance->_onKeyEvent(window, key, action);
}

void Game::_StaticOnCursorEvent(GLFWwindow* window, double xPos, double yPos)
{
    g_GameInstance->_onCursorEvent(window, xPos, yPos);
}

// ===================================== Private =====================================

void Game::_createGLWindow()
{
    glfwSetErrorCallback(Game::_StaticOpenGLErrorCallback);

    glfwInit();

    // 設定OpenGL版本，這邊指定OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

void Game::_render()
{

}

void Game::_onKeyEvent(GLFWwindow* window, int key, int action)
{
    //this->_player->UpdateKeyInput(key, action);
    //this->_player->Temp(window);
}

void Game::_onCursorEvent(GLFWwindow* window, float xPos, float yPos)
{
    float dx = xPos - this->_windowCenterX;
    float dy = this->_windowCenterY - yPos;

    //this->_player->MouseInput(dx, dy);
    //glfwSetCursorPos(window, this->_windowCenterX, this->_windowCenterY);
}
