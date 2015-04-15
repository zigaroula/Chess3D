#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "program.h"

using namespace std;

static Program * program;


int main()
{
    cout << "Hello World!" << endl;

    glewInit();

    if (!GLEW_VERSION_3_2)
       cout << "OpenGL version 3.3 is not available; please update your drivers!";
    return 0;
}

/* A mettre dans l'initialisation

  program = new Program("Programme", "shader.vert", "shader.frag");
*/
