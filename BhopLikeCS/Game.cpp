#include "Game.h"

Game::Game(int windowWidth, int windowHeight, bool isFullScrean)
{
    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;
    this->_isFullScrean = isFullScrean;

    this->_createGLWindow();
}

Game::~Game()
{
    this->_window = nullptr;
    delete this->_player;
    this->_player = nullptr;
}

void Game::Run(int tickrate)
{
    this->_player = new Player(75.0f, this->_windowWidth, this->_windowHeight);

    /*GLfloat vertices[] =
    {
        -0.5f, 0.0f,  0.5f,
        -0.5f, 0.0f, -0.5f,
         0.5f, 0.0f, -0.5f,
         0.5f, 0.0f,  0.5f,
         0.0f, 0.8f,  0.0f,
    };

    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };*/

    GLfloat vertices[] =
    {
        -100.0f,  100.0f, 0.0f,
        -100.0f, -100.0f, 0.0f,
         200.0f, -100.0f, 0.0f,
         200.0f,  100.0f, 0.0f
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

    glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // 開啟深度測試，這樣才能讓物體有遠近之分
    // 不然最後畫的東西會在畫面最前面
    glEnable(GL_DEPTH_TEST);

    double tickPerSeconds = 1.0 / tickrate;
    double currentTime;
    double lastTime = glfwGetTime();
    float deltaTime;

    while (!glfwWindowShouldClose(this->_window))
    {
        // 限制 fps 與 tickrate 的地方
        currentTime = glfwGetTime();
        deltaTime = static_cast<float>(currentTime - lastTime);

        if (deltaTime < tickPerSeconds)
            continue;

        lastTime = currentTime;

        // 先行做事件偵測，後再繪製
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->_player->Temp(this->_window);
        this->_player->HandleInputs(this->_window);

        glm::mat4 viewProjectionMatrix = this->_player->GetCamera().GetProjectionMatrix();

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

// ===================================== Private =====================================

void Game::_createGLWindow()
{
    glfwSetErrorCallback(Game::_StaticOpenGLErrorCallback);

    // 初始化 GLFW
    glfwInit();

    // 設定OpenGL版本，這邊指定OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 關閉調整視窗的功能
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    this->_window = glfwCreateWindow(this->_windowWidth, this->_windowHeight, "Bhop Like CS", this->_isFullScrean ? monitor : NULL, NULL);

    if (!this->_window)
    {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
    }

    // 如果不是全螢幕就設定視窗為置中
    if (!this->_isFullScrean)
    {
        const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
        int initWindowXPos = (vidMode->width - this->_windowWidth) / 2;
        int initWindowYPos = (vidMode->height - this->_windowHeight) / 2;

        glfwSetWindowPos(this->_window, initWindowXPos, initWindowYPos);
    }

    // 將視窗的執行緒設定成當前執行緒
    glfwMakeContextCurrent(this->_window);

    // 關閉垂直同步 (不然輸入延遲會很高)
    glfwSwapInterval(0);

    // 如果有支援滑鼠原始輸入，就開啟
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    // 初始化 GLEW
    glewExperimental = GL_TRUE;
    glewInit();
}

void Game::_render()
{

}
