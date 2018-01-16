#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
const int width=500, height=500;
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx= x2-x1, dy= y2-y1;
    int steps= max(abs(dx), abs(dy));
    float xinc= (float)dx/steps, yinc= (float)dy/steps;
    float x=x1,y=y1;
    glBegin(GL_POINTS);
    for(int i=0; i<=steps; ++i)
    {
        glVertex2f(2*x/width, 2*y/height);
        x+=xinc;
        y+=yinc;
    }
    glEnd();
}
void drawLine(double x1, double y1, double x2, double y2, double double_inc= 0.001)
{
    double dx= x2-x1, dy= y2-y1;
    double steps= max(dx<0?-dx:dx,dy<0?-dy:dy)/double_inc;
    double xinc= dx/steps, yinc= dy/steps;
    double x=x1,y=y1;
    glBegin(GL_POINTS);
    for(int i=0; i<=steps; i++)
    {
        glVertex2f(x, y);
        x+=xinc;
        y+=yinc;
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(0, 25,225,225);
    drawLine(.0,.0,.9,.8);
    glBegin(GL_LINES);
    glVertex2d(.0,-.1);
    glVertex2d(.9,.7);
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
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("DAA");
    intiopenGL();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
