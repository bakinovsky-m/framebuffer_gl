#include <iostream>
#include <GL/glut.h>

static int WINDOW_HEIGHT = 500;
static int WINDOW_WIDTH = 500;

static bool isBlue = false;
static bool enableAlphaTest = false;
static bool enableStencilTest = false;
static bool enableDepthTest = false;

void init(){
    glClearColor(1, 1, 1, 1);
    glClearDepth(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutPostRedisplay();
    glutSwapBuffers();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(3);
    glPointSize(3);
    glBegin(GL_POLYGON);
    if(isBlue)
        glColor3d(0,0,1);
    else
        glColor3d(1,0,0);
    glVertex2d(0, 0);
    glVertex2d(0.9, 0.9);
    glVertex2d(0.9, 0.9);
    glVertex2d(0.9, 0);
    glVertex2d(0.9, 0);
    glVertex2d(0, 0);
    glEnd();

    glAlphaFunc(GL_GREATER, 0.1);
    if (enableAlphaTest)
        glEnable(GL_ALPHA_TEST);
    glBegin(GL_POLYGON);
    glColor4d(0,1,0,0);
    glVertex2d(0, 0);
    glVertex2d(-0.9, -0.9);
    glVertex2d(-0.9, -0.9);
    glVertex2d(-0.9, 0);
    glVertex2d(-0.9, 0);
    glVertex2d(0, 0);
    glEnd();
    if (enableAlphaTest)
        glDisable(GL_ALPHA_TEST);

//    glAlphaFunc(GL_GREATER, 0);
    glStencilFunc(GL_GREATER, 0, 0xff);
    glStencilOp(GL_ZERO, GL_KEEP, GL_KEEP);
    if (enableStencilTest)
        glEnable(GL_STENCIL_TEST);
    glBegin(GL_POLYGON);
    glColor4d(0,0,1,0);
    glVertex2d(0, 0);
    glVertex2d(0.9, -0.9);
    glVertex2d(0.9, -0.9);
    glVertex2d(0.9, 0);
    glVertex2d(0.9, 0);
    glVertex2d(0, 0);
    glEnd();
    if (enableStencilTest)
        glDisable(GL_STENCIL_TEST);

    glDepthFunc(GL_NEVER);
    if (enableDepthTest)
        glEnable(GL_DEPTH_TEST);
    glBegin(GL_POLYGON);
    glColor4d(0.5,0,0.3,0);
    glVertex3d(0, 0, -1);
    glVertex3d(-0.9, 0.9, -1);
    glVertex3d(-0.9, 0.9, -1);
    glVertex3d(-0.9, 0, -1);
    glVertex3d(-0.9, 0, -1);
    glVertex3d(0, 0, -1);
    glEnd();
    if (enableDepthTest)
        glDisable(GL_DEPTH_TEST);

    glutPostRedisplay();
}

void ListenKeyboard(unsigned char key, int, int){
    switch(key){
    case ' ':
        std::cout << "swapping buffers" << std::endl;
        glutSwapBuffers();
        break;
    case 'c':
        std::cout << "switching color" << std::endl;
        isBlue = !isBlue;
        break;
    case 'a':
        std::cout << "alpha test" << std::endl;
        enableAlphaTest = !enableAlphaTest;
        break;
    case 's':
        std::cout << "stencil test" << std::endl;
        enableStencilTest = !enableStencilTest;
        break;
    case 'd':
        std::cout << "depth test" << std::endl;
        enableDepthTest = !enableDepthTest;
        break;
    }
}

int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA | GLUT_STENCIL);
    glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("MyOpenGL");
    std::cout << "opengl version: " << glGetString( GL_VERSION ) << std::endl;
    init();
    glutDisplayFunc(Display);
    glutKeyboardFunc(ListenKeyboard);
    glutMainLoop();
}
