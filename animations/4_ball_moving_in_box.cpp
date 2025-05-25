#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

#define PI 3.14159

int roundVal(float x) {
    return (int)(x + 0.5);
}

void ddaLine(int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(roundVal(x), roundVal(y), color);
        x += x_inc;
        y += y_inc;
    }
}

void midpointLine(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        putpixel(x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void bresenhamLine(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1) {
        putpixel(x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int cx = 320, cy = 240;
    float r = 10;
    int angle = 0, direction = 1;

    int prev_x = cx + r * cos(angle * PI / 180);
    int prev_y = cy + r * sin(angle * PI / 180);

    while (!kbhit()) {
        cleardevice();

        int x = cx + r * cos(angle * PI / 180);
        int y = cy + r * sin(angle * PI / 180);

        // Draw the spiral path as a line segment from previous point to current
        // Choose the line algorithm to draw the spiral path:
        ddaLine(prev_x, prev_y, x, y, WHITE);
        // midpointLine(prev_x, prev_y, x, y, WHITE);
        // bresenhamLine(prev_x, prev_y, x, y, WHITE);

        // Draw the circle at current position
        circle(x, y, 10);

        // Update previous point to current for next iteration
        prev_x = x;
        prev_y = y;

        angle += direction * 5;
        r += direction * 0.5;

        if (r >= 150 || r <= 10)
            direction *= -1;

        delay(50);
    }

    getch();
    closegraph();
}
