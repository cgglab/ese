#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 100000

// Structure for stack elements
typedef struct {
    int x, y;
} Point;

// Stack implementation
Point stack[MAX_STACK];
int top = -1;

void push(int x, int y) {
    if (top < MAX_STACK - 1) {
        top++;
        stack[top].x = x;
        stack[top].y = y;
    }
}

Point pop() {
    Point p = {-1, -1};
    if (top >= 0) {
        p = stack[top];
        top--;
    }
    return p;
}

int isEmpty() {
    return top == -1;
}

// Non-recursive flood fill function
void floodFill(int x, int y, int oldColor, int newColor) {
    push(x, y);

    while (!isEmpty()) {
        Point p = pop();
        int px = p.x;
        int py = p.y;

        if (getpixel(px, py) == oldColor) {
            putpixel(px, py, newColor);

            // Push neighboring pixels
            push(px + 1, py);
            push(px - 1, py);
            push(px, py + 1);
            push(px, py - 1);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int n, i;
    int x[20], y[20];

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter number of vertices of the convex polygon: ");
    scanf("%d", &n);

    // Accept vertices
    for (i = 0; i < n; i++) {
        printf("Enter coordinates of vertex %d (x y): ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    // Draw polygon
    for (i = 0; i < n - 1; i++) {
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }
    line(x[n - 1], y[n - 1], x[0], y[0]);

    int seedX, seedY;
    printf("Enter seed point inside the polygon (x y): ");
    scanf("%d %d", &seedX, &seedY);

    int oldColor = getpixel(seedX, seedY);
    int newColor = 4; // Red

    floodFill(seedX, seedY, oldColor, newColor);

    getch();
    closegraph();
    return 0;
}
