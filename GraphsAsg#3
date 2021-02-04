// asg1num3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <GL/glut.h>
#include <iostream>


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(50, 37);
        glVertex2i(150, 37);
        glVertex2i(150, 112);
        glVertex2i(50, 112);
    glEnd();

    glFlush();
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(75, 350); //positions top left corner of window
    glutInitWindowSize(200, 150);
    glutCreateWindow("Number 3");
    
    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop(); // Last


}
