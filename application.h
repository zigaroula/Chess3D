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

class Application
{
public:
    static void start();
    
private:
    static void display();
    static void initOpenGL();
    
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_size_callback(GLFWwindow *window, int width, int height);
    
    static GLFWwindow *window;
    static Program *program;
    static Scene scene;
    
    static constexpr int DEFAULT_WIDTH = 640;
    static constexpr int DEFAULT_HEIGHT = 480;
    
};

#endif