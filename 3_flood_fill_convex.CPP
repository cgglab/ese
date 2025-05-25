#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>

void scanlineFill(int x, int y, int fillColor, int boundaryColor) {
    int currentX, leftX, rightX;
    int currentColor;

    do {
        currentColor = getpixel(x, y);
        if (currentColor != boundaryColor && currentColor != fillColor) {
            // Move to the leftmost pixel in this scanline
            leftX = x;
            while (getpixel(leftX - 1, y) != boundaryColor && getpixel(leftX - 1, y) != fillColor) {
                leftX--;
            }

            // Move to the rightmost pixel in this scanline
            rightX = x;
            while (getpixel(rightX + 1, y) != boundaryColor && getpixel(rightX + 1, y) != fillColor) {
                rightX++;
            }

            // Fill the scanline
            for (currentX = leftX; currentX <= rightX; currentX++) {
                putpixel(currentX, y, fillColor);
                delay(0); // Adjust delay if needed
            }

            // Check the scanlines above and below
            for (currentX = leftX; currentX <= rightX; currentX++) {
                if (getpixel(currentX, y - 1) != boundaryColor && getpixel(currentX, y - 1) != fillColor) {
                    scanlineFill(currentX, y - 1, fillColor, boundaryColor);
                }
                if (getpixel(currentX, y + 1) != boundaryColor && getpixel(currentX, y + 1) != fillColor) {
                    scanlineFill(currentX, y + 1, fillColor, boundaryColor);
                }
            }
        }
    } while (0);
}

void main() {
    int gd = DETECT, gm;
    int n, i, x[20], y[20], poly[40];
    int seedX, seedY, fillColor, boundaryColor = 15;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter number of vertices of the convex polygon (max 20): ");
    scanf("%d", &n);

    printf("Enter coordinates of vertices (x y):\n");
    for (i = 0; i < n; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%d%d", &x[i], &y[i]);
        poly[2 * i] = x[i];
        poly[2 * i + 1] = y[i];
    }
    poly[2 * n] = x[0];     // Close the polygon
    poly[2 * n + 1] = y[0];

    setcolor(boundaryColor);
    drawpoly(n + 1, poly);

    printf("Enter seed point inside the polygon (x y): ");
    scanf("%d%d", &seedX, &seedY);

    printf("Enter fill color (1-14): ");
    scanf("%d", &fillColor);

    scanlineFill(seedX, seedY, fillColor, boundaryColor);

    getch();
    closegraph();
}
