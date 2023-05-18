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

    // �}�Ҳ`�״��աA�o�ˤ~�������馳���񤧤�
    // ���M�̫�e���F��|�b�e���̫e��
    glEnable(GL_DEPTH_TEST);

    double tickPerSeconds = 1.0 / tickrate;
    double currentTime;
    double lastTime = glfwGetTime();
    float deltaTime;

    while (!glfwWindowShouldClose(this->_window))
    {
        // ���� fps �P tickrate ���a��
        currentTime = glfwGetTime();
        deltaTime = static_cast<float>(currentTime - lastTime);

        if (deltaTime < tickPerSeconds)
            continue;

        lastTime = currentTime;

#ifdef _BENCHMARK
        double processStartTime = glfwGetTime();
#endif

        // ���氵�ƥ󰻴��A��Aø�s
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // �B�z����:
        // 1. ��� player ���ƹ��P��L��J
        // 2. physics �����z�p�� (�I���B�[�t�׵���)
        // 3. �N physics �������p��A�ǵ� player ���̫᪺��s (��m����)
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

    // ��l�� GLFW
    glfwInit();

    // �]�wOpenGL�����A�o����wOpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // �����վ�������\��
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

    // �p�G���O���ù��N�]�w�������m��
    if (!this->_isFullScrean)
    {
        int initWindowXPos = (primaryMonitorWidth - this->_windowWidth) / 2;
        int initWindowYPos = (primaryMonitorHeight - this->_windowHeight) / 2;

        glfwSetWindowPos(this->_window, initWindowXPos, initWindowYPos);
    }

    // �N������������]�w����e�����
    glfwMakeContextCurrent(this->_window);

    // ���������P�B (���M��J����|�ܰ�)
    glfwSwapInterval(0);

    // �p�G���䴩�ƹ���l��J�A�N�}��
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    // ��l�� GLEW
    glewExperimental = GL_TRUE;
    glewInit();
}

void Game::_render()
{

}
