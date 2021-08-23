#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "fileutil.h"
#include "errorHandler.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "renderer.h"
#include "textures.h"

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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f  // 3
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


    glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    Shader shader("res/shader/basic.shader");

	Texture texture("res\\textures\\meme.png");
	texture.bind();
    shader.setUniform1i("u_texture", 0);
    shader.setUniformMat4f("u_MVP", projection);
    
    Renderer renderer;

    // some fancy animated color shifts
    float red = 0.0f, inc = 0.01f;

    /* Unbinding everything */
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();

        /*
            Instead of glDrawArrays we use glDrawELements
            params:
                mode: GL_TRIANGLES
                count: number of indices
                type: data type of indices, it has to be GL_UNSIGNED_INT
                indexBuffer: nullptr as we have already binded the buffer to GL_ELEMENT_ARRAY_BUFFER target
        */

        // An openGL error that got handled
        //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));

        /* Binding Shader program and just VAO as vao stores vb and ibo */
	   /* glUseProgram(shader);
		glUniform4f(uniform_location, red, 0.5f, 0.5f, 0.5f);*/
        shader.bind();
        //shader.setUniform4f("u_color", red, 0.5f, 0.5f, 0.5f);
        
        renderer.draw(va, ib, shader);

        if (red > 1.0f)
            inc = -0.01f;
        else if (red < 0.0f)
            inc = 0.01f;

        red += inc;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    /*glDeleteProgram(shader);*/
    glfwTerminate();
    return 0;
}