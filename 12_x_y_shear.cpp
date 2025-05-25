#include <graphics.h>
#include <stdio.h>
#include <conio.h>

int scrCX, scrCY;

void mathToScreen(int mX, int mY, int *sX, int *sY) {
    *sX = scrCX + mX;
    *sY = scrCY - mY;
}

void drawGrid() {
    int maxX = getmaxx();
    int maxY = getmaxy();

    scrCX = maxX / 2;
    scrCY = maxY / 2;

    setcolor(WHITE);
    line(0, scrCY, maxX, scrCY);   // X-axis
    line(scrCX, 0, scrCX, maxY);   // Y-axis

    setcolor(LIGHTGRAY);
    outtextxy(scrCX + 10, scrCY - 20, "Q1 (+X, +Y)");
    outtextxy(scrCX - 100, scrCY - 20, "Q2 (-X, +Y)");
    outtextxy(scrCX - 100, scrCY + 10, "Q3 (-X, -Y)");
    outtextxy(scrCX + 10, scrCY + 10, "Q4 (+X, -Y)");

    setcolor(YELLOW);
    outtextxy(getmaxx() - 60, scrCY + 5, "X-axis");
    outtextxy(scrCX - 30, 5, "Y-axis");
    outtextxy(scrCX + 5, scrCY + 5, "(0,0)");
}

void drawPolygon(int x[], int y[], int n, int color, const char *label) {
    setcolor(color);
    for (int i = 0; i < n; i++) {
        int sx1, sy1, sx2, sy2;
        mathToScreen(x[i], y[i], &sx1, &sy1);
        mathToScreen(x[(i + 1) % n], y[(i + 1) % n], &sx2, &sy2);
        line(sx1, sy1, sx2, sy2);
    }
    int sx0, sy0;
    mathToScreen(x[0], y[0], &sx0, &sy0);
    outtextxy(sx0 + 5, sy0 + 5, label);
}

void applyXShearPolygon(int x[], int y[], int n, double shX, int tx[], int ty[]) {
    for (int i = 0; i < n; i++) {
        tx[i] = x[i] + (int)(shX * y[i]);
        ty[i] = y[i];
    }
}

void applyYShearPolygon(int x[], int y[], int n, double shY, int tx[], int ty[]) {
    for (int i = 0; i < n; i++) {
        tx[i] = x[i];
        ty[i] = y[i] + (int)(shY * x[i]);
    }
}

int main() {
    int gDr = DETECT, gM;
    initgraph(&gDr, &gM, "C:\\TURBOC3\\BGI");

    drawGrid();

    int n;
    printf("Enter number of vertices of the polygon: ");
    scanf("%d", &n);

    int x[20], y[20];  // Original coordinates
    int tx[20], ty[20]; // Transformed coordinates

    for (int i = 0; i < n; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    drawPolygon(x, y, n, BLUE, "Original");

    int choice;
    double shearF;
    printf("\nChoose Shear Type:\n");
    printf("1. X-Shear\n");
    printf("2. Y-Shear\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter shear factor (e.g., 0.5, 1.0, -0.2): ");
    scanf("%lf", &shearF);

    if (choice == 1) {
        applyXShearPolygon(x, y, n, shearF, tx, ty);
        drawPolygon(tx, ty, n, GREEN, "X-Sheared");
    } else if (choice == 2) {
        applyYShearPolygon(x, y, n, shearF, tx, ty);
        drawPolygon(tx, ty, n, MAGENTA, "Y-Sheared");
    } else {
        printf("Invalid choice! No shear performed.\n");
    }

    getch();
    closegraph();
    return 0;
}