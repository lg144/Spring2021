#include <math.h>
#include <iostream>
#include <gl/glut.h>
#include "global.h"
#define X_MAX 600
#define Y_MAX 400
#define X_POSITION 200
#define Y_POSITION 200
using namespace std;
static Coords polygons[20][100];
static int coordsP = 0;
static int polygonsP = 0;
static int previousMouseLoc[2] = { 0,0 };
static int recentMouseButton = 0;

static bool drawn = false;


Color getPixelColor(GLint x, GLint y) {
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}
void init() {

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, X_MAX, 0, Y_MAX);    
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
void onMouseMove(int x, int y) {
    if (coordsP == 0 || recentMouseButton == GLUT_RIGHT_BUTTON) {
        previousMouseLoc[0] = x;
        previousMouseLoc[1] = y;
        return;
    }
    y = (glutGet(GLUT_WINDOW_HEIGHT) - y) * (float)Y_MAX / glutGet(GLUT_WINDOW_HEIGHT);
    x = x * ((float)X_MAX / glutGet(GLUT_WINDOW_WIDTH));
    glBlendFunc(GL_ONE, GL_ZERO);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2i(previousMouseLoc[0], previousMouseLoc[1]);
    glVertex2i(polygons[polygonsP][coordsP-1].x, polygons[polygonsP][coordsP - 1].y);
    glEnd();
    glColor4f(borderColor[0], borderColor[1], borderColor[2], borderColor[3]);
    glBegin(GL_LINE_STRIP);
        glVertex2i(polygons[polygonsP][coordsP - 1].x, polygons[polygonsP][coordsP - 1].y);
        glVertex2i(x, y);
    glEnd();
    glFlush();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    previousMouseLoc[0] = x;
    previousMouseLoc[1] = y;
    drawn = true;
}
void onMouseClick(int button, int state, int x, int y)
{
    recentMouseButton = button;
    y = (glutGet(GLUT_WINDOW_HEIGHT) - y) * (float)Y_MAX / glutGet(GLUT_WINDOW_HEIGHT);
    x = x * ((float)X_MAX / glutGet(GLUT_WINDOW_WIDTH));
    if (button == GLUT_RIGHT_BUTTON && coordsP >= 3) {
        glBlendFunc(GL_ONE, GL_ZERO);
        glColor4f(borderColor[0], borderColor[1], borderColor[2], borderColor[3]);
        glBegin(GL_LINES);
        glVertex2i(polygons[polygonsP][coordsP-1].x, polygons[polygonsP][coordsP - 1].y);
        glVertex2i(polygons[polygonsP][0].x, polygons[polygonsP][0].y);
        glEnd();
        glFlush();
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        polygonsP++;
        coordsP = 0;
        drawn = false;
    }
    if (button == GLUT_LEFT_BUTTON && (state == GLUT_DOWN && coordsP == 0 || state == GLUT_UP && drawn)) {
        glPointSize(2);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        polygons[polygonsP][coordsP].x = x;//mouseLoc[0] = x;
        polygons[polygonsP][coordsP].y = y;//mouseLoc[1] = y;
        coordsP++;
        drawn = false;
    }
}
int openGLMain()
{
    int argc = 1;
    char* argv[1] = { (char*)"Something" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(X_MAX, Y_MAX);
    glutInitWindowPosition(X_POSITION, Y_POSITION);
    //start setting up a display window
    glutCreateWindow("Polygon Shader");
    init();
    glutDisplayFunc(display);
    //finish setting up a display window
    glutMotionFunc(onMouseMove);
    glutMouseFunc(onMouseClick);
    glutMainLoop();
    return 0;
}
