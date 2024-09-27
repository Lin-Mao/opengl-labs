#include <GL/glut.h>
#include <vector>
#include <cmath> // For cos and sin

// g++ cover_the_spot.cpp -o cover_the_spot -lglut -lGL

struct Disk {
    float x, y;
    float radius;
};

std::vector<Disk> disks;
Disk currentDisk;
bool isEasyMode = false;
bool isMouseHeld = false;

void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; ++i) {
        float angle = 2 * 3.14159265 * i / 100;
        float dx = radius * std::cos(angle);  // Use std::cos
        float dy = radius * std::sin(angle);  // Use std::sin
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the red circle
    drawCircle(0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f); // red circle at center

    // Draw placed disks
    for (const auto& disk : disks) {
        drawCircle(disk.x, disk.y, disk.radius, 0.0f, 0.0f, 1.0f); // blue disks
    }

    // Draw current disk in Easy Mode
    if (isEasyMode && isMouseHeld) {
        drawCircle(currentDisk.x, currentDisk.y, currentDisk.radius, 0.0f, 0.0f, 1.0f); // blue
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float mouseX = (x - 250.0f) / 250.0f;  // Convert to OpenGL coordinates
        float mouseY = (250.0f - y) / 250.0f;

        if (!isEasyMode) {
            Disk newDisk = { mouseX, mouseY, 0.1f };  // Add a new disk
            disks.push_back(newDisk);
        } else {
            currentDisk = { mouseX, mouseY, 0.1f };
            isMouseHeld = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (isEasyMode && isMouseHeld) {
            disks.push_back(currentDisk);
            isMouseHeld = false;
        }
    }

    glutPostRedisplay();
}

void motion(int x, int y) {
    if (isEasyMode && isMouseHeld) {
        currentDisk.x = (x - 250.0f) / 250.0f;
        currentDisk.y = (250.0f - y) / 250.0f;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'n': // Normal Mode
            isEasyMode = false;
            break;
        case 'e': // Easy Mode
            isEasyMode = true;
            break;
        case 'u': // Undo
            if (!disks.empty()) {
                disks.pop_back();
            }
            break;
        case 'r': // Restart
            disks.clear();
            break;
    }

    glutPostRedisplay();
}

void setupProjection() {
    // Set up an orthographic projection using glOrtho
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // Orthographic projection, replacing gluOrtho2D
    glMatrixMode(GL_MODELVIEW);  // Switch back to model view matrix
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cover the Spot");

    setupProjection();  // Call to set up the projection matrix

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
