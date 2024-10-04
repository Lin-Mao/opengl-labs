#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/freeglut.h>

class Rectangle {
private:
    // member variables
    float x;
    float y;
    float w;
    float h;
    float r;
    float g;
    float b;
    bool selected;

public:
    // default constructor
    Rectangle() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
        selected = false;
    }

    // parametrized constructor
    Rectangle(float _x, float _y, float _w, float _h, float _r, float _g, float _b) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
        r = _r;
        g = _g;
        b = _b;
        selected = false;
    }

    // draw method
    void draw() {
        glColor3f(r, g, b);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        if (selected) {
            Rectangle outer = Rectangle(x + 0.02f, y - 0.02f, w - 0.04f, h - 0.04f, 1.0f, 1.0f, 1.0f);
            Rectangle inner = Rectangle(x + 0.04f, y - 0.04f, w - 0.08f, h - 0.08f, r, g, b);
            outer.draw();
            inner.draw();
        }
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        }
        return false;
    }

    void select() {
        selected = true;
    }

    void deselect() {
        selected = false;
    }
};

#endif