#ifndef POINT_H
#define POINT_H

#include <GL/freeglut.h>

class Point {
private:
    // member variables
    float x;
    float y;
    float r;
    float g;
    float b;
    float size;

public:
    // default constructor
    Point() {
        x = 0.0f;
        y = 0.0f;
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
        size = 7.0f;
    }

    // parametrized constructor
    Point(float _x, float _y, float _r, float _g, float _b, float _size) {
        x = _x;
        y = _y;
        r = _r;
        g = _g;
        b = _b;
        size = _size;
    }

    void draw() {
        glColor3f(r, g, b);
        glPointSize(size);

        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
};

#endif