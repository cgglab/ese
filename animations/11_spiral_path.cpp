#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159

void drawSpiralPath(int cx, int cy, float a, float b, float maxTheta, float step) {
    int i;
    float theta, r, x, y;
    int prevX = -1, prevY = -1;

    for (theta = 0; theta < maxTheta; theta += step) {
        r = a + b * theta;
        x = cx + r * cos(theta);
        y = cy + r * sin(theta);

        if (prevX != -1)
            line(prevX, prevY, (int)x, (int)y);

        prevX = (int)x;
        prevY = (int)y;
    }
}

void automatedAnimation() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int maxX = getmaxx();
    int maxY = getmaxy();
    int cx = maxX / 2;
    int cy = maxY / 2;

    float a = 0, b = 3, step = 0.1, theta = 0;
    float maxTheta = 6 * PI;
    float r, x, y;

    drawSpiralPath(cx, cy, a, b, maxTheta, 0.05);

    outtextxy(10, maxY - 20, "Press any key to stop");

    while (theta < maxTheta && !kbhit()) {
        r = a + b * theta;
        x = cx + r * cos(theta);
        y = cy + r * sin(theta);

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        fillellipse((int)x, (int)y, 5, 5);

        delay(50);

        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse((int)x, (int)y, 5, 5);

        putpixel((int)x, (int)y, WHITE);
        theta += step;
    }

    getch();
    closegraph();
}

void manualAnimation() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int maxX = getmaxx();
    int maxY = getmaxy();
    int cx = maxX / 2;
    int cy = maxY / 2;

    float a = 0, b = 3, step = 0.2, theta = 0;
    float maxTheta = 6 * PI;
    float r, x, y;

    int prevX = -1, prevY = -1;
    drawSpiralPath(cx, cy, a, b, maxTheta, 0.05);

    outtextxy(10, maxY - 20, "Press SPACE to step, ESC to exit");

    char key;
    do {
        key = getch();
        if (key == ' ') {
            if (prevX != -1) {
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                fillellipse(prevX, prevY, 5, 5);
                putpixel(prevX, prevY, WHITE);
            }

            r = a + b * theta;
            x = cx + r * cos(theta);
            y = cy + r * sin(theta);

            setcolor(CYAN);
            setfillstyle(SOLID_FILL, CYAN);
            fillellipse((int)x, (int)y, 5, 5);

            prevX = (int)x;
            prevY = (int)y;
            theta += step;
        }
    } while (key != 27 && theta < maxTheta);

    getch();
    closegraph();
}

void showMenu() {
    int choice;

    do {
        clrscr();
        printf("============================\n");
        printf(" Spiral Animation in Turbo C\n");
        printf("============================\n");
        printf("1. Automated Animation\n");
        printf("2. Manual Animation\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                automatedAnimation();
                break;
            case 2:
                manualAnimation();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Press any key...\n");
                getch();
        }
    } while (choice != 3);
}

int main() {
    showMenu();
    return 0;
}
