#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    float x = x1;
    float y = y1;

    int sx = (x2 >= x1) ? 1 : -1;
    int sy = (y2 >= y1) ? 1 : -1;

    float m = (float)dy / dx;

    if (dx >= dy)
    {
        do
        {
            putpixel(round(x), round(y), WHITE);
            x += sx;
            y += m;
        } while (x <= x2);
    }
    else
    {
        do
        {
            putpixel(round(x), round(y), WHITE);
            y += sy;
            x += 1 / m;
        } while (y <= y2);
    }
}

void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int x = x1;
    int y = y1;

    int sx = (x2 >= x1) ? 1 : -1;
    int sy = (y2 >= y1) ? 1 : -1;

    putpixel(x, y, WHITE);

    if (dx >= dy)
    {
        int g = (2 * dy) - dx;
        do
        {
            x += sx;

            if (g >= 0)
            {
                y += sy;
                g += (2 * dy) - (2 * dx);
            }
            else
            {
                g += 2 * dy;
            }

            putpixel(x, y, WHITE);
        } while (x != x2);
    }
    else
    {
        int g = (2 * dx) - dy;
        do
        {
            y += sy;

            if (g >= 0)
            {
                x += sx;
                g += (2 * dx) - (2 * dy);
            }
            else
            {
                g += 2 * dx;
            }

            putpixel(x, y, WHITE);
        } while (y != y2);
    }
}

int main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2, choice;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); // ** IMPORTANT: Change this path to your BGI directory **

    printf("Enter the starting point (x1 y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter the ending point (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    printf("\nChoose the Line Drawing Algorithm:\n");
    printf("1. DDA Algorithm\n");
    printf("2. Bresenham's Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        drawLineDDA(x1, y1, x2, y2);
    } else if (choice == 2) {
        drawLineBresenham(x1, y1, x2, y2);
    } else {
        printf("Invalid choice!\n");
    }

    getch();
    closegraph();
    return 0;
}
