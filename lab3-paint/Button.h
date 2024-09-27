#ifndef BUTTON_H
#define BUTTON_H

#include <GL/freeglut.h>
#include <string>
#include <iostream>

class Button {
public:
    float x;
    float y;
    float w;
    float h;
    bool pressed;
    std::string text;

    Button() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        pressed = false;
        text = "Button";
    }

    Button(float _x, float _y, std::string _text) {
        x = _x;
        y = _y;
        w = 0.1f;
        h = 0.1f;
        pressed = false;
        text = _text;
    }

    void drawb() {
        float padding = 0.06f;

        float textWidth = 0;
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        w = 0.1f;

        // white polygon
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();
        
        // black border
        glLineWidth(3.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + w, y);

            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);

            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);

            glVertex2f(x, y - h);
            glVertex2f(x, y);
        glEnd();

        // position of where text will be rendered
        if (pressed) {
            glRasterPos2f(x + (padding / 2) - 0.02f, y - (h / 2) - 0.045f);
        } else {
            glRasterPos2f(x + (padding / 2), y - (h / 2) - 0.025f);
        }
        for (int i = 0; i < text.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        }

        // // alternative way to render text
        // const unsigned char* temp = (unsigned char*) text.c_str();
        // glutBitmapString(GLUT_BITMAP_9_BY_15, temp);
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        }
        return false;
    }
};

#endif