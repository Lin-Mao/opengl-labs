#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <GL/freeglut.h>
#include "AppController.h"
#include "Toolbar.h"
#include "ColorSelector.h"
#include "Canvas.h"

class Controller : public AppController {
    Color color = Color(1.0f, 0.0f, 0.0f);
    Toolbar toolbar;
    ColorSelector colorSelector;
    Canvas canvas;

public:
    Controller(){
        // Initialize your state variables
    }

    void render() {
        // Render some graphics
        toolbar.draw();
        colorSelector.draw();
        canvas.draw();
    }

    void leftMouseDown(float mx, float my) {
        if (toolbar.contains(mx, my)) {
            toolbar.handleMouseClick(mx, my, color, colorSelector, canvas);
        }

        if (colorSelector.contains(mx, my)) {
            colorSelector.handleMouseClick(mx, my, color);
        }

        if (canvas.contains(mx, my)) {
            canvas.handleMouseClick(mx, my, color);
        }
    }

    void mouseMotion(float mx, float my) {
        if (canvas.contains(mx, my)) {
            canvas.handleMouseMotion(mx, my, color);
        }
    }

    void leftMouseUp(float mx, float my) {
        if (toolbar.contains(mx, my)) {
            toolbar.handleMouseRelease(mx, my, color, colorSelector);
        }
    }

    ~Controller(){
        // Release memory
    }
};

#endif