#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

#define PI 3.14159265

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

// Draw the entire wave and get ball coordinates at the same time
void drawSineWaveAndBall(int ballX) {
    int x1 = 0;
    int y1 = 200 + 40 * sin(x1 * PI / 180);
    int x2, y2;
    int ballY = 0;

    for (x2 = 1; x2 < getmaxx(); x2++) {
        y2 = 200 + 40 * sin(x2 * PI / 180);

        // Draw DDA Line between (x1, y1) and (x2, y2)
        int dx = x2 - x1;
        int dy = y2 - y1;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

        float Xinc = dx / (float)steps;
        float Yinc = dy / (float)steps;

        float x = x1, y = y1;
        for (int i = 0; i <= steps; i++) {
            putpixel((int)x, (int)y, LIGHTGRAY);

            // Check if this x is close to ballX (±5 pixels)
            if ((int)x >= ballX - 5 && (int)x <= ballX + 5) {
                ballY = (int)y;
            }

            x += Xinc;
            y += Yinc;
        }

        x1 = x2;
        y1 = y2;
    }

    // Draw the ball on top of the wave
    if (ballY != 0) {
        midpointCircle(ballX, ballY, 15);
    }
}

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int ballX = 0, direction = 1;

    while (!kbhit()) {
        cleardevice();

        drawSineWaveAndBall(ballX);  // Draw wave and ball

        ballX += direction * 10;

        if (ballX >= getmaxx() || ballX <= 0)
            direction *= -1;  // Reverse direction

        delay(50);
    }

    getch();
    closegraph();
}
