#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

#define PI 3.14159

// DDA line drawing
void ddaLine(int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        putpixel((int)(x + 0.5), (int)(y + 0.5), color);
        x += Xinc;
        y += Yinc;
    }
}

// Midpoint circle algorithm for drawing semicircle (arc from 180 to 360 degrees)
void drawSemiCircleMidpoint(int cx, int cy, int r, int color) {
    int x = 0;
    int y = r;
    int d = 1 - r;

    while (x <= y) {
        // Only plot points from 180 to 360 degrees (bottom half semicircle)
        // Points in bottom half have y >= cy
        if (cy + y >= cy) putpixel(cx + x, cy + y, color); // Q4
        if (cy + x >= cy) putpixel(cx + y, cy + x, color); // Q4

        if (cy + x >= cy) putpixel(cx - y, cy + x, color); // Q3
        if (cy + y >= cy) putpixel(cx - x, cy + y, color); // Q3

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

    int rectX = 150, rectY = 150, rectW = 200, rectH = 150;
    int radius = 50;
    int centerX = rectX + rectW / 2;
    int arcCenterY = rectY;  // Arc center is at rectangle top edge

    float angle = 0;
    int direction = 1;

    while (!kbhit()) {
        cleardevice();

        // Draw rectangle sides and bottom using DDA lines
        ddaLine(rectX, rectY, rectX, rectY + rectH, WHITE);                // left vertical
        ddaLine(rectX + rectW, rectY, rectX + rectW, rectY + rectH, WHITE); // right vertical
        ddaLine(rectX, rectY + rectH, rectX + rectW, rectY + rectH, WHITE); // bottom horizontal

        // Top left segment (left edge to left of semicircle)
        ddaLine(rectX, rectY, centerX - radius, rectY, WHITE);

        // Top right segment (right of semicircle to right edge)
        ddaLine(centerX + radius, rectY, rectX + rectW, rectY, WHITE);

        // Draw semicircle (bottom half only)
        drawSemiCircleMidpoint(centerX, arcCenterY, radius, WHITE);

        // Animate ball along semicircle path
        float rad = angle * PI / 180.0;
        int ballX = centerX + (int)(radius * cos(rad));
        int ballY = arcCenterY + (int)(radius * sin(rad));

        setcolor(RED);
        circle(ballX, ballY, 5);
        floodfill(ballX, ballY, RED);

        delay(30);

        angle += direction * 2;
        if (angle >= 180) direction = -1;
        if (angle <= 0) direction = 1;
    }

    getch();
    closegraph();
    return 0;
}
