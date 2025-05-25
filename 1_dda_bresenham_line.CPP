#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h> // Required for abs() in C

// Define TRUE and FALSE for C (since true/false keywords are C++ specific)
#define TRUE 1
#define FALSE 0

void drawLineDDA(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float s = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xInc = dx / s;
    float yInc = dy / s;

    float x = x1;
    float y = y1;
    
    int i;
    for (i = 0; i <= s; i++) {
        putpixel((int)(x + 0.5), (int)(y + 0.5), WHITE);
        x += xInc;
        y += yInc;
    }
}

void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1;
    int y = y1;

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (TRUE) {
        putpixel(x, y, WHITE);
        if (x == x2 && y == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2, choice;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); // ** IMPORTANT: Change this path to your BGI directory **



    printf("Enter the starting point (x1 y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter the ending point (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    printf("\nChoose the Line Drawing Algorithm:\n");
    printf("1. DDA Algorithm\n");
    printf("2. Bresenham's Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        drawLineDDA(x1, y1, x2, y2);
    } else if (choice == 2) {
        drawLineBresenham(x1, y1, x2, y2);
    } else {
        printf("Invalid choice!\n");
    }

    getch();
    closegraph();
    return 0;
}