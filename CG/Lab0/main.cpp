#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
float getRand()
{
    return 1.0*(rand()-RAND_MAX/2)/RAND_MAX;
}
float prevX= getRand(), prevY=getRand(), newX, newY;
int cnt=0;
void display()
{
    cnt++;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1,0,0);
    glVertex3f(-.2,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,-.2,0);
    glColor3f(0,0,1);
    glVertex3f(.2,.2,0);
    glColor3f(1,1,1);
    glVertex3f(.5,-0.5,0);
    glColor3f(1,1,1);
    glVertex3f(.5,0.5,0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1,1,1);
    glVertex3f(-.5,-.5,0);
    glVertex3f(.0,.0,0);
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(1,0,1);
    glVertex3f(.5,.5,1);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glVertex3f(-.2,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,-.2,0);
    glColor3f(0,0,1);
    glVertex3f(.2,.2,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(1,0,0);
    glVertex3f(-.3,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,-.3,0);
    glColor3f(0,0,1);
    glVertex3f(.3,.3,0);
    glEnd();
    if(cnt>10)
    {
        cnt=0;
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        newX = getRand();
        newY = getRand();
        glVertex3f(newX,newY,0);
        glVertex3f(prevX,prevY,0);
        prevX = newX;
        prevY = newY;
        glEnd();
    }
    glRotatef(1,1,1,0);
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
