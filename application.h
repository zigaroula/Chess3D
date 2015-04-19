#ifndef __application_h_
#define __application_h_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include "program.h"
#include "scene.h"
#include "camera.h"
#include "game.h"

class Application
{
public:
    static void start();

private:
    static void display();
    static void initOpenGL();
    static void initGame();

    static void setTitleFps();
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_size_callback(GLFWwindow *window, int width, int height);
    static void mousepos_callback(GLFWwindow* window, double mouseX, double mouseY);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    static void saveTexture();

    static double lastTime;
    static int nbFrames;
    static int nbFramesLastSecond;
    static GLFWwindow *window;
    static Program program;
    static Program program_shadows;
    static Program program_selection;
    static Scene scene;
    static Camera *camera;
    static Game game;
    
    static void renderShadow();
    static void renderScene();

    static int window_width, window_height;
    static int framebuffer_width, framebuffer_height;

    // Pour la camera
    static int midWindowX, midWindowY;

    // Selection
    static void processSelection(int, int);
    static void renderSelection();
};


#endif
