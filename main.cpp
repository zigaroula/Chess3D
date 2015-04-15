#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    glewInit();
    if (!GLEW_VERSION_3_2)
       cout << "OpenGL version 3.3 is not available; please update your drivers!";
    return 0;
}

