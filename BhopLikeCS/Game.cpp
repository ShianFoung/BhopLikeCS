#include "Header.h"

#include "Game.h"
#include "Player.h"
#include "Physics.h"
#include "Shader.h"

Game::Game(const char* title, const int windowWidth, const int windowHeight, bool fullscreen)
{
    this->title = title;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->fullscreen = fullscreen;

    this->createOpenGLWindow();
}

Game::~Game()
{
    this->window = nullptr;
}

void Game::Run(int tickrate)
{
    if (this->window == nullptr)
        return;

    float vertices[] =
    {
        -100.0f,   100.0f, 0.0f,
        -100.0f,  -100.0f, 0.0f,
         1000.0f, -100.0f, 0.0f,
         1000.0f,  100.0f, 0.0f
    };

    int indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    GLuint vao, vbo, ebo;

    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ebo);

    glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glNamedBufferData(ebo, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));
    glVertexArrayElementBuffer(vao, ebo);

    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    Shader shader = Shader("default");

    // 開啟深度測試，這樣才能讓物體有遠近之分
    // 不然最後畫的東西會在畫面最前面
    glEnable(GL_DEPTH_TEST);

    Player player(90.0f, g_WindowWidth, g_WindowHeight);
    Physics physics(&player);

    double tickPerSeconds = 1.0 / tickrate;
    double currentTime;
    double lastTime = glfwGetTime();
    float deltaTime;

    while (!glfwWindowShouldClose(this->window))
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
        player.HandleInputs(this->window, deltaTime);
        physics.Update(deltaTime);
        player.Update();

        glm::mat4 viewProjectionMatrix = player.GetCamera().GetProjectionMatrix();

        // TODO
        shader.Use();
        //shader.SetCameraUniform(glm::value_ptr(viewProjectionMatrix));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(this->window);

#ifdef _BENCHMARK
        std::cout << glfwGetTime() - processStartTime << '\r';
#endif
    }

    glfwDestroyWindow(this->window);

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Game::init()
{

}

void Game::createOpenGLWindow()
{
    // Handle GLFW Errors
    glfwSetErrorCallback(Game::staticOpenGLErrorCallback);

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

    if (this->fullscreen)
    {
        this->window = glfwCreateWindow(primaryMonitorWidth, primaryMonitorHeight, this->title, monitor, NULL);
        this->windowWidth = primaryMonitorWidth;
        this->windowHeight = primaryMonitorHeight;
    }
    else
        this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, this->title, NULL, NULL);

    // 視窗建立失敗，直接退出
    if (this->window == nullptr)
    {
        std::cerr << "Failed to create window." << std::endl;
        glfwTerminate();
        return;
    }

    // 如果不是全螢幕就設定視窗為置中
    if (!this->fullscreen)
    {
        int initWindowXPos = (primaryMonitorWidth - this->windowWidth) / 2;
        int initWindowYPos = (primaryMonitorHeight - this->windowHeight) / 2;

        glfwSetWindowPos(this->window, initWindowXPos, initWindowYPos);
    }

    // 將視窗的執行緒設定成當前執行緒
    glfwMakeContextCurrent(this->window);

    // 關閉垂直同步 (不然輸入延遲會很高)
    glfwSwapInterval(0);

    // 如果有支援滑鼠原始輸入，就開啟
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    // 初始化 GLEW
    glewExperimental = GL_TRUE;
    glewInit();
}

void Game::staticOpenGLErrorCallback(int error, const char* description)
{
    std::cerr << "OpenGL Error: " << error << "(" << description << ")" << std::endl;
}
