#include "Engine.h"

#ifdef _DEBUG
void OpenGLErrorCallback(int error, const char* description)
{
    std::cerr << "OpenGL Error: " << error << "(" << description << ")" << std::endl;
}

void OpenGLWindowCloseCallback(GLFWwindow* window)
{
    glfwSetWindowShouldClose(window, 1);

    std::cout << "Press Enter to exit..." << std::endl;
}
#endif

Engine::Engine(int windowWidth, int windowHeight, bool isFullscrean)
{
    Engine::Instance = this;

    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;
    this->_isFullscrean = isFullscrean;

    this->_windowCenterX = this->_windowWidth / 2.0;
    this->_windowCenterY = this->_windowHeight / 2.0;

    this->CreateGLWindow();
    this->InitInputEvents();
}

Engine::~Engine()
{
    glfwDestroyWindow(this->_window);
    //delete this->_camera;
    delete this->_player;
}

void Engine::CreateGLWindow()
{
    glfwSetErrorCallback(OpenGLErrorCallback);

    glfwInit();

    // 設定OpenGL版本，這邊指定OpenGL3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->_openGLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->_openGLVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = NULL;

    if (this->_isFullscrean)
    {
        monitor = glfwGetPrimaryMonitor();

        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    }

    this->_window = glfwCreateWindow(this->_windowWidth, this->_windowHeight, "Bhop Like CS", monitor, NULL);

#ifdef _DEBUG
    // 設定視窗關閉時的Callback
    glfwSetWindowCloseCallback(this->_window, OpenGLWindowCloseCallback);
#endif

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

void Engine::InitInputEvents()
{
    glfwSetKeyCallback(this->_window, Engine::_OnKeyEvent);
    glfwSetCursorPosCallback(this->_window, Engine::_OnCursorEvent);
}

void Engine::Run()
{
    // 坐標系與CS會不一樣
    // CS的坐標系中，Z軸才是高度
    // 但在這裡面為了開發方便，所以會以Y軸為高度

    GLfloat vertices[] =
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

    glEnable(GL_DEPTH_TEST);

    this->_player = new Player((float) this->_windowWidth / (float) this->_windowHeight);

    while (!glfwWindowShouldClose(this->_window))
    {
        // 先行做事件偵測，後再繪製
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->_player->UpdateKeyInput(this->_window);
        glm::mat4 matrix = this->_player->GetProjectionViewMatrix();

        shader.Use();
        shader.SetTemp(glm::value_ptr(matrix));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(this->_window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Engine::Render()
{
    
}

// ===================================== Private Static =====================================

Engine* Engine::Instance = nullptr;

void Engine::_OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Engine::Instance->_onKeyEvent(window, key, scancode, action, mods);
}

void Engine::_OnCursorEvent(GLFWwindow* window, double xPos, double yPos)
{
    Engine::Instance->_onCursorEvent(window, xPos, yPos);
}

// ===================================== Private =====================================

void Engine::_onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
}

void Engine::_onCursorEvent(GLFWwindow* window, double xPos, double yPos)
{
    // 暫時測試用
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        this->_flag = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        this->_flag = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (this->_flag)
    {
        double dx = this->_windowCenterX - xPos;
        double dy = this->_windowCenterY - yPos;

        // 玩家輸入
        this->_player->UpdateMouseInput(dx, dy);
        glfwSetCursorPos(window, this->_windowCenterX, this->_windowCenterY);
    }
}
