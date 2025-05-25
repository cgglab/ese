#include <graphics.h>
#include <conio.h>
#include <dos.h>

void drawLineDDA(int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    int prevX = -1, prevY = -1;
    for (int i = 0; i <= steps; i++) {
        int px = (int)(x);
        int py = (int)(y);
        if (px != prevX || py != prevY) {
            putpixel(px, py, color);
            prevX = px; prevY = py;
        }
        x += xInc;
        y += yInc;
    }
}

void drawBox() {
    drawLineDDA(20, 20, 620, 20, WHITE);
    drawLineDDA(620, 20, 620, 460, WHITE);
    drawLineDDA(620, 460, 20, 460, WHITE);
    drawLineDDA(20, 460, 20, 20, WHITE);
}

void drawCircleBresenham(int xc, int yc, int r, int color) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (x <= y) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);
        putpixel(xc + y, yc + x, color);
        putpixel(xc - y, yc + x, color);
        putpixel(xc + y, yc - x, color);
        putpixel(xc - y, yc - x, color);
        if (d < 0) d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int x = 50, y = 50, dx = 5, dy = 5;
    int radius = 10;

    while (!kbhit()) {
        cleardevice();
        drawBox();
        drawCircleBresenham(x, y, radius, YELLOW);

        x += dx;
        y += dy;

        if (x >= 620 - radius || x <= 20 + radius) dx = -dx;
        if (y >= 460 - radius || y <= 20 + radius) dy = -dy;

        delay(30);
    }

    getch();
    closegraph();
}
