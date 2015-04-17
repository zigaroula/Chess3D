#include "application.h"

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define TAILLE_SHADOW_MAP 1024

GLFWwindow *Application::window;
Program Application::program;
Program Application::programSM;
Scene Application::scene;
double Application::lastTime;
int Application::nbFrames;
int Application::nbFramesLastSecond;

static bool ombres;

void Application::start()
{
    ombres = false;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    std::cout << "OpenGL version supported by this platform: " << glGetString(GL_VERSION) << std::endl;

    initOpenGL();

    glfwSwapInterval(0);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    lastTime = glfwGetTime();
    nbFrames = 0;
    nbFramesLastSecond = 7000;

    while (!glfwWindowShouldClose(window))
    {

        display();

        /* computing fps */
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0)
        {
            nbFramesLastSecond = nbFrames;
            setTitleFps();
            nbFrames = 0;
            lastTime += 1.0;
        }
        scene.move(nbFramesLastSecond);
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

    programSM.initForShadowMap();
    program.init();

    scene.initScene(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    program.use();

    scene.setPerspective(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(program.getId(), "projection_matrix"), 1, GL_FALSE, scene.getProjectionMatrixArray());
    
    
}

void Application::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(ombres){
        //###############OMBRE PORTEE PASSE 1###############################"

        programSM.use();


        glBindFramebuffer(GL_FRAMEBUFFER, scene.getShadowBufferId());



        // On vérifie que le tampon d'image est OK ... ?
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cerr << "Probleme avec le tampon d'image" << std::endl;

        glm::vec3 lightInvDir = scene.getLight(0).getPos();

        // On calcule la matrice Model-Vue-Projection du point de vue de la lumière
        glm::mat4 depthProjectionMatrix = scene.getProjectionMatrix();
        glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
        for (unsigned int i = 0; i < scene.size(); ++i)
        {
            const Vao &vao = scene[i];

            glm::mat4 depthModelMatrix =  vao.getModelMatrix();
            glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
            // On envoie la matrix au shader lié (MVP_matrix)
            glUniformMatrix4fv(glGetUniformLocation(programSM.getId(), "MVP_matrix"), 1, GL_FALSE, &depthMVP[0][0]);

            glBindVertexArray(vao.getId());

            glDrawArrays(GL_TRIANGLES, 0, vao.getVertexCount());
        }
        
        //glDrawBuffer(depthTexture);




    }

    program.use();

    /* render each VAO*/
    
    
    for (unsigned int i = 0; i < scene.size(); ++i)
    {
        const Vao &vao = scene[i];

        glUniformMatrix4fv(glGetUniformLocation(program.getId(), "normal_matrix"), 1, GL_FALSE, scene.getNormalMatrixArray(i));

        glUniformMatrix4fv(glGetUniformLocation(program.getId(), "model_matrix"), 1, GL_FALSE, vao.getModelMatrixArray());
        glBindVertexArray(vao.getId());
        glDrawArrays(GL_TRIANGLES, 0, vao.getVertexCount());
    }

    glBindVertexArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();

    // CAMERA VIEW
    scene.setView();
    glUniformMatrix4fv(glGetUniformLocation(program.getId(), "view_matrix"), 1, GL_FALSE, scene.getViewMatrixArray());



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
        case 'W':
            scene.setCamFW(true);
            break;
        case 'S':
            scene.setCamBW(true);
            break;
        case 'A':
            scene.setCamLS(true);
            break;
        case 'D':
            scene.setCamRS(true);
            break;
        case 'Q':
            scene.setCamZP(true);
            break;
        case 'E':
            scene.setCamZN(true);
            break;
        case 'I':
            ombres = true;
            break;
        default:
            break;
        }
    } else if (action == GLFW_RELEASE) {
        switch(key) {
        case 'W':
            scene.setCamFW(false);
            break;
        case 'S':
            scene.setCamBW(false);
            break;
        case 'A':
            scene.setCamLS(false);
            break;
        case 'D':
            scene.setCamRS(false);
            break;
        case 'Q':
            scene.setCamZP(false);
            break;
        case 'E':
            scene.setCamZN(false);
            break;
        case 'I':
            ombres = false;
            break;
        default:
            break;
        }
    }
}

void Application::mousepos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    // CAMERA CONTROL, inutile pour l'instant
    scene.getCamera().handleMouseMove((int)mouseX, (int)mouseY);
}

void Application::setTitleFps()
{
    std::string title = "Chess 3D - FPS: " + std::to_string(nbFrames);
    glfwSetWindowTitle(window, title.c_str());


}
