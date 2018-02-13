#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(1,1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(0,.5);
    glVertex2f(.5,0);
    glVertex2f(.25,-.25);
    glVertex2f(-.25,-.25);
    glVertex2f(-.5,0);
    glEnd();
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0.0, 0.0, w, h);
}
void intiopenGL()
{
    glClearColor(0.0, 0.0, 0.0, 1);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("OpenGL Test");

    intiopenGL();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
