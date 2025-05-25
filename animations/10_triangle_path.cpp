#include <graphics.h>
#include <conio.h>
#include <dos.h>

int roundVal(float x) {
    return (int)(x + 0.5);
}

// DDA Line Drawing function
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

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    ddaLine(x1, y1, x2, y2, color);
    ddaLine(x2, y2, x3, y3, color);
    ddaLine(x3, y3, x1, y1, color);
}

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int x1 = 200, y1 = 300;
    int x2 = 400, y2 = 300;
    int x3 = 300, y3 = 120;

    float t;
    int cx, cy;
    int offset = 10;

    while (!kbhit()) {
        // Clockwise movement

        // Bottom line left to right
        for (t = 0.0; t <= 1.0; t += 0.01) {
            cleardevice();
            drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);

            cx = x1 + (x2 - x1) * t;
            cy = y1 + offset;

            circle(cx, cy, 5);
            delay(10);
        }

        // Right edge upward
        for (t = 0.0; t <= 1.0; t += 0.01) {
            cleardevice();
            drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);

            cx = x2 + (x3 - x2) * t;
            cy = y2 + (y3 - y2) * t - offset;

            circle(cx, cy, 5);
            delay(10);
        }

        // Left edge downward
        for (t = 0.0; t <= 1.0; t += 0.01) {
            cleardevice();
            drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);

            cx = x3 + (x1 - x3) * t;
            cy = y3 + (y1 - y3) * t - offset;

            circle(cx, cy, 5);
            delay(10);
        }

        // Anticlockwise movement

        // Left edge upward
        for (t = 1.0; t >= 0.0; t -= 0.01) {
            cleardevice();
            drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);

            cx = x3 + (x1 - x3) * t;
            cy = y3 + (y1 - y3) * t - offset;

            circle(cx, cy, 5);
            delay(10);
        }

        // Right edge downward
        for (t = 1.0; t >= 0.0; t -= 0.01) {
            cleardevice();
            drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);

            cx = x2 + (x3 - x2) * t;
            cy = y2 + (y3 - y2) * t - offset;

            circle(cx, cy, 5);
            delay(10);
        }

        // Bottom line right to left
        for (t = 1.0; t >= 0.0; t -= 0.01) {
            cleardevice();
            drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);

            cx = x1 + (x2 - x1) * t;
            cy = y1 + offset;

            circle(cx, cy, 5);
            delay(10);
        }
    }

    getch();
    closegraph();
}
