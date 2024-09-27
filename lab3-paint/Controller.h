#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "AppController.h"
#include "Texture.h"
#include "Button.h"
#include "Colors.h"

using namespace std;

class Point {
public:
    float r;
    float g;
    float b;
    float x;
    float y;
    float s;

    Point(float _x, float _y, float _r, float _g, float _b, float _s) {
        x = _x;
        y = _y;
        r = _r;
        g = _g;
        b = _b;
        s = _s;
    }

    Point() = default;
    ~Point() = default;

    void drawp() {
        glColor3f(r, g, b);
        glPointSize(s);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }
};


class Pen {
public:
    float x;
    float y;
    float r;
    float g;
    float b;
    float thickness = 1.0f;
    bool pressed = false;
    bool color_reset = false;

    Pen() = default;
    ~Pen() = default;
};


class Controller : public AppController {
    Texture pencil;
    Texture eraser;
    Texture clear;
    Colors blue;
    Colors green;
    Colors red;
    Colors black;
    Colors yellow;
    Colors orange;
    Colors pink;
    Colors purple;
    Colors brown;
    Colors gray;
    Colors cyan;
    Colors magenta;
    Colors coral;
    Colors gold;
    Button thicker;
    Button thinner;

    Pen pen;

    std::vector<Point> points; 

public:
Controller(){
    // Initialize your state variables
    pencil = Texture(-1.0f, 1.0f, 0.2f, 0.2f, "assets/pencil.png");
    eraser = Texture(-1.0f, 0.8f, 0.2f, 0.2f, "assets/eraser.png");
    clear = Texture(-1.0f, 0.6f, 0.2f, 0.2f, "assets/cleartext.png");
    black = Colors(-1.0f, 0.4f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f);
    blue = Colors(-0.9f, 0.4f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f);
    red = Colors(-1.0f, 0.3f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f);
    green = Colors(-0.9f, 0.3f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f);
    pink = Colors(-1.0f, 0.2f, 0.1f, 0.1f, 0.871f, 0.039f, 0.486f);
    yellow = Colors(-0.9f, 0.2f, 0.1f, 0.1f, 1.0f, 0.882f, 0.0f);
    orange = Colors(-1.0f, 0.1f, 0.1f, 0.1f, 1.0f, 0.353f, 0.0f);
    brown = Colors(-0.9f, 0.1f, 0.1f, 0.1f, 0.294f, 0.161f, 0.071f);
    purple = Colors(-1.0f, 0.0f, 0.1f, 0.1f, 0.498f, 0.0f, 0.741f);
    gray = Colors(-0.9f, 0.0f, 0.1f, 0.1f, 0.8f, 0.8f, 0.8f);
    cyan = Colors(-1.0f, -0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f);
    magenta = Colors(-0.9f, -0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 1.0f);
    coral = Colors(-1.0f, -0.2f, 0.1f, 0.1f, 1.0f, 0.5f, 0.31f);
    gold = Colors(-0.9f, -0.2f, 0.1f, 0.1f, 1.0f, 0.843f, 0.0f);

    thicker = Button(-1.0f, -0.3f, "+");
    thinner = Button(-0.9f, -0.3f, "-");
    pencil.selected = true;

    pen.thickness = 12.0f;
    pen.pressed = false;
    pen.color_reset = false;
    pen.r = 0.0f;
    pen.g = 0.0f;
    pen.b = 0.0f;
    black.selected = true;
}

void reset_texture(){
    pencil.selected = false;
    eraser.selected = false;
    clear.selected = false;
}

void reset_color_button() {
    blue.selected = false;
    green.selected = false;
    red.selected = false;
    black.selected = false;
    yellow.selected = false;
    orange.selected = false;
    pink.selected = false;
    purple.selected = false;
    brown.selected = false;
    gray.selected = false;
    cyan.selected = false;
    magenta.selected = false;
    coral.selected = false;
    gold.selected = false;
}

void reset_thickness_button() {
    thicker.pressed = false;
    thinner.pressed = false;
}

void render() {
    // background
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glEnd();

    pencil.draw();
    eraser.draw();
    clear.draw();
    blue.drawc();
    black.drawc();
    green.drawc();
    red.drawc();
    brown.drawc();
    pink.drawc();
    purple.drawc();
    yellow.drawc();
    orange.drawc();
    gray.drawc();
    cyan.drawc();
    magenta.drawc();
    coral.drawc();
    gold.drawc();
    thicker.drawb();
    thinner.drawb();

    for (auto point : points) {
        point.drawp();
    }

    reset_thickness_button();
}

void leftMouseDown(float mx, float my) {
    pen.pressed = true;

    if(pencil.contains(mx, my)){
        reset_texture();
        if (pen.color_reset == true) {
            pen.r = 0.0f;
            pen.g = 0.0f;
            pen.b = 0.0f;
            black.selected = true;
            pen.color_reset = false;
        }
        pencil.selected = true;
    } else if (eraser.contains(mx, my)) {
        reset_texture();
        pen.r = 1.0f;
        pen.g = 1.0f;
        pen.b = 1.0f;
        eraser.selected = true;
        pen.color_reset = true;
        reset_color_button();
    } else if(clear.contains(mx, my)){
        points.clear();
        reset_texture();
        clear.selected = true;
    }

    if(pencil.selected == true){
        if (blue.contains(mx, my)) {
            reset_color_button();
            blue.selected = true;
            pen.r = 0.0f;
            pen.g = 0.0f;
            pen.b = 1.0f;
        } else if (green.contains(mx, my)) {
            reset_color_button();
            green.selected = true;
            pen.r = 0.0f;
            pen.g = 1.0f;
            pen.b = 0.0f;
        } else if (red.contains(mx, my)) {
            reset_color_button();
            red.selected = true;
            pen.r = 1.0f;
            pen.g = 0.0f;
            pen.b = 0.0f;
        } else if (black.contains(mx, my)) {
            reset_color_button();
            black.selected = true;
            pen.r = 0.0f;
            pen.g = 0.0f;
            pen.b = 0.0f;
        } else if (yellow.contains(mx, my)) {
            reset_color_button();
            yellow.selected = true;
            pen.r = 1.0f;
            pen.g = 0.882f;
            pen.b = 0.0f;
        } else if (orange.contains(mx, my)) {
            reset_color_button();
            orange.selected = true;
            pen.r = 1.0f;
            pen.g = 0.353f;
            pen.b = 0.0f;
        } else if (pink.contains(mx, my)) {
            reset_color_button();
            pink.selected = true;
            pen.r = 0.871f;
            pen.g = 0.039f;
            pen.b = 0.486f;
        } else if (purple.contains(mx, my)) {
            reset_color_button();
            purple.selected = true;
            pen.r = 0.498f;
            pen.g = 0.0f;
            pen.b = 0.741f;
        } else if (brown.contains(mx, my)) {
            reset_color_button();
            brown.selected = true;
            pen.r = 0.294f;
            pen.g = 0.161f;
            pen.b = 0.071f;
        } else if (gray.contains(mx, my)) {
            reset_color_button();
            gray.selected = true;
            pen.r = 0.8f;
            pen.g = 0.8f;
            pen.b = 0.8f;
        } else if (cyan.contains(mx, my)) {
            reset_color_button();
            cyan.selected = true;
            pen.r = 0.0f;
            pen.g = 1.0f;
            pen.b = 1.0f;
        } else if (magenta.contains(mx, my)) {
            reset_color_button();
            magenta.selected = true;
            pen.r = 1.0f;
            pen.g = 0.0f;
            pen.b = 1.0f;
        } else if (coral.contains(mx, my)) {
            reset_color_button();
            coral.selected = true;
            pen.r = 1.0f;
            pen.g = 0.5f;
            pen.b = 0.31f;
        } else if (gold.contains(mx, my)) {
            reset_color_button();
            gold.selected = true;
            pen.r = 1.0f;
            pen.g = 0.843f;
            pen.b = 0.0f;
        } else if (thicker.contains(mx, my)) {
            thicker.pressed = true;
            if (pen.thickness < 60.0f) {
                pen.thickness += 5.0f;
            }
        } else if (thinner.contains(mx, my)) {
            thinner.pressed = true;
            if (pen.thickness > 5.0f) {
                pen.thickness -= 5.0f;
            }
        }
    }
}

void mouseMotion(float x, float y){
    if(pen.pressed == true){
        if(y > -0.4f && x < -0.8f){
        } else {
            points.push_back(Point(x, y, pen.r, pen.g, pen.b, pen.thickness));
        }
    }
}

void leftMouseUp(float x, float y){
    pen.pressed = false;

    if (clear.selected) {
        clear.selected = false;
        pencil.selected = true;
    }
}

    
~Controller(){
    // Release memory
}
};

#endif