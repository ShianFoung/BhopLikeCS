#include "Game.h"

Game::Game(const char* title, const int windowWidth, const int windowHeight, bool isFullScrean)
{
    this->_title = title;
    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;
    this->_isFullScrean = isFullScrean;

    this->_createGLWindow();
}

Game::~Game()
{
    this->_window = nullptr;
}

void Game::Run(int tickrate)
{
    Player player = Player(90.0f, this->_windowWidth, this->_windowHeight);
    Physics physics = Physics(&player);

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
         1000.0f, -100.0f, 0.0f,
         1000.0f,  100.0f, 0.0f
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

    //glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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

#ifdef _BENCHMARK
        double processStartTime = glfwGetTime();
#endif

        // 先行做事件偵測，後再繪製
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 處理順序:
        // 1. 獲取 player 的滑鼠與鍵盤輸入
        // 2. physics 做物理計算 (碰撞、加速度等等)
        // 3. 將 physics 做完的計算再傳給 player 做最後的更新 (位置等等)
        player.HandleInputs(this->_window, deltaTime);
        physics.Update(deltaTime);
        player.Update();

        glm::mat4 viewProjectionMatrix = player.GetCamera().GetProjectionMatrix();

        // TODO
        shader.Use();
        shader.SetCameraUniform(glm::value_ptr(viewProjectionMatrix));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(this->_window);

#ifdef _BENCHMARK
        double processTime = glfwGetTime() - processStartTime;
        std::cout << processTime << '\r';
#endif
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
    const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
    const int primaryMonitorWidth = vidMode->width;
    const int primaryMonitorHeight = vidMode->height;

    if (this->_isFullScrean)
    {
        this->_window = glfwCreateWindow(primaryMonitorWidth, primaryMonitorHeight, this->_title, monitor, NULL);
        this->_windowWidth = primaryMonitorWidth;
        this->_windowHeight = primaryMonitorHeight;
    }
    else
        this->_window = glfwCreateWindow(this->_windowWidth, this->_windowHeight, this->_title, NULL, NULL);

    if (!this->_window)
    {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
    }

    // 如果不是全螢幕就設定視窗為置中
    if (!this->_isFullScrean)
    {
        int initWindowXPos = (primaryMonitorWidth - this->_windowWidth) / 2;
        int initWindowYPos = (primaryMonitorHeight - this->_windowHeight) / 2;

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
