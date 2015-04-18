#include "application.h"


#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

GLFWwindow *Application::window;
Program Application::program;
Program Application::program_shadows;
Scene Application::scene;
Game Application::game;
double Application::lastTime;
int Application::nbFrames;
int Application::nbFramesLastSecond;
int Application::window_height;
int Application::window_width;
int Application::midWindowX;
int Application::midWindowY;
int Application::framebuffer_width, Application::framebuffer_height;

void Application::start()
{
    initGame();

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,  GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    window_height = mode->height;
    window_width= mode->width;

    midWindowX = window_width/2;
    midWindowY = window_height/2;
    window = glfwCreateWindow(window_width, window_height, "Chess3D", NULL, NULL);

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
    nbFramesLastSecond = 100;



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

    program.init();
    program_shadows.initForShadowMap();

    scene.initScene(window_width, window_height);

    program.use();

    scene.setPerspective(window_width, window_height);
    glUniformMatrix4fv(glGetUniformLocation(program.getId(), "projection_matrix"), 1, GL_FALSE, scene.getProjectionMatrixArray());
    
    glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);

}

void Application::initGame() {
    game.initClassicGame();
}

void Application::display()
{

    renderShadow();
    renderScene();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::renderShadow()
{
    // 1ERE PASSE SHADOW
    program_shadows.use();
    
    glBindFramebuffer(GL_FRAMEBUFFER , scene.getShadowBufferId());
    
    glClear(GL_DEPTH_BUFFER_BIT); /* important */
    glViewport(0, 0, scene.getShadowSize(), scene.getShadowSize());
    glm::vec3 lightPos(100.f, 100.f, 100.f);
    
    // On calcule la matrice Model-Vue-Projection du point de vue de la lumière
    const glm::mat4& shadow_proj_matrix = scene.getShadowProjectionMatrix();
    glm::mat4 depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0,0,0), glm::vec3(0,1,0));

    /* render each VAO*/
    for (unsigned int i = 0; i < scene.size(); ++i)
    {
        const Vao &vao = scene[i];
        
        const glm::mat4& model_matrix =  vao.getModelMatrix();
        glm::mat4 depthMVP = shadow_proj_matrix * depthViewMatrix * model_matrix;
        // On envoie la matrix au shader lié (MVP_matrix)
        glUniformMatrix4fv(glGetUniformLocation(program_shadows.getId(), "MVP_matrix"), 1, GL_FALSE, &depthMVP[0][0]);
        
        glBindVertexArray(vao.getId());
        glDrawArrays(GL_TRIANGLES, 0, vao.getVertexCount());
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER , 0);
    
}

void Application::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2EME PASSE SHADOW
    program.use();
    
    // CAMERA VIEW
    scene.setView();


    glUniformMatrix4fv(glGetUniformLocation(program.getId(), "view_matrix"), 1, GL_FALSE, scene.getViewMatrixArray());
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, scene.getShadowTexureId());
    glUniform1i(glGetUniformLocation(program.getId(), "shadow_text"), 2);
    
    glViewport(0, 0, framebuffer_width, framebuffer_height);
    
    glm::vec3 lightPos(100.f, 100.f, 100.f);
    const glm::mat4& shadow_proj_matrix = scene.getShadowProjectionMatrix();
    glm::mat4 depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0,0,0), glm::vec3(0,1,0));
    
    for (unsigned int i = 0; i < scene.size(); ++i)
    {
        const Vao &vao = scene[i];
        
        const glm::mat4& model_matrix =  vao.getModelMatrix();
        glm::mat4 depthMVP = shadow_proj_matrix * depthViewMatrix * model_matrix;
        glm::mat4 depthBiasMVP = scene.getBiasMatrix() * depthMVP;
        
        glUniform1i(glGetUniformLocation(program.getId(), "texture_enabled"), vao.isTextureEnabled());
        
        if (vao.isTextureEnabled())
        {
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, vao.getTextureId());
            glUniform1i(glGetUniformLocation(program.getId(), "object_texture"), 3);
        }
        
        glUniformMatrix4fv(glGetUniformLocation(program.getId(), "bias_matrix"), 1, GL_FALSE, glm::value_ptr(depthBiasMVP));
        
        glUniform3fv(glGetUniformLocation(program.getId(), "ambient_color"), 1, vao.getAmbientColorArray());
        
        glUniformMatrix4fv(glGetUniformLocation(program.getId(), "normal_matrix"), 1, GL_FALSE, scene.getNormalMatrixArray(i));
        
        glUniformMatrix4fv(glGetUniformLocation(program.getId(), "model_matrix"), 1, GL_FALSE, vao.getModelMatrixArray());
        
        
        glBindVertexArray(vao.getId());
        glDrawArrays(GL_TRIANGLES, 0, vao.getVertexCount());
    }
    
    glBindVertexArray(0);
    
}

void Application::saveTexture()
{
	std::cout << "save texture" << std::endl;

    glBindTexture(GL_TEXTURE_2D, scene.getShadowTexureId());

    GLint textureWidth, textureHeight;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

    std::cout << textureWidth << ";" << textureHeight << std::endl;

    GLfloat *data = new GLfloat[textureWidth*textureHeight];
    glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, data);

    std::ofstream myfile;
    myfile.open("test.txt");
    for (int i = 0 ; i < textureHeight; ++i)
    {
    	for (int j = 0; j < textureWidth; ++j)
    	{
    		int index = i*textureWidth+j;
    		myfile << data[index] << ",";

    	}
    	myfile << "\n";
    }

    myfile.close();

}

void Application::window_size_callback(GLFWwindow *window, int width, int height)
{
    glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);

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
        case 'T':
        	saveTexture();
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
