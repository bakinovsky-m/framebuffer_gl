#include <iostream>
#include <GL/glut.h>

#include "utils.hpp"

static int WINDOW_HEIGHT = 500;
static int WINDOW_WIDTH = 500;

static bool isBlue = false;
static bool enableAlphaTest = false;
static bool enableStencilTest = false;
static bool enableDepthTest = false;

void renderString(double x, double y, std::string string){
    double dx = x;
    //Top left corner of text
    glRasterPos3d(x, y, -1);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);  //RGBA values of text color
    for (char c : string){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        double symbolWidth = glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, c)/(double)WINDOW_WIDTH;
        dx += symbolWidth + 0.015;
        glRasterPos3d(dx, y, -1);
    }
}

void drawKvadrat(const Kvadrat kv) {
    glColor4d(kv.color.r, kv.color.g, kv.color.b, kv.color.a);
    glBegin(GL_QUADS);
    glVertex3d(kv.tl_x, kv.tl_y, kv.depth);
    glVertex3d(kv.br_x, kv.tl_y, kv.depth);
    glVertex3d(kv.br_x, kv.br_y, kv.depth);
    glVertex3d(kv.tl_x, kv.br_y, kv.depth);
    glEnd();
}

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

    renderString(0, 0.9, "color change (c)");
    if(isBlue)
        drawKvadrat(Kvadrat(0,0.9,0.8,0.1, Color(0,0,1,0)));
    else
        drawKvadrat(Kvadrat(0,0.9,0.8,0.1, Color(1,0,0,0)));

    renderString(-0.9, 0, "alpha test (a)");
    glAlphaFunc(GL_GREATER, 0.1);
    if (enableAlphaTest)
        glEnable(GL_ALPHA_TEST);
    // prikolniy constructor, zaceni!
    drawKvadrat({-0.9, 0, -0.1, -0.8, {0,1,0,0}});
    if (enableAlphaTest)
        glDisable(GL_ALPHA_TEST);

    renderString(0,0, "stencil test (s)");
    glStencilFunc(GL_GREATER, 0, 0xff);
    glStencilOp(GL_ZERO, GL_KEEP, GL_KEEP);
    if (enableStencilTest)
        glEnable(GL_STENCIL_TEST);
    // tak tozhe mozhno!
    drawKvadrat(Kvadrat{0,0,0.8,-0.8, 0, Color{0.3, 0.3,0}});
    if (enableStencilTest)
        glDisable(GL_STENCIL_TEST);

    renderString(-0.9, 0.9, "depth test (d)");
    glDepthFunc(GL_NEVER);
    if (enableDepthTest)
        glEnable(GL_DEPTH_TEST);
    drawKvadrat(Kvadrat{-0.9, 0.9, -0.1, 0.1, 0, Color{1, 0.5, 0}});
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
