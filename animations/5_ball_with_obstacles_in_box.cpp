#include <graphics.h>
#include <conio.h>
#include <dos.h>

// Draw circle using midpoint algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r, p = 1 - r;

    while (x <= y) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        x++;
        if (p < 0) p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

// Draw rectangle and two vertical lines in middle with a gap
void drawPath(int left, int top, int right, int bottom, int midX, int midY) {
    rectangle(left, top, right, bottom);

    // Top-middle vertical line (top to midY - gap)
    line(midX, top, midX, midY - 20);

    // Bottom-middle vertical line (midY + gap to bottom)
    line(midX, midY + 20, midX, bottom);
}

void animatePath() {
    int left = 100, top = 100, right = 400, bottom = 300;
    int midX = (left + right) / 2;
    int midY = (top + bottom) / 2;
    int r = 10;

    while (!kbhit()) {
        int x, y;

        // 1. Bottom-left to top-left
        for (y = bottom - r; y >= top + r && !kbhit(); y -= 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(left + r, y, r);
            delay(10);
        }

        // 2. Top-left to top-middle
        for (x = left + r; x <= midX - r && !kbhit(); x += 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(x, top + r, r);
            delay(10);
        }

        // 3. Top-middle to mid-top (vertical down to gap)
        for (y = top + r; y <= midY - 20 - r && !kbhit(); y += 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(midX, y, r);
            delay(10);
        }

        // 4. Mid-top to right-middle (horizontal right)
        for (x = midX + r; x <= right - r && !kbhit(); x += 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(x, midY, r);
            delay(10);
        }

        // 5. Right-middle to bottom-right (vertical down)
        for (y = midY + r; y <= bottom - r && !kbhit(); y += 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(right - r, y, r);
            delay(10);
        }

        // 6. Bottom-right to bottom-middle (horizontal left)
        for (x = right - r; x >= midX + r && !kbhit(); x -= 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(x, bottom - r, r);
            delay(10);
        }

        // 7. Bottom-middle to mid-bottom (vertical up to gap)
        for (y = bottom - r; y >= midY + 20 + r && !kbhit(); y -= 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(midX, y, r);
            delay(10);
        }

        // 8. Mid-bottom to left-middle (horizontal left)
        for (x = midX - r; x >= left + r && !kbhit(); x -= 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(x, midY, r);
            delay(10);
        }

        // 9. Left-middle to bottom-left (vertical down)
        for (y = midY + r; y <= bottom - r && !kbhit(); y += 2) {
            cleardevice();
            drawPath(left, top, right, bottom, midX, midY);
            drawCircle(left + r, y, r);
            delay(10);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    animatePath();

    getch();
    closegraph();
    return 0;
}
