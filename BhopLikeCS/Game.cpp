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

    // �}�Ҳ`�״��աA�o�ˤ~�������馳���񤧤�
    // ���M�̫�e���F��|�b�e���̫e��
    glEnable(GL_DEPTH_TEST);

    Player player(90.0f, g_WindowWidth, g_WindowHeight);
    Physics physics(&player);

    double tickPerSeconds = 1.0 / tickrate;
    double currentTime;
    double lastTime = glfwGetTime();
    float deltaTime;

    while (!glfwWindowShouldClose(this->window))
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

    if (this->fullscreen)
    {
        this->window = glfwCreateWindow(primaryMonitorWidth, primaryMonitorHeight, this->title, monitor, NULL);
        this->windowWidth = primaryMonitorWidth;
        this->windowHeight = primaryMonitorHeight;
    }
    else
        this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, this->title, NULL, NULL);

    // �����إߥ��ѡA�����h�X
    if (this->window == nullptr)
    {
        std::cerr << "Failed to create window." << std::endl;
        glfwTerminate();
        return;
    }

    // �p�G���O���ù��N�]�w�������m��
    if (!this->fullscreen)
    {
        int initWindowXPos = (primaryMonitorWidth - this->windowWidth) / 2;
        int initWindowYPos = (primaryMonitorHeight - this->windowHeight) / 2;

        glfwSetWindowPos(this->window, initWindowXPos, initWindowYPos);
    }

    // �N������������]�w����e�����
    glfwMakeContextCurrent(this->window);

    // ���������P�B (���M��J����|�ܰ�)
    glfwSwapInterval(0);

    // �p�G���䴩�ƹ���l��J�A�N�}��
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    // ��l�� GLEW
    glewExperimental = GL_TRUE;
    glewInit();
}

void Game::staticOpenGLErrorCallback(int error, const char* description)
{
    std::cerr << "OpenGL Error: " << error << "(" << description << ")" << std::endl;
}
