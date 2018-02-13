#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
const int width=500, height=500;
void BresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx= x2-x1, dy= y2-y1;
    int d= 2*dy-dx, inc= 2*dy;
    glBegin(GL_POINTS);
    for(int x=x1, y=y1; x<=x2; ++x){
        glVertex2i(x,y);
        d+=inc;
        if(d>=0){
            ++y;
            d-=2*dx;
        }
    }
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(.5, 0,0,1);
    glTranslatef(1,1,0);
    glBegin(GL_POLYGON);
    glVertex2i(-10,-10);
    glVertex2i(10, -10);
    glVertex2i(10, 10);
    glVertex2i(-10,10);
    glEnd();
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0.0, 0.0, width, height);
}
void initopenGL()
{
    glClearColor(0.0, 0.0, 0.0, 1);
    glOrtho(0, 500, 0, 500,0,1);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Mid");
    initopenGL();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
