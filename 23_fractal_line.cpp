#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // for rand()
#include <dos.h>     // for delay()

#define MAX_POINTS 2048  // Maximum points for 10 iterations (2^10 + 1)

struct Point {
    float x, y;
};

// Recursive function to generate midpoint displaced fractal line
void fractalLine(struct Point *pts, int left, int right, int depth, float displacement) {
    if (depth == 0 || (right - left) <= 1)
        return;

    int mid = (left + right) / 2;

    pts[mid].x = (pts[left].x + pts[right].x) / 2;
    pts[mid].y = (pts[left].y + pts[right].y) / 2;

    pts[mid].y += (rand() % 100 - 50) * displacement;  // Random vertical displacement

    fractalLine(pts, left, mid, depth - 1, displacement / 2);
    fractalLine(pts, mid, right, depth - 1, displacement / 2);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int totalPoints, iterations, i;
    struct Point points[MAX_POINTS];

    // First, ask for endpoints
    printf("Enter start point (x y): ");
    scanf("%f %f", &points[0].x, &points[0].y);

    printf("Enter end point (x y): ");
    scanf("%f %f", &points[1].x, &points[1].y);  // Temporarily store in points[1]

    // Then ask for iterations
    printf("Enter number of iterations (1 to 10): ");
    scanf("%d", &iterations);

    if (iterations < 1 || iterations > 10) {
        printf("Invalid input. Using 5 iterations.\n");
        iterations = 5;
    }

    totalPoints = (1 << iterations) + 1;  // 2^n + 1

    // Copy endpoints to proper locations for the fractal
    points[totalPoints - 1] = points[1];

    // Initialize random number generator
    randomize();

    // Generate the fractal line
    fractalLine(points, 0, totalPoints - 1, iterations, 50);

    // Draw the fractal line
    setcolor(WHITE);
    for (i = 0; i < totalPoints - 1; i++) {
        line((int)points[i].x, (int)points[i].y, (int)points[i+1].x, (int)points[i+1].y);
        delay(10);
    }

    getch();
    closegraph();
    return 0;
}