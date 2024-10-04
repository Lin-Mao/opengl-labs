#ifndef COLOR_H
#define COLOR_H

class Color {
private:
    float r;
    float g;
    float b;
    bool is_erased;

public:
    Color() {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
        is_erased = false;
    }

    Color(float _r, float _g, float _b) {
        r = _r;
        g = _g;
        b = _b;
        is_erased = false;
    }

    void setRGB(float _r, float _g, float _b) {
        r = _r;
        g = _g;
        b = _b;
    }

    // getters
    float getR() {
        return r;
    }

    float getG() {
        return g;
    }

    float getB() {
        return b;
    }

    // setters
    void makeRed() {
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
    }

    void makeGreen() {
        r = 0.0f;
        g = 1.0f;
        b = 0.0f;
    }

    void makeBlue() {
        r = 0.0f;
        g = 0.0f;
        b = 1.0f;
    }
    void makePink() {
        r = 1.0f;
        g = 0.0f;
        b = 1.0f;
    }
    void makePurple() {
        r = 0.5f;
        g = 0.0f;
        b = 1.0f;
    }
    void makeOrange() {
        r = 1.0f;
        g = 0.5f;
        b = 0.0f;
    }
    void makeBlack() {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }
    void makeEraser() {
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
    }

    bool isErased() {
        return is_erased;
    }

    void resetErased(bool erased) {
        is_erased = erased;
    }
};

#endif