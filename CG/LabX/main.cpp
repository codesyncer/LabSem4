#ifdef _WIN32
#include <windows.h>
#endif
#define M_PI 3.14159
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
    int dx = x2 - x1, dy = abs(y2 - y1);
    int p = 2 * dy + dx;
    int x = x1, y = y1;
    int dec = 2 * dx, inc = 2 * dy;
    glBegin(GL_POINTS);
    while (x <= x2) {
        glVertex2i(x, y);
        ++x;
        if (p >= 0) {
            --y;
            p -= dec;
        }
        p += inc;
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
    int inc = 1 + 2 * x, dec = 2 * y;
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
            dec -= 2;
            p -= dec;
        }
        ++x;
        inc += 2;
        p += inc;
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
    int inc = ry2 + 2 * ry2 * x, dec = 2 * rx2 * y, lhs = ry2 * x, rhs = rx2 * y;
    glBegin(GL_POINTS);
    while (lhs <= rhs) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        ++x;
        inc += ry2 + ry2;
        lhs += ry2;
        if (p >= 0) {
            --y;
            dec -= rx2 + rx2;
            rhs -= rx2;
            p -= dec;
        }
        p += inc;
    }
    int xLimit = x - 1;
    x = rx, y = 0;
    inc = rx2 + 2 * rx2 * y, dec = 2 * ry2 * x;
    p = (int) round(ry2 * (rx - 1.0 / 2) * (rx - 1.0 / 2)) + rx2 - rx2 * ry2;
    while (x > xLimit) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        ++y;
        inc += rx2 + rx2;
        if (p >= 0) {
            --x;
            dec -= ry2 + ry2;
            p -= dec;
        }
        p += inc;
    }
    glEnd();
}

struct Vertex {
    GLint x, y;
    GLubyte r, g, b;

    Vertex(GLint x, GLint y, GLubyte r = 0, GLubyte g = 0, GLubyte b = 0) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->g = g;
        this->b = b;
    }

    Vertex() = default;

    void set(GLint x, GLint y, GLubyte r = 0, GLubyte g = 0, GLubyte b = 0) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->g = g;
        this->b = b;
    }
};


Vertex *vertices = nullptr;
int polyVertices[][2] = {{-20,-20}, {20, -20}, {40, 10}, {0, 30}, {-30, 20}};
int i = 1;

void rectangleEffect() {
    glRotated(-i + 1, 0, 0, 1);
    glTranslatef(1, 1, 0);
    glRotated(i, 0, 0, 1);
    glVertexPointer(2, GL_INT, sizeof(Vertex), vertices);
    glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(Vertex), &vertices[0].r);
    glDrawArrays(GL_QUADS, 0, 4);
    i = (i + 1) % 360;
}

void fillPoly(int n, int v[][2]){
    struct EdgeBucket{
        int yMax, yMin, x, sign, dx, dy, sum;
    };
    struct Edge{
        int lx, ly, rx, ry;
    };
    EdgeBucket *edgeBuckets = new EdgeBucket[n];
    Edge *edges = new Edge[n];
    int m = 0;
    for (int i =0; i<n;++i){
        int i1 = i; int i2 = (i+1)%n;
        if(v[i1][1] != v[i2][1]){
            edgeBuckets[m].yMax = max(v[i1][1], v[i2][1]);
            edgeBuckets[m].yMin = min(v[i1][1], v[i2][1]);
            edgeBuckets[m].x = v[i1][1] < v[i2][1] ? v[i1][0] : v[i2][0];
            edgeBuckets[m].sign = (v[i2][1] - v[i1][1]) * (v[i2][0] - v[i1][0]) < 0 ? -1 : 1;
            edgeBuckets[m].dy = abs(v[i1][1] - v[i2][1]);
            edgeBuckets[m].dx = abs(v[i1][0] - v[i2][0]);
            edgeBuckets[m].sum = 0;
            edges[m].lx = v[i1][0] < v[i2][0] ? v[i1][0] : v[i2][0];
            edges[m].ly = v[i1][0] < v[i2][0] ? v[i1][1] : v[i2][1];
            edges[m].rx = v[i1][0] > v[i2][0] ? v[i1][0] : v[i2][0];
            edges[m].ry = v[i1][0] > v[i2][0] ? v[i1][1] : v[i2][1];
            m++;
        }
    }
    sort(edges, edges+m, [](Edge &e1, Edge &e2){
         return min(e1.ly, e1.ry) < min(e2.ly, e2.ry);
        });

    delete edgeBuckets;
    delete edges;
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,0);
    //drawLineDDA(-100, -100, 200, 150);
    //drawLineBresenham(-120, 80, 0, 0);
    //drawLineBresenham(-100, 80, 0, 0);
    //drawCircleNaive(100, 100, 140);
    //drawCircleAngular(100, 100, 130);
    drawCircleMidPoint(100, 100, 120);
    //drawEllipseAngular(-100, -100, 100, 75);
    drawEllipseMidPoint(100, 100, 100, 75);
    //rectangleEffect();
    fillPoly(6, polyVertices);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void initOpenGL() {
    glOrtho(-250, 250, -250, 250, -250, 250);
    glClearColor(0, 0, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    vertices = new Vertex[4];
    vertices[0].set(-20, -20, 255, 0, 0);
    vertices[1].set(20, -20, 0, 255, 0);
    vertices[2].set(20, 20, 0, 0, 255);
    vertices[3].set(-20, 20, 255, 255, 255);
}

void deInitOpenGl() {
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    delete vertices;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CG");
    initOpenGL();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    deInitOpenGl();
    return 0;
}
