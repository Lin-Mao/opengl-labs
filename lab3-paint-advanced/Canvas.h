#ifndef CANVAS_H
#define CANVAS_H

#include "Rectangle.h"
#include "Point.h"
#include "Color.h"
#include <vector>

class Canvas {
private:
    Rectangle area;
    std::vector<Point> points;
    float size = 7.0f;

public:
    Canvas() {
        area = Rectangle(-0.8f, 1.0f, 1.8f, 1.8f, 1.0f, 1.0f, 1.0f);
    }

    void draw() {
        area.draw();

        for (int i = 0; i < points.size(); i++) {
            points[i].draw();
        }
    }

    void handleMouseClick(float mx, float my, Color color) {
        points.push_back(Point(mx, my, color.getR(), color.getG(), color.getB(), size));
    }

    void handleMouseMotion(float mx, float my, Color color) {
        points.push_back(Point(mx, my, color.getR(), color.getG(), color.getB(), size));

    }

    bool contains(float mx, float my) {
        return area.contains(mx, my);
    }

    void clear() {
        points.clear();
    }

    void sizePlus() {
        if (size < 60.0f) {
            size += 5.0f;
        }
    }

    void sizeMinus() {
        if (size > 5.0f) {
            size -= 5.0f;
        }
    }
};

#endif