#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>  // For sin, cos
#include <dos.h>   // For delay

// Define PI for calculations
#define PI 3.14159265

// Structure to represent a point
struct P {
    int x, y;
};

// Function to draw the Koch curve recursively
void koch(struct P p1, struct P p2, int it) {
    // Base case: if iterations are 0, draw a straight line segment
    if (it == 0) {
        line(p1.x, p1.y, p2.x, p2.y);
        return;
    }

    // Calculate the length of the segment
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    // Calculate the three points that divide the segment into four
    struct P q1, q2, q3;
    
    // q1: first point (1/3 of the way from p1 to p2)
    q1.x = p1.x + dx / 3;
    q1.y = p1.y + dy / 3;

    // q2: third point (2/3 of the way from p1 to p2)
    q2.x = p1.x + 2 * dx / 3;
    q2.y = p1.y + 2 * dy / 3;

    // q3: the peak of the equilateral triangle
    q3.x = q1.x + (q2.x - q1.x) * cos(PI / 3) - (q2.y - q1.y) * sin(PI / 3);
    q3.y = q1.y + (q2.x - q1.x) * sin(PI / 3) + (q2.y - q1.y) * cos(PI / 3);

    // Recursively call koch for the four new segments
    koch(p1, q1, it - 1); // First segment
    koch(q1, q3, it - 1); // Second segment (bump up)
    koch(q3, q2, it - 1); // Third segment (bump down)
    koch(q2, p2, it - 1); // Fourth segment
}

int main() {
    int gd = DETECT, gm;
    struct P startP, endP;
    int it;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); // Adjust BGI path as needed

    printf("Enter start point of the line (x y): ");
    scanf("%d %d", &startP.x, &startP.y);

    printf("Enter end point of the line (x y): ");
    scanf("%d %d", &endP.x, &endP.y);

    printf("Enter number of iterations (0-3): ");
    scanf("%d", &it);

    // Limit iterations to avoid excessive computation and display issues
    if (it < 0 || it > 3) {
        printf("Invalid iterations. Using 3.\n");
        it = 3;
    }

    cleardevice(); // Clear the screen

    setcolor(WHITE);
    outtextxy(10, 10, "Original Line (White)");
    line(startP.x, startP.y, endP.x, endP.y); // Draw the initial line

    // Small delay to see the original line before drawing the fractal
    delay(1000);
    cleardevice(); // Clear for the fractal

    setcolor(RED);
    outtextxy(10, 10, "Koch Curve (Red)");
    koch(startP, endP, it); // Generate and draw the Koch curve

    getch(); // Wait for a key press
    closegraph(); // Close the graphics mode
    return 0;
}