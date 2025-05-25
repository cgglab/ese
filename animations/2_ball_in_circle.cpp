#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <dos.h>

#define PI 3.1416

// Midpoint Circle Algorithm to draw circle at (xc,yc) with radius r
void midpointCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r;

    // Plot all eight octants
    while (x <= y) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int R = 100, r = 10, x = 300, y = 250;
    double angle = 0;
    int direction = 1;

    while (!kbhit()) {
        cleardevice();

        // Draw big circle using Midpoint Circle Algorithm
        midpointCircle(x, y, R);

        // Calculate small ball position
        int cx = x + (R - 15) * cos(angle * PI / 180);
        int cy = y + (R - 15) * sin(angle * PI / 180);

        // Draw small circle using Midpoint Circle Algorithm
        midpointCircle(cx, cy, r);

        // Update angle
        angle += direction * 2;
        if (angle >= 360 || angle <= 0)
            direction *= -1;  // Change direction

        delay(30);
    }

    getch();
    closegraph();
}
