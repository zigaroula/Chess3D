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
    Application();
    
private:
    void display();
    void initOpenGL();
    
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    GLFWwindow *window;
    Program *program;
    Scene scene;
    
};


#endif