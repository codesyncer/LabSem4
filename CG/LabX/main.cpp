#ifdef _WIN32
#include <windows.h>
#endif
#define M_PI 3.14159

#include <GL/glut.h>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
const int width = 1000, height = 1000;


void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;
    int step = max(abs(dx), abs(dy)), i = 0;
    float xInc = (float) dx / step, yInc = (float) dy / step;
    auto *vertices = new GLint[2 * (step + 1)];
    float x = x2, y = y1;
    while (step-- >= 0) {
        vertices[i] = static_cast<GLint>(round(x));
        vertices[i + 1] = static_cast<GLint>(round(y));
        i += 2;
        x += xInc;
        y += yInc;
    }
    glVertexPointer(2, GL_INT, 2 * sizeof(GLint), vertices);
    glDrawArrays(GL_POINTS, 0, i / 2);
    delete (vertices);
}

void drawLineBresenham(int x1, int y1, int x2, int y2) {
    bool draw_xy = true;
    float m = (float) (y2 - y1) / (x2 - x1);
    if (y2 > y1) {
//        oct 1
        if (0 <= m && m <= 1) {
        }
//        oct 2 & 3
        else if (m > 1 || m < -1) {
            swap(x1, y1);
            swap(x2, y2);
            draw_xy = false;
        }
//        oct 4
        else if (m > -1) {
            swap(x1, x2);
            swap(y1, y2);
        }
    } else {
//        oct 5
        if (0 <= m && m <= 1) {
            swap(x1, x2);
            swap(y1, y2);
        }
//        oct 6 & 7
        else if (m > 1 || m < -1) {
            swap(x1, x2);
            swap(y1, y2);
            swap(x1, y1);
            swap(x2, y2);
            draw_xy = false;
        }
//        oct 8
        else if (m > -1) {
        }
    }
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int p = 2 * dy - dx;
    int x = x1, y = y1;
    int dec = 2 * dx, inc = 2 * dy, i = 0;
    auto *vertices = new GLint[2 * (abs(dx) + 1)];
    bool inc_y = y < y2;
    while (x <= x2) {
        vertices[i] = draw_xy ? x : y;
        vertices[i + 1] = draw_xy ? y : x;
        i += 2;
        ++x;
        if (p >= 0) {
            y = y + (inc_y ? 1 : -1);
            p -= dec;
        }
        p += inc;
    }
    glVertexPointer(2, GL_INT, 2 * sizeof(GLint), vertices);
    glDrawArrays(GL_POINTS, 0, i / 2);
    delete (vertices);
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
        if (p >= 0) {
            --x;
            dec -= ry2 + ry2;
            p -= dec;
        }
        inc += rx2 + rx2;
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
int polyVertices[][2] = {{-100, -100},
                         {100,  -150},
                         {70,   100},
                         {0,    0},
                         {-150, 100},
                         {-80,  20}};
//int polyVertices[][2] = {{0, 0},
//                        {100, 100},
//                        {100, 0}};
//int polyVertices[][2] = {{0, 0},
//                    {100, 100},
//                    {100, 0}};
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

void fillPoly(int n, int v[][2]) {
    struct EdgeBucket {
        int yMax, yMin, sign, dx, dy, rem;
        float x;
    };
    EdgeBucket edgeTable[n];
    int m = 0;
    for (int i = 0; i < n; ++i) {
        int i1 = i;
        int i2 = (i + 1) % n;
        if (v[i1][1] != v[i2][1]) {
            edgeTable[m].yMax = max(v[i1][1], v[i2][1]);
            edgeTable[m].yMin = min(v[i1][1], v[i2][1]);
            edgeTable[m].rem = edgeTable[m].yMax - edgeTable[m].yMin;
            edgeTable[m].x = v[i1][1] < v[i2][1] ? v[i1][0] : v[i2][0];
            if (edgeTable[m].yMax == v[i2][1])
                edgeTable[m].sign = (v[i2][0] - v[i1][0]) < 0 ? -1 : 1;
            else
                edgeTable[m].sign = (v[i2][0] - v[i1][0]) <= 0 ? 1 : -1;
            edgeTable[m].dy = abs(v[i1][1] - v[i2][1]);
            edgeTable[m].dx = abs(v[i1][0] - v[i2][0]);
            m++;
        }
    }
    sort(edgeTable, edgeTable + m, [](EdgeBucket &e1, EdgeBucket &e2) {
        return e1.yMin < e2.yMin;
    });
    int activeList[n];
    for (int y = edgeTable[0].yMin; true; ++y) {
        int j = 0;
        for (int i = 0; i < m; ++i)
            if (edgeTable[i].yMin <= y && edgeTable[i].rem > 0)
                activeList[j++] = i;
        if (j == 0)
            break;
        sort(activeList, activeList + j, [&edgeTable](int &e1, int &e2) {
            return edgeTable[e1].x < edgeTable[e2].x;
        });
        for (int k = 0; k < j; k += 2) {
            int e1 = activeList[k];
            int e2 = activeList[k + 1];
            glBegin(GL_LINES);
            glVertex2i((int) round(edgeTable[e1].x), y);
            glVertex2i((int) round(edgeTable[e2].x), y);
            glEnd();
            edgeTable[e1].x += edgeTable[e1].sign * (float) edgeTable[e1].dx / edgeTable[e1].dy;
            edgeTable[e2].x += edgeTable[e2].sign * (float) edgeTable[e2].dx / edgeTable[e2].dy;
            edgeTable[e1].rem--;
            edgeTable[e2].rem--;
        }
    }
}

void customTranslate(int n, int v[][2], int x, int y) {
    int rotateMat[3][3] = {{1, 0, x},
                           {0, 1, y},
                           {0, 0, 1}};
    int r2 = 2, c2 = 1, r1 = 3;
    int result[r1][c2];
    for (int a = 0; a < n; ++a) {
        for (int i = 0; i < r1; ++i)
            for (int j = 0; j < c2; ++j) {
                result[i][j] = 0;
                for (int k = 0; k < r2; ++k)
                    result[i][j] += rotateMat[i][k] * v[a][k];
                result[i][j] += rotateMat[i][r2] * 1;
            }
        v[a][0] = round(result[0][0]);
        v[a][1] = round(result[1][0]);
    }
}

void customScale(int n, int v[][2], float s, int x = 0, int y = 0) {
    for (int i = 0; i < n; ++i) {
        v[i][0] -= x;
        v[i][1] -= y;
    }
    float rotateMat[2][2] = {{s, 0},
                             {0, s}};
    int r2 = 2, c2 = 1, r1 = 2;
    float result[r1][c2];
    for (int a = 0; a < n; ++a) {
        for (int i = 0; i < r1; ++i)
            for (int j = 0; j < c2; ++j) {
                result[i][j] = 0;
                for (int k = 0; k < r2; ++k)
                    result[i][j] += rotateMat[i][k] * v[a][k];
            }
        v[a][0] = round(result[0][0]);
        v[a][1] = round(result[1][0]);
    }
    for (int i = 0; i < n; ++i) {
        v[i][0] += x;
        v[i][1] += y;
    }
}

void customRotate(int n, int v[][2], double theta, int x = 0, int y = 0) {
    for (int i = 0; i < n; ++i) {
        v[i][0] -= x;
        v[i][1] -= y;
    }
    theta *= M_PI / 180;
    float s = sin(theta), c = cos(theta);
    float rotateMat[2][2] = {{c, -s},
                             {s, c}};
    int r2 = 2, c2 = 1, r1 = 2;
    float result[r1][c2];
    for (int a = 0; a < n; ++a) {
        for (int i = 0; i < r1; ++i)
            for (int j = 0; j < c2; ++j) {
                result[i][j] = 0;
                for (int k = 0; k < r2; ++k)
                    result[i][j] += rotateMat[i][k] * v[a][k];
            }
        v[a][0] = round(result[0][0]);
        v[a][1] = static_cast<int>(round(result[1][0]));
    }
    for (int i = 0; i < n; ++i) {
        v[i][0] += x;
        v[i][1] += y;
    }
}

void myCube(int a) {
    int polyVertices[][2] = {{-a / 2, -a / 2},
                             {a / 2,  -a / 2},
                             {a / 2,  a / 2},
                             {-a / 2, a / 2}};
    int tmp[4][2];
    memcpy(tmp, polyVertices, sizeof(polyVertices));
    glTranslated(0, 0, -a / 2);
    glColor3ub(255, 255, 255);
    fillPoly(sizeof(tmp) / sizeof(tmp[0]), tmp);
    glTranslated(0, 0, a);
    glColor3ub(255, 0, 0);
    fillPoly(sizeof(tmp) / sizeof(tmp[0]), tmp);
    glTranslated(0, 0, -a / 2);
    glRotated(90, 0, 1, 0);
    glTranslated(0, 0, a / 2);
    glColor3ub(0, 255, 0);
    fillPoly(sizeof(tmp) / sizeof(tmp[0]), tmp);
    glTranslated(0, 0, -a);
    glColor3ub(0, 0, 255);
    fillPoly(sizeof(tmp) / sizeof(tmp[0]), tmp);
    glTranslated(0, 0, a / 2);
    glRotated(-90, 0, 1, 0);
}

bool clip(int xmin, int xmax, int ymin, int ymax, int &x1, int &y1, int &x2, int &y2) {
    int dx = x2 - x1, dy = y2 - y1;
    int p[] = {-dx, dx, -dy, dy}, q[] = {x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};
    float u0 = 0, u1 = 1;
    for (int k = 0; k < 4; ++k) {
        if (p[k] == 0 && q[k] < 0) return false;
        if (p[k] == 0 && q[k] >= 0) {
            y1 = max(y1, ymin);
            y2 = min(y2, ymax);
            x1 = max(x1, xmin);
            x2 = min(x2, xmax);
            return true;
        }
        if (p[k] != 0) {
            if (p[k] < 0)
                u0 = max(u0, (float) q[k] / p[k]);
            else
                u1 = min(u1, (float) q[k] / p[k]);

        }
    }
    if (u0 > u1) return false;
    x2 = (int) (x1 + u1 * dx);
    y2 = (int) (y1 + u1 * dy);
    x1 = (int) (x1 + u0 * dx);
    y1 = (int) (y1 + u0 * dy);
    return true;
}

void clipDemo() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(-200, -200);
    glVertex2i(100, -200);
    glVertex2i(100, 50);
    glVertex2i(-200, 50);
    glVertex2i(-200, -200);
    glEnd();
    int x1, x2, y2, y1;
    x1 = -240, y1 = -100, x2 = 240, y2 = 180;
//    x1 = 0, y1 = 100, x2 = 240, y2 = -150;
//    x1 = -100, y1 = -240, x2 = 80, y2 = 80;
//    x1 = 0, y1 = 0, x2 = -240, y2 = 25;
    if (clip(-200, 100, -200, 50, x1, y1, x2, y2)) {
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
//    drawLineDDA(0, 0, 200, 50);
//    drawLineBresenham(0, 0, 200, 150);
//    drawLineBresenham(0, 0, 150, 200);
//    drawLineBresenham(0, 0, -150, 200);
//    drawLineBresenham(0, 0, -200, 150);
//    drawLineBresenham(0, 0, -200, -150);
//    drawLineBresenham(0, 0, -150, -200);
//    drawLineBresenham(0, 0, 150, -200);
//    drawLineBresenham(0, 0, 200, -150);
    //drawCircleMidPoint(100, 100, 50);
    //drawCircleMidPoint(-100, -100, 50);
    //drawEllipseAngular(-100, -100, 100, 75);
    //drawEllipseMidPoint(0, 0, 200, 100);
    //rectangleEffect();
    //glColor3f(0, 0, 1);
    //fillPoly(sizeof(polyVertices1) / sizeof(polyVertices1[0]), polyVertices1);
    //glColor3f(0, 1, 0);
    //fillPoly(sizeof(polyVertices) / sizeof(polyVertices[0]), polyVertices);
    //glRotated(1,0,1,1);
    //glutSolidCube(200);
//    glRotated(1,0,1,0);
//    myCube(100);
    clipDemo();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(w / 2 - h / 2, 0, h, h);
}

void initOpenGL() {
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
    glClearColor(.05, .05, .05, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
    vertices = new Vertex[4];
    vertices[0].set(-20, -20, 255, 0, 0);
    vertices[1].set(20, -20, 0, 255, 0);
    vertices[2].set(20, 20, 0, 0, 255);
    vertices[3].set(-20, 20, 255, 255, 255);
    //customScale(sizeof(polyVertices) / sizeof(polyVertices[0]), polyVertices, .5);
    //customTranslate(sizeof(polyVertices) / sizeof(polyVertices[0]), polyVertices, 200,200);
    //customRotate(sizeof(polyVertices) / sizeof(polyVertices[0]), polyVertices, 45, polyVertices[1][0], polyVertices[1][1]);
}

void deInitOpenGl() {
    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_COLOR_ARRAY);
    delete vertices;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
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
