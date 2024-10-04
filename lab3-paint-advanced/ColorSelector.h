#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include "Rectangle.h"
#include "Color.h"

class ColorSelector {
private:
    Rectangle area;
    Rectangle red;
    Rectangle green;
    Rectangle blue;
    Rectangle pink;
    Rectangle purple;
    Rectangle orange;
    Rectangle black;

public:   
    ColorSelector() {
        area = Rectangle(-0.8f, -0.8f, 1.8f, 0.2f, 0.8f, 0.8f, 0.8f);
        red = Rectangle(-0.8f, -0.8f, 0.2f, 0.2f, 1.0f, 0.0f, 0.0f);
        green = Rectangle(-0.6f, -0.8f, 0.2f, 0.2f, 0.0f, 1.0f, 0.0f);
        blue = Rectangle(-0.4f, -0.8f, 0.2f, 0.2f, 0.0f, 0.0f, 1.0f);
        pink = Rectangle(-0.2f, -0.8f, 0.2f, 0.2f, 1.0f, 0.0f, 1.0f);
        purple = Rectangle(0.0f, -0.8f, 0.2f, 0.2f, 0.5f, 0.0f, 1.0f);
        orange = Rectangle(0.2f, -0.8f, 0.2f, 0.2f, 1.0f, 0.5f, 0.0f);
        black = Rectangle(0.4f, -0.8f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f);
        red.select();        
    }

    void deselectAll() {
        red.deselect();
        green.deselect();
        blue.deselect();
        pink.deselect();
        purple.deselect();
        orange.deselect();
        black.deselect();
    }

    void draw() {
        area.draw();
        red.draw();
        green.draw();
        blue.draw();
        pink.draw();
        purple.draw();
        orange.draw();
        black.draw();
        
    }

    void handleMouseClick(float mx, float my, Color& color) {
        if (red.contains(mx, my)) {
            deselectAll();
            red.select();
            color.makeRed();
        }
        else if (green.contains(mx, my)) {
            deselectAll();
            green.select();
            color.makeGreen();

        }
        else if (blue.contains(mx, my)) {
            deselectAll();
            blue.select();
            color.makeBlue();
        }
        else if (pink.contains(mx, my)) {
            deselectAll();
            pink.select();
            color.makePink();
        }
        else if (purple.contains(mx, my)) {
            deselectAll();
            purple.select();
            color.makePurple();
        }
        else if (orange.contains(mx, my)) {
            deselectAll();
            orange.select();
            color.makeOrange();
        }
        else if (black.contains(mx, my)) {
            deselectAll();
            black.select();
            color.makeBlack();
        }
    }

    bool contains(float mx, float my) {
        return area.contains(mx, my);
    }

    void makeRed() {
        red.select();
    }
};

#endif