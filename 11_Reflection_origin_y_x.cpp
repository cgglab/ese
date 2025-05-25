#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

int scrCX, scrCY;

void mathToScreen(int mX, int mY, int *sX, int *sY) {
    *sX = scrCX + mX;
    *sY = scrCY - mY;
}

void drawGrid() {
    int maxX, maxY;
    maxX = getmaxx();
    maxY = getmaxy();
    scrCX = maxX / 2;
    scrCY = maxY / 2;

    setcolor(WHITE);
    line(0, scrCY, maxX, scrCY);  // X-axis
    line(scrCX, 0, scrCX, maxY);  // Y-axis

    setcolor(LIGHTGRAY);
    outtextxy(scrCX + 10, scrCY - 20, "Q1 (+X, +Y)");
    outtextxy(scrCX - 100, scrCY - 20, "Q2 (-X, +Y)");
    outtextxy(scrCX - 100, scrCY + 10, "Q3 (-X, -Y)");
    outtextxy(scrCX + 10, scrCY + 10, "Q4 (+X, -Y)");

    setcolor(YELLOW);
    outtextxy(maxX - 40, scrCY + 5, "X-axis");
    outtextxy(scrCX - 10, 5, "Y-axis");
    outtextxy(scrCX + 5, scrCY + 5, "Origin (0,0)");
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

void reflectAboutOrigin(int x[], int y[], int n) {
    int i, rx[20], ry[20];
    for (i = 0; i < n; i++) {
        rx[i] = -x[i];
        ry[i] = -y[i];
    }
    drawPolygon(rx, ry, n, GREEN, "Reflected Origin");
}

void reflectAboutYeqX(int x[], int y[], int n) {
    int i, rx[20], ry[20];
    int sLineX1, sLineY1, sLineX2, sLineY2;

    for (i = 0; i < n; i++) {
        rx[i] = y[i];
        ry[i] = x[i];
    }

    // Draw the line Y = X
    mathToScreen(-getmaxx() / 2, -getmaxx() / 2, &sLineX1, &sLineY1);
    mathToScreen(getmaxx() / 2, getmaxx() / 2, &sLineX2, &sLineY2);
    setcolor(CYAN);
    line(sLineX1, sLineY1, sLineX2, sLineY2);
    outtextxy(sLineX2 - 60, sLineY2 - 10, "Y = X Axis");

    drawPolygon(rx, ry, n, MAGENTA, "Reflected Y=X");
}

int main() {
    int gDr = DETECT, gM;
    int x[20], y[20];
    int n, i;
    int ch;

    initgraph(&gDr, &gM, "C:\\TURBOC3\\BGI");
    drawGrid();

    printf("Enter number of vertices of the polygon (max 20): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter coordinates for vertex %d (x y): ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    drawPolygon(x, y, n, BLUE, "Original");

    printf("\nChoose Reflection Type:\n");
    printf("1. Reflect about Origin (0,0)\n");
    printf("2. Reflect about line Y=X\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);

    if (ch == 1) {
        reflectAboutOrigin(x, y, n);
    } else if (ch == 2) {
        reflectAboutYeqX(x, y, n);
    } else {
        printf("Invalid choice!\n");
    }

    getch();
    closegraph();
    return 0;
}
