#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "fileutil.h"
#include "errorHandler.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "renderer.h"
#include "textures.h"
#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Match the framerate of monitor */
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
         0.0f,  0.0f, 0.0f, 0.0f, // 0
         200.0f,  0.0f, 1.0f, 0.0f, // 1
         200.0f,  200.0f, 1.0f, 1.0f, // 2
         0.0f,  200.0f, 0.0f, 1.0f  // 3
    };



    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    /* Enabling blending for png files */
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    /* Vertex array object */
    VertexArray va;

    /* Vertex buffer */
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    /* Layout for glVertexAttribPointer */
    VertexBufferLayout layout;

    /* Pushing 2 float as each vertex is represented by 2 floats x, y */
    layout.push<float>(2);
    layout.push<float>(2);

    /* Adding the vertex buffer and layout to vertex array */
    va.addBuffer(vb, layout);


    // index buffer
    IndexBuffer ib(indices, 6);

	/*ShaderSource source = getShaderSource("res/shader/basic.shader");

	unsigned int shader = getShader(source.vertexSrc, source.fragmentSrc);
	glUseProgram(shader);

	unsigned int uniform_location = glGetUniformLocation(shader, "u_color");*/


    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));


    Shader shader("res/shader/basic.shader");

	Texture texture("res\\textures\\meme.png");
	texture.bind();
    shader.setUniform1i("u_texture", 0);
    
    Renderer renderer;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    // some fancy animated color shifts
    float red = 0.0f, inc = 0.01f, x_translate = 0.0f, x_inc = -0.1f;
    glm::vec3 translation(0.0f, 0.0f, 0.0f);

    /* Unbinding everything */
    /*glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/

    test::Test* currentTest = nullptr;
    test::TestMenu* menu = new test::TestMenu(currentTest);
    currentTest = menu;

    menu->RegisterTest<test::TestClearColor>("Test Color");
    menu->RegisterTest<test::TestTexture2D>("Test Texture");
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.clear();


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            currentTest->onUpdate(0.0f);
            currentTest->onRender();
            ImGui::Begin("Test");
            if (currentTest != menu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = menu;
            }
            currentTest->ImGuiRender();
            ImGui::End();
        }

        shader.bind();


        
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 mvp = projection * view * model;
        shader.setUniformMat4f("u_MVP", mvp);
        
        //renderer.draw(va, ib, shader);

        /*if (x_translate > 0.5f)
            x_inc = -0.1f;
        else if (x_translate < -0.5f)
            x_inc = 0.1f;

        x_translate += x_inc;*/

        if (red > 1.0f)
            inc = -0.01f;
        else if (red < 0.0f)
            inc = 0.01f;

        red += inc;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    /*glDeleteProgram(shader);*/

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}