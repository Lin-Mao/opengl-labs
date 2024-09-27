#include <GL/freeglut.h>
#include <vector>
#include <iostream>
#include <cstring>

// Define colors for the color selector
GLfloat colors[7][3] = {
    {1.0f, 0.0f, 0.0f}, // Red
    {0.0f, 1.0f, 0.0f}, // Green
    {0.0f, 0.0f, 1.0f}, // Blue
    {1.0f, 1.0f, 0.0f}, // Yellow
    {1.0f, 0.0f, 1.0f}, // Magenta
    {0.0f, 1.0f, 1.0f}, // Cyan
    {0.0f, 0.0f, 0.0f}  // Black
};

// Structure to hold data for each point drawn on the canvas
struct Point {
    GLfloat x, y;       // Coordinates of the point
    GLfloat color[3];   // Color of the point
    GLfloat size;       // Size (stroke thickness) of the point
};

// Vector to store the points drawn on the canvas
std::vector<Point> points;

// Application state variables
bool isPainting = false; // Indicates whether the user is painting
bool eraser = false;     // Indicates whether the eraser tool is selected
int selectedColor = 0;   // Index of the currently selected color
GLfloat strokeSize = 5.0f; // Current stroke size (default 5)
int strokeSizes[3] = {5, 10, 20}; // Array storing possible stroke sizes (small, medium, large)

// Function to render text on the screen
void renderBitmapString(float x, float y, const char* string) {
    glRasterPos2f(x, y);  // Set the position where the text will appear
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Render each character of the string
    }
}

// Function to draw a button with a black outline
void drawButtonWithOutline(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    // Draw the button (filled rectangle)
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    // Draw the black outline around the button
    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glLineWidth(2.0f);  // Set the line thickness
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Function to draw the user interface (buttons and labels)
void drawUI() {
    // Set the fill color for buttons
    glColor3f(0.8f, 0.8f, 0.8f);  // Light gray color for buttons

    // Draw the buttons for Paint, Eraser, Clear screen, Stroke sizes, and Colors

    // Paint button
    drawButtonWithOutline(-1.0f, 0.75f, -0.88f, 0.88f);

    // Erase button
    drawButtonWithOutline(-0.86f, 0.75f, -0.74f, 0.88f);

    // Clear screen button
    drawButtonWithOutline(-0.72f, 0.75f, -0.60f, 0.88f);

    // Stroke size buttons (small, medium, large)
    drawButtonWithOutline(-0.58f, 0.75f, -0.46f, 0.88f); // Small stroke
    drawButtonWithOutline(-0.44f, 0.75f, -0.32f, 0.88f); // Medium stroke
    drawButtonWithOutline(-0.30f, 0.75f, -0.18f, 0.88f); // Large stroke

    // Color selection buttons
    for (int i = 0; i < 7; i++) {
        glColor3fv(colors[i]);  // Set the color for the button
        drawButtonWithOutline(-0.16f + i * 0.16f, 0.75f, -0.04f + i * 0.16f, 0.88f);
    }

    // Render text labels for the buttons
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for text

    // Labels for Paint, Eraser, and Clear screen
    renderBitmapString(-0.96f, 0.7f, "Paint");
    renderBitmapString(-0.82f, 0.7f, "Eraser");
    renderBitmapString(-0.68f, 0.7f, "Clear");

    // Labels for Stroke size buttons
    renderBitmapString(-0.54f, 0.7f, "Small");
    renderBitmapString(-0.40f, 0.7f, "Medium");
    renderBitmapString(-0.26f, 0.7f, "Large");

    // Labels for Color selection buttons
    for (int i = 0; i < 7; i++) {
        char colorLabel[10];
        snprintf(colorLabel, sizeof(colorLabel), "Color %d", i + 1);
        renderBitmapString(-0.14f + i * 0.16f, 0.7f, colorLabel);
    }
}

// Function to draw all the points (painted or erased) on the canvas
void drawPoints() {
    for (auto &p : points) {
        glColor3fv(p.color);     // Set the color of the point
        glPointSize(p.size);      // Set the size (thickness) of the point
        glBegin(GL_POINTS);       // Begin drawing the point
        glVertex2f(p.x, p.y);     // Specify the coordinates of the point
        glEnd();                  // End drawing
    }
}

// Function to handle rendering
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the UI buttons and the points on the canvas
    drawUI();
    drawPoints();

    glutSwapBuffers();  // Swap buffers to update the screen
}

