#include <iostream>
#include <GL/glut.h>

#include "utils.hpp"

static int WINDOW_HEIGHT = 500;
static int WINDOW_WIDTH = 500;

static bool manualSwapping = false;
static bool isBlue = false;
static bool enableAlphaTest = false;
static bool enableStencilTest = false;
static bool enableDepthTest = false;
static bool enableLogicalOp = false;

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

void drawRectanle(const Rectangle kv) {
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
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glLineWidth(3);
    glPointSize(3);

    { // трафарет (stencil)
        // подготовка трафарета (треугольный полигон)
        glEnable(GL_STENCIL_TEST);
        glColorMask(GL_FALSE, GL_FALSE,GL_FALSE,GL_FALSE);
        glStencilMask(0xff);
        glStencilFunc(GL_NEVER, 1, 0xff);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
        { // рисуем полигон, который будет запрещённой для отрисовки областью
            glBegin(GL_POLYGON);
            glVertex2d(0,0);
            glVertex2d(0.5, -0.5);
            glVertex2d(0, -.5);
            glEnd();
        }
        glStencilMask(0x0);
        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
        glDisable(GL_STENCIL_TEST);
    }

    glutPostRedisplay();
    glutSwapBuffers();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if(enableLogicalOp){
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_COPY_INVERTED);
    } else {
        glDisable(GL_COLOR_LOGIC_OP);
    }

    {
        renderString(0, 0.9, "color change (c)");
        if(isBlue)
            drawRectanle(Rectangle(0,0.9,0.8,0.1, Color(0,0,1,0)));
        else
            drawRectanle(Rectangle(0,0.9,0.8,0.1, Color(1,0,0,0)));
    }

    { // альфа (это четвёртый цвет в палитре RGBA)
        renderString(-0.9, 0, "alpha test (a)");
        glAlphaFunc(GL_GREATER, 0.1);
        if (enableAlphaTest)
            glEnable(GL_ALPHA_TEST);
        // в конструкторе цвета менятся чётвёртая компонента - это альфа и есть
        drawRectanle(Rectangle{-0.9, 0, -0.3, -0.5, Color{0,1,0,0}});
        drawRectanle(Rectangle{-0.5, -.4, -0.1, -0.8, Color{0.7,1,0,1}});
        if (enableAlphaTest)
            glDisable(GL_ALPHA_TEST);
    }

    { // трафарет
        renderString(0,0, "stencil test (s)");
        glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
        if (enableStencilTest)
            glEnable(GL_STENCIL_TEST);
        // tak tozhe mozhno!
        drawRectanle(Rectangle{0,0,0.8,-0.8, 0, Color{0.3, 0.3, 0, 0.3}});
        if (enableStencilTest)
            glDisable(GL_STENCIL_TEST);
    }

    { // глубина
        renderString(-0.9, 0.9, "depth test (d)");
        glEnable(GL_DEPTH_TEST);
        if (enableDepthTest)
            // квадрат вне разрешённой глубины
            drawRectanle(Rectangle{-0.55, 0.55, -0.1, 0.1, 1, Color{0.5, 0.5, 0, 0.3}});
        else {
            // квадрат внутри разрешённой глубины
            drawRectanle(Rectangle{-0.55, 0.55, -0.1, 0.1, 0.9, Color{0.5, 0.5, 0.3}});
        }
        drawRectanle(Rectangle{-0.9, 0.9, -0.5, 0.5, 0, Color{1, 0.5, 0, 0.4}});
        glDisable(GL_DEPTH_TEST);
    }

    glutPostRedisplay();
    if(!manualSwapping)
        glutSwapBuffers();
}

void ListenKeyboard(unsigned char key, int, int){
    switch(key){
    case 'm':
        std::cout << "manualSwapping: " << manualSwapping << std::endl;
        manualSwapping = !manualSwapping;
        break;
    case ' ':
        if (manualSwapping){
            std::cout << "swapping buffers" << std::endl;
            glutSwapBuffers();
        }
        break;
    case 'c':
        std::cout << "switching color" << std::endl;
        isBlue = !isBlue;
        break;
    case 'a':
        enableAlphaTest = !enableAlphaTest;
        std::cout << "alpha test: " << enableAlphaTest << std::endl;
        break;
    case 's':
        enableStencilTest = !enableStencilTest;
        std::cout << "stencil test: " << enableStencilTest << std::endl;
        break;
    case 'd':
        enableDepthTest = !enableDepthTest;
        std::cout << "depth test: " << enableDepthTest << std::endl;
        break;
    case 'l':
        enableLogicalOp = !enableLogicalOp;
        std::cout << "logical op: " << enableLogicalOp<< std::endl;
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
