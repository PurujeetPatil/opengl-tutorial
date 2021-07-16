#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "fileutil.h"

static unsigned int compileShader(unsigned int type, const std::string& src)
{
    // Create a shader ID
    unsigned int id = glCreateShader(type);

    // openGL likes NULL terminated string and its pointer for some reason
    const char* s_src = src.c_str();

    // Pass the id for shader, number of shaders, reference to pointer to src of shader (wtf?) and length of shader(we are passing null, as null terminated) 
    glShaderSource(id, 1, &s_src, nullptr);

    // Compile the shader by the id
    glCompileShader(id);

    //-------------------Error Handling---------------------
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        // i specifies that we are giving an integer and v specifies it wants a vector
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        // Create a message buffer of that length
        char* message = (char*)_malloca(length * sizeof(char));

        // Pass the message buffer
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile shader! : " << (type == GL_VERTEX_SHADER ? "|Vertex|" : "|Fragment|");
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int getShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // Create a program to run on GPU
    unsigned int program = glCreateProgram();

    //------------------------Vertex Shader-------------------------

    // Create a shader ID
    unsigned int v_id = compileShader(GL_VERTEX_SHADER, vertexShader);

    //-----------------------Fragment Shader------------------------

    // Same shit below, expect for target that is GL_FRAGMENT_SHADER
    unsigned int f_id = compileShader(GL_FRAGMENT_SHADER, fragmentShader);


    // attach the shader to the program by id
    glAttachShader(program, v_id);
    glAttachShader(program, f_id);

    // link the two shader .obj(s) in the program
    glLinkProgram(program);

    // validate if successfully linked
    glValidateProgram(program);

    // delete the intermediates like .obj(s)
    glDeleteShader(v_id);
    glDeleteShader(f_id);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Vertex buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // index buffer
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);    

    ShaderSource source = getShaderSource("res/shader/basic.shader");

    unsigned int shader = getShader(source.vertexSrc, source.fragmentSrc);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*
            Instead of glDrawArrays we use glDrawELements
            params:
                mode: GL_TRIANGLES
                count: number of indices
                type: data type of indices, it has to be GL_UNSIGNED_INT
                indexBuffer: nullptr as we have already bind'ed the buffer to GL_ELEMENT_ARRAY_BUFFER targe
        */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}