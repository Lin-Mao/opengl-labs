#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "Rectangle.h"
#include "Texture.h"
#include "Color.h"
#include "Canvas.h"
#include "Button.h"
#include "ColorSelector.h"

class Toolbar {
private:
    Rectangle area;
    Texture pencil;
    Texture eraser;
    Texture clear;
    Button size_plus;
    Button size_minus;

public:
    Toolbar() {
        area = Rectangle(-1.0f, 1.0f, 0.2f, 2.0f, 0.8f, 0.8f, 0.8f);
        pencil = Texture(-1.0f, 1.0f, 0.2f, 0.2f, "assets/pencil.png");
        eraser = Texture(-1.0f, 0.8f, 0.2f, 0.2f, "assets/eraser.png");
        clear = Texture(-1.0f, 0.6f, 0.2f, 0.2f, "assets/clear.png");
        size_plus = Button(-1.0f, 0.4f, "+");
        size_minus = Button(-0.9f, 0.4f, "-");
        pencil.select();
    }
    
    void draw() {
        area.draw();
        pencil.draw();
        eraser.draw();
        clear.draw();
        size_plus.draw();
        size_minus.draw();
    }

    void clearSelection() {
        pencil.deselect();
        eraser.deselect();
        clear.deselect();
    }

    void handleMouseClick(float mx, float my, Color& color, ColorSelector& color_sel, Canvas& canvas) {
        if (pencil.contains(mx, my)) {
            clearSelection();
            pencil.select();
            if (color.isErased()) {
                color.makeRed();
                color_sel.makeRed();
                color.resetErased(false);
            }
        } else if (eraser.contains(mx, my)) {
            clearSelection();
            eraser.select();
            color.makeEraser();
            color_sel.deselectAll();
            color.resetErased(true);
        } else if (clear.contains(mx, my)) {
            clearSelection();
            clear.select();
            canvas.clear();
        } else if (size_plus.contains(mx, my)) {
            size_plus.select();
            canvas.sizePlus();
        } else if (size_minus.contains(mx, my)) {
            size_minus.select();
            canvas.sizeMinus();
        }
    }

    void handleMouseRelease(float mx, float my, Color& color, ColorSelector& color_sel) {
        if (clear.contains(mx, my)) {
            clearSelection();
            pencil.select();
            if (color.isErased()) {
                color.makeRed();
                color_sel.makeRed();
                color.resetErased(false);
            }
        } else if (size_plus.contains(mx, my)) {
            size_plus.deselect();
            size_minus.deselect();
        } else if (size_minus.contains(mx, my)) {
            size_minus.deselect();
            size_plus.deselect();
        }
    }

    bool contains(float mx, float my) {
        return area.contains(mx, my);
    }
};

#endif