#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <math.h>

// DDA Line Drawing Function
void ddaLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        putpixel((int)x, (int)y, WHITE);
        x += Xinc;
        y += Yinc;
    }
}

// Midpoint Circle Drawing Function
void midpointCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    while (x <= y) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        x++;
        if (p < 0)
            p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int x1 = 150, y1 = 300;
    int x2 = 400, y2 = 300;
    int x3 = x2, y3 = 100;

    float t;
    int cx, cy;

    while (!kbhit()) {
        for (t = 0.0; t <= 1.0; t += 0.01) {
            cx = x3 + (x1 - x3) * t;
            cy = y3 + (y1 - y3) * t;

            // Draw Triangle using DDA
            ddaLine(x1, y1, x2, y2);
            ddaLine(x2, y2, x3, y3);
            ddaLine(x3, y3, x1, y1);

            // Draw Circle using Midpoint Algorithm
            midpointCircle(cx, cy, 5);

            delay(20);
            cleardevice();
        }
    }

    getch();
    closegraph();
}