// Mouse click handler
void mouse(int button, int state, int x, int y) {
    // Convert screen coordinates to normalized device coordinates (-1 to 1)
    GLfloat fx = (GLfloat)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0f;
    GLfloat fy = 1.0f - (GLfloat)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2);

    // Handle button press
    if (state == GLUT_DOWN) {
        // Check if a button in the UI area is clicked
        if (fy > 0.75f) { // Only detect clicks in the UI area (top 25% of the screen)
            if (fx > -1.0f && fx < -0.88f) {
                eraser = false; // Select Paint tool
            } else if (fx > -0.86f && fx < -0.74f) {
                eraser = true;  // Select Eraser tool
            } else if (fx > -0.72f && fx < -0.60f) {
                points.clear(); // Clear the canvas
            } else if (fx > -0.58f && fx < -0.46f) {
                strokeSize = strokeSizes[0]; // Select Small stroke
            } else if (fx > -0.44f && fx < -0.32f) {
                strokeSize = strokeSizes[1]; // Select Medium stroke
            } else if (fx > -0.30f && fx < -0.18f) {
                strokeSize = strokeSizes[2]; // Select Large stroke
            } else {
                // Handle color selection
                for (int i = 0; i < 7; i++) {
                    if (fx > (-0.16f + i * 0.16f) && fx < (-0.04f + i * 0.16f)) {
                        selectedColor = i; // Select the color
                    }
                }
            }
        } else {
            isPainting = true; // Start painting on the canvas
        }
    } else if (state == GLUT_UP) {
        isPainting = false; // Stop painting when mouse is released
    }
}

// Mouse motion handler (when dragging)
void motion(int x, int y) {
    if (isPainting) {
        // Convert screen coordinates to normalized device coordinates (-1 to 1)
        GLfloat fx = (GLfloat)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0f;
        GLfloat fy = 1.0f - (GLfloat)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2);

        // Create a new point and set its properties (position, color, size)
        Point p;
        p.x = fx;
        p.y = fy;
        p.size = strokeSize;

        // Set the color of the point based on the current tool (paint or eraser)
        if (eraser) {
            p.color[0] = p.color[1] = p.color[2] = 1.0f; // White color for eraser
        } else {
            p.color[0] = colors[selectedColor][0];
            p.color[1] = colors[selectedColor][1];
            p.color[2] = colors[selectedColor][2];
        }

        points.push_back(p); // Add the point to the list of points
        glutPostRedisplay(); // Request a screen update
    }
}

// Initialization function (sets up the initial OpenGL state)
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set the background color to white
    glColor3f(0.0, 0.0, 0.0);         // Set the default drawing color to black
    glPointSize(5.0);                 // Set the default point size (stroke size)
    glMatrixMode(GL_PROJECTION);      // Set the projection matrix mode
    glLoadIdentity();                 // Reset the projection matrix
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set the coordinate system (orthographic projection)
}

// Main function
int main(int argc, char** argv) {
    // Initialize the GLUT library
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Use double buffering and RGB color mode
    
    // Set the initial window size (1000x800 pixels)
    glutInitWindowSize(1000, 800);
    
    // Create a window with the title "Simple Paint Application"
    glutCreateWindow("Simple Paint Application");

    // Initialize OpenGL settings
    init();

    // Register callback functions
    glutDisplayFunc(display); // Function to handle display rendering
    glutMouseFunc(mouse);     // Function to handle mouse clicks
    glutMotionFunc(motion);   // Function to handle mouse dragging

    // Enter the GLUT event processing loop
    glutMainLoop();

    return 0;
}
