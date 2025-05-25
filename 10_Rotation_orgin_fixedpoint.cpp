#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Custom rounding function for Turbo C++ */
int my_round(double x) {
    return (int)(x + 0.5);
}

int screenCenterX, screenCenterY;

void mathToScreen(int mathX, int mathY, int *screenX, int *screenY) {
    *screenX = screenCenterX + mathX;
    *screenY = screenCenterY - mathY;
}

void drawGrid() {
    int maxX = getmaxx();
    int maxY = getmaxy();

    screenCenterX = maxX / 2;
    screenCenterY = maxY / 2;

    setcolor(WHITE);
    line(0, screenCenterY, maxX, screenCenterY);
    line(screenCenterX, 0, screenCenterX, maxY);

    setcolor(LIGHTGRAY);
    outtextxy(screenCenterX + 10, screenCenterY - 20, "Q1 (+X, +Y)");
    outtextxy(screenCenterX - 100, screenCenterY - 20, "Q2 (-X, +Y)");
    outtextxy(screenCenterX - 100, screenCenterY + 10, "Q3 (-X, -Y)");
    outtextxy(screenCenterX + 10, screenCenterY + 10, "Q4 (+X, -Y)");

    setcolor(YELLOW);
    outtextxy(getmaxx() - 40, screenCenterY + 5, "X-axis");
    outtextxy(screenCenterX - 20, 5, "Y-axis");
    outtextxy(screenCenterX + 5, screenCenterY + 5, "Origin (0,0)");
}

void drawPolygon(int x[], int y[], int n, int color, char label[]) {
    int i, sx1, sy1, sx2, sy2;

    setcolor(color);
    for (i = 0; i < n; i++) {
        mathToScreen(x[i], y[i], &sx1, &sy1);
        mathToScreen(x[(i + 1) % n], y[(i + 1) % n], &sx2, &sy2);
        line(sx1, sy1, sx2, sy2);
    }

    mathToScreen(x[0], y[0], &sx1, &sy1);
    outtextxy(sx1 + 5, sy1 + 5, label);
}

void rotatePolygonAboutOrigin(int x[], int y[], int n, int angle) {
    double angleRad = angle * M_PI / 180.0;
    double cosA = cos(angleRad);
    double sinA = sin(angleRad);
    int i;
    int newX[20], newY[20];

    for (i = 0; i < n; i++) {
        newX[i] = my_round(x[i] * cosA - y[i] * sinA);
        newY[i] = my_round(x[i] * sinA + y[i] * cosA);
    }

    drawPolygon(newX, newY, n, GREEN, "Rotated (Origin)");
}

void rotatePolygonAboutFixedPoint(int x[], int y[], int n, int pivotX, int pivotY, int angle) {
    double angleRad = angle * M_PI / 180.0;
    double cosA = cos(angleRad);
    double sinA = sin(angleRad);
    int i;
    int newX[20], newY[20];
    double tempX, tempY;

    for (i = 0; i < n; i++) {
        tempX = x[i] - pivotX;
        tempY = y[i] - pivotY;
        newX[i] = my_round(tempX * cosA - tempY * sinA + pivotX);
        newY[i] = my_round(tempX * sinA + tempY * cosA + pivotY);
    }

    drawPolygon(newX, newY, n, MAGENTA, "Rotated (Fixed)");
}

int main() {
    int gd = DETECT, gm;
    int x[20], y[20];
    int n, i;
    int angle, choice;
    int pivotX, pivotY;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    drawGrid();

    printf("Enter number of vertices (max 20): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    printf("Enter rotation angle (degrees): ");
    scanf("%d", &angle);

    printf("\nRotation Type:\n1. About Origin\n2. About Fixed Point\nChoice: ");
    scanf("%d", &choice);

    drawPolygon(x, y, n, BLUE, "Original");

    if (choice == 1) {
        rotatePolygonAboutOrigin(x, y, n, angle);
    } else if (choice == 2) {
        printf("Enter pivot point (x y): ");
        scanf("%d %d", &pivotX, &pivotY);
        rotatePolygonAboutFixedPoint(x, y, n, pivotX, pivotY, angle);
    } else {
        printf("Invalid choice!\n");
    }

    getch();
    closegraph();
    return 0;
}