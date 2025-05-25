#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#define PI 3.14159265

// DDA line drawing algorithm
void ddaLine(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x0, y = y0;

    for (int i = 0; i <= steps; i++) {
        putpixel((int)(x + 0.5), (int)(y + 0.5), WHITE);
        x += xInc;
        y += yInc;
    }
}

// Midpoint circle drawing algorithm
void midpointCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 1 - r;

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

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int cx = 320, cy = 100, len = 150;
    float angle;

    for (int j = 0; j < 3; j++) {  // Repeat animation 3 times
        // Swing right
        for (angle = -45; angle <= 45; angle += 5) {
            cleardevice();
            float rad = angle * PI / 180;
            int x = cx + len * sin(rad);
            int y = cy + len * cos(rad);

            ddaLine(cx, cy, x, y);        // Draw pendulum string with DDA
            midpointCircle(x, y, 20);     // Draw bob with midpoint circle

            delay(80);
        }
        // Swing left
        for (angle = 45; angle >= -45; angle -= 5) {
            cleardevice();
            float rad = angle * PI / 180;
            int x = cx + len * sin(rad);
            int y = cy + len * cos(rad);

            ddaLine(cx, cy, x, y);        // Draw pendulum string with DDA
            midpointCircle(x, y, 20);     // Draw bob with midpoint circle

            delay(80);
        }
    }

    getch();
    closegraph();
    return 0;
}
