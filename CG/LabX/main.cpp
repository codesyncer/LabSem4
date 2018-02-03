#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include <algorithm>

using namespace std;
const int width = 500, height = 500;

void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float xInc = (float) dx / steps, yInc = (float) dy / steps;
    float x = x1, y = y1;
    glBegin(GL_POINTS);
    while (steps-- >= 0) {
        glVertex2i((int) round(x), (int) round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;
    int p = 2 * dy + dx;
    int x = x1, y = y1;
    glBegin(GL_POINTS);
    while (x <= x2) {
        glVertex2i(x, y);
        ++x;
        if (p >= 0) {
            ++y;
            p -= 2 * dx;
        }
        p += 2 * dy;
    }
    glEnd();
}

void drawCircleNaive(int xc, int yc, int r) {
    int y, xLimit = (int) round(r / sqrt(2));
    glBegin(GL_POINTS);
    for (int x = 0; x <= xLimit; ++x) {
        y = (int) round(sqrt(r * r - x * x));
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    }
    glEnd();
}

void drawCircleAngular(int xc, int yc, int r, float step = -1) {
    int x, y;
    float o = 0;
    if (step == -1) step = 1.0f / r;
    glBegin(GL_POINTS);
    while (o <= M_PI / 4) {
        x = (int) round(r * cos(o)), y = (int) round(r * sin(o));
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
        o += step;
    }
    glEnd();
}

void drawCircleMidPoint(int xc, int yc, int r) {
    int x = 0, y = r, p = 5 / 4 - r;
    glBegin(GL_POINTS);
    while (x <= y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
        if (p >= 0) {
            --y;
            p -= 2 * y;
        }
        ++x;
        p += 1 + 2 * x;
    }
    glEnd();
}

void drawEllipseAngular(int xc, int yc, int rx, int ry, float step = -1) {
    int x, y;
    float o = 0;
    if (step == -1) step = 1.0f / max(rx, ry);
    glBegin(GL_POINTS);
    while (o <= M_PI / 2) {
        x = (int) round(rx * cos(o)), y = (int) round(ry * sin(o));
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        o += step;
    }
    glEnd();
}

void drawEllipseMidPoint(int xc, int yc, int rx, int ry) {
    int rx2 = rx * rx, ry2 = ry * ry;
    int x = 0, y = ry, p = ry2 - rx2 * ry + rx2 / 4;
    glBegin(GL_POINTS);
    while (ry2 * x <= rx2 * y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        ++x;
        if (p >= 0) {
            --y;
            p -= 2 * rx2 * y;
        }
        p += ry2 + 2 * ry2 * x;
    }
    int xlim = x - 1;
    x = rx, y = 0;
    p = (int) round(ry2 * (rx + 1.0 / 2) * (rx + 1.0 / 2)) + rx2 - rx2 * ry2;
    while (x >= xlim) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        ++y;
        if (p >= 0) {
            --x;
            p -= 2 * ry2 * x;
        }
        p += rx2 + 2 * rx2 * y;
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
//    drawLineDDA(-100, -100, 200, 150);
//    drawLineBresenham(-200, -150, 100, 100);
//    drawCircleNaive(100, 100, 140);
//    drawCircleAngular(100, 100, 130);
//    drawCircleMidPoint(100, 100, 120);
    drawEllipseMidPoint(100, 100, 100, 75);
    drawEllipseAngular(-100, -100, 100, 75);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void initOpenGL() {
    glOrtho(-250, 250, -250, 250, -250, 250);
    glClearColor(0, 0, 0, 0);
    glColor3f(0, 1, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(2200, 0);
    glutCreateWindow("CG");
    initOpenGL();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}