#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>

// Define TRUE and FALSE for older compilers if 'true' and 'false' are undefined
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// Helper function to draw 8 symmetric points of a circle
void draw8SymmetricPoints(int xc, int yc, int x, int y) {
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
    putpixel(xc + y, yc + x, WHITE);
    putpixel(xc - y, yc + x, WHITE);
    putpixel(xc + y, yc - x, WHITE);
    putpixel(xc - y, yc - x, WHITE);
}

// Function for Bresenham's Circle Drawing Algorithm
void drawCircleBresenham(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - (2 * r); // Initial decision parameter

    // Draw the initial 8 symmetric points
    draw8SymmetricPoints(xc, yc, x, y);

    while (x <= y) {
        if (d < 0) { // Midpoint is inside the circle (choose E)
            d = d + (4 * x) + 6;
        } else { // Midpoint is outside or on the circle (choose SE)
            d = d + (4 * (x - y)) + 10;
            y--; // Decrement y
        }
        x++; // Always increment x

        draw8SymmetricPoints(xc, yc, x, y);
    }
}

// Function for Midpoint Circle Drawing Algorithm
void drawCircleMidpoint(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int p = 1 - r; // Initial decision parameter

    // Draw the initial 8 symmetric points
    draw8SymmetricPoints(xc, yc, x, y);

    while (x <= y) {
        x++; // Always increment x
        if (p < 0) { // Midpoint is inside the circle (choose E)
            p = p + (2 * x) + 1;
        } else { // Midpoint is outside or on the circle (choose SE)
            y--; // Decrement y
            p = p + (2 * x) + 1 - (2 * y);
        }
        draw8SymmetricPoints(xc, yc, x, y);
    }
}

int main() {
    // ALL variable declarations MUST be at the very beginning of the function
    int gd = DETECT, gm;
    int xc, yc, r, choice; // MOVED these declarations here!

    // IMPORTANT: Change this path to your BGI directory (e.g., "C:\\TURBOC3\\BGI")
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter the center coordinates (xc yc): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter the radius (r): ");
    scanf("%d", &r);

    printf("\nChoose the Circle Drawing Algorithm:\n");
    printf("1. Bresenham's Algorithm\n");
    printf("2. Midpoint Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        drawCircleBresenham(xc, yc, r);
    } else if (choice == 2) {
        drawCircleMidpoint(xc, yc, r);
    } else {
        printf("Invalid choice!\n");
    }

    getch(); // Wait for a key press to close the graphics window
    closegraph(); // Close the graphics mode
    return 0;
}