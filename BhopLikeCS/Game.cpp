#include "../Header.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Game.h"

Game* game = nullptr;

void openGLErrorCallback(int error, const char* description)
{
    std::cout << "OpenGL Error: " << error << "(" << description << ")\n";
}

Game::Game(const char* title, const int windowWidth, const int windowHeight, bool fullscreen)
{
    game = this;

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    io.FontGlobalScale = 2.0f;

    Map map(Config::gameSettings.map);

    std::vector<BoundingBox> boundingBox;
    std::vector<std::vector<Vertex>> orderedVertices;
    std::vector<Texture> textures;
    std::vector<VertexBuffer> vbos;

    map.Generate(boundingBox, orderedVertices, textures, vbos); 

    VertexArray vao;
    vao.AddAttribute(0, 3, GL_FLOAT, 0);
    vao.AddAttribute(1, 3, GL_FLOAT, 3 * sizeof(float));
    vao.AddAttribute(2, 3, GL_FLOAT, 6 * sizeof(float));
    vao.Bind();

    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader colorShader = Shader("defaultColor");
    Shader defaultShader = Shader("default");

    defaultShader.SetUniform1i("textureImage", 0);

    // �}�Ҳ`�״��աA�o�ˤ~�������馳���񤧤�
    // ���M�̫�e���F��|�b�e���̫e��
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    Player player(90.0f, Config::windowSettings.width, Config::windowSettings.height);
    Physics physics(player, boundingBox);

    double tickPerSeconds = 1.0 / tickrate;
    double currentTime;
    double lastTime = glfwGetTime();
    float frameTime;

    while (!glfwWindowShouldClose(this->window))
    {
        // ���� fps �P tickrate ���a��
        currentTime = glfwGetTime();
        frameTime = static_cast<float>(currentTime - lastTime);

        if (frameTime < tickPerSeconds)
            continue;

        lastTime = currentTime;

#ifdef _BENCHMARK
        double processStartTime = glfwGetTime();
#endif
        // ���氵�ƥ󰻴��A��Aø�s
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // �B�z����:
        // 1. ��� player ���ƹ��P��L��J
        // 2. physics �����z�p�� (�I���B�[�t�׵���)
        // 3. �N physics �������p��A�ǵ� player ���̫᪺��s (��m����)
        player.HandleInputs(this->window, frameTime);
        physics.Update(frameTime);
        player.Update(frameTime);

        glm::mat4 cameraMatrix = player.GetCamera().GetProjectionMatrix();

        glEnable(GL_DEPTH_TEST);
        colorShader.Activate();
        colorShader.SetCameraUniform(cameraMatrix);
        defaultShader.Activate();
        defaultShader.SetCameraUniform(cameraMatrix);

        for (int i = 0; i < vbos.size(); i++)
        {
            if (i == 0)
                colorShader.Activate();
            else
            {
                defaultShader.Activate();

                textures[i - 1].Activate(0);
            }

            if (orderedVertices[i].size() == 0)
                continue;

            vao.BindBuffer(vbos[i]);
            glDrawArrays(GL_TRIANGLES, 0, orderedVertices[i].size());
        }

        ImGui::SetNextWindowSize(ImVec2(200, 100));
        ImGui::Begin("Speed", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text(std::to_string(static_cast<int>(utils::GetXYVectorLength(player.GetVelocity()))).c_str());
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(this->window);

#ifdef _BENCHMARK
        std::cout << glfwGetTime() - processStartTime << '\r';
#endif
    }

    glfwTerminate();

    vao.Delete();
    for (VertexBuffer& vbo : vbos)
        vbo.Delete();

    for (Texture& texture : textures)
        texture.Delete();
}

void Game::createOpenGLWindow()
{
    // Handle GLFW Errors
    glfwSetErrorCallback(openGLErrorCallback);

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
        std::cout << "Failed to create window." << std::endl;
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
