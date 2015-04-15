#include "application.h"

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLFWwindow *Application::window;
Program Application::program;
Scene Application::scene;
Camera *Application::camera;

void Application::start()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Use OpenGL Core v3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,  GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Chess3D", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
#ifndef __APPLE__
    glewInit();
#endif

    std::cout << "OpenGL version supported by this platform: " << glGetString(GL_VERSION) << std::endl;
    
    initOpenGL();
    
    
    /* TEST CAMERA
    camera = new Camera(640, 480);
    glfwSetMousePos(midWindowX, midWindowY);
    glfwSetMousePosCallback(window, mousepos_callback);
    */
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    
    
    while (!glfwWindowShouldClose(window))
    {
        display();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    
}

void Application::initOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    
    program.init();
    
    scene.initScene();
    
    program.use();
    
    scene.setPerspective(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(program.getId(), "projection_matrix"), 1, GL_FALSE, scene.getProjectionMatrixArray());

    glm::mat4 view_matrix(1.f);
    view_matrix = glm::lookAt(glm::vec3(2.f, 1.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    glUniformMatrix4fv(glGetUniformLocation(program.getId(), "view_matrix"), 1, GL_FALSE, glm::value_ptr(view_matrix));
    
}

void Application::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    program.use();
    
    /* render each VAO*/
    for (int i = 0; i < scene.size(); ++i)
    {
        const Vao &vao = scene[i];
        
        glUniformMatrix4fv(glGetUniformLocation(program.getId(), "model_matrix"), 1, GL_FALSE, vao.getModelMatrixArray());
        glBindVertexArray(vao.getId());
        glDrawArrays(GL_TRIANGLES, 0, vao.getVertexCount());
    }
    
    glBindVertexArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::window_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    scene.setPerspective(width, height);
    program.use();
    glUniformMatrix4fv(glGetUniformLocation(program.getId(), "projection_matrix"), 1, GL_FALSE, scene.getProjectionMatrixArray());
}

void Application::error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // CAMERA CONTROL
    if (action == GLFW_PRESS) {
        switch(key) {
        case 'Z':
            camera->holdingForward = true;
            break;
        case 'S':
            camera->holdingBackward = true;
            break;
        case 'Q':
            camera->holdingLeftStrafe = true;
            break;
        case 'D':
            camera->holdingRightStrafe = true;
            break;
        default:
            break;
        }
    } else {
        switch(key) {
        case 'Z':
            camera->holdingForward = false;
            break;
        case 'S':
            camera->holdingBackward = false;
            break;
        case 'Q':
            camera->holdingLeftStrafe = false;
            break;
        case 'D':
            camera->holdingRightStrafe = false;
            break;
        default:
            break;
        }
    }
}

void Application::mousepos_callback(int mouseX, int mouseY) {
    // CAMERA CONTROL
    camera->handleMouseMove(mouseX, mouseY);
}
