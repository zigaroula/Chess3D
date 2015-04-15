#ifndef __application_h_
#define __application_h_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/gl.h>
#endif
#include <GLFW/glfw3.h>

#include "program.h"


class Application
{
public:
    Application();
    GLuint getProgram() const { return program->getId(); }

    
private:
    void display();
    void initOpenGL();
    
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    GLuint vao;
    GLFWwindow *window;
    
    Program *program;
};


#endif