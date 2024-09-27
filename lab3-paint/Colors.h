#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <GL/freeglut.h>
#include "AppController.h"
#include "Texture.h"
#include "Button.h"
using namespace std;

class Colors {
    public:
    float x;
    float y;
    float w;
    float h;
    float b;
    float g;
    float r;
    bool selected;
    
    Colors(){

    }

    Colors(float _x, float _y, float _w, float _h, float _r, float _g, float _b){
        x = _x;
        y = _y;
        w = _w;
        h = _h;
        selected = false;
        b = _b;
        g = _g;
        r = _r;

    }

     void drawc() {
        // color background for polygon
        
        glColor3f( r, g, b);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        // black border
        if (selected) {
            glColor3f(1.0f, 1.0f, 1.0f);
        } else {
            glColor3f(0.0f, 0.0f, 0.0f);
        }
        glLineWidth(3.0f);
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
     }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        }
        return false;
    }


};





#endif