#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#define MAX 10

void drawAxes() {
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;
    
    setcolor(WHITE);
    line(midx, 0, midx, getmaxy()); // Y-axis
    line(0, midy, getmaxx(), midy); // X-axis
    
    // Label the quadrants
    settextstyle(SMALL_FONT, HORIZ_DIR, 4);
    outtextxy(midx + 20, 20, "I");
    outtextxy(20, 20, "II");
    outtextxy(20, midy + 20, "III");
    outtextxy(midx + 20, midy + 20, "IV");
}

void applyTransformation(int x[], int y[], int n, int tx, int ty, float sx, float sy, int newX[], int newY[]) {
    int i;
    for (i = 0; i < n; i++) {
        // Apply scaling first
        newX[i] = (int)(x[i] * sx);
        newY[i] = (int)(y[i] * sy);
        // Then apply translation
        newX[i] += tx;
        newY[i] += ty;
    }
}

void plotPolygon(int x[], int y[], int n, int dx, int dy, int color, char* label) {
    int i;
    setcolor(color);
    for (i = 0; i < n - 1; i++) {
        line(dx + x[i], dy - y[i], dx + x[i + 1], dy - y[i + 1]);
    }
    line(dx + x[n - 1], dy - y[n - 1], dx + x[0], dy - y[0]); // Close polygon
    outtextxy(dx + x[0] + 10, dy - y[0] - 10, label);
}

void main() {
    int gd = DETECT, gm;
    int x[MAX], y[MAX], scaledX[MAX], scaledY[MAX], transformedX[MAX], transformedY[MAX];
    int n, i;
    float sx, sy;
    int tx, ty;
    int midx, midy;
    char msg[100];

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    printf("Enter number of vertices (max 10): ");
    scanf("%d", &n);

    printf("Enter coordinates (x y) of polygon (relative to origin):\n");
    for (i = 0; i < n; i++) {
        printf("Point %d: ", i + 1);
        scanf("%d%d", &x[i], &y[i]);
    }

    printf("Enter scaling factors Sx and Sy (try 0.5 0.5 for visible scaling): ");
    scanf("%f%f", &sx, &sy);

    printf("Enter translation Tx and Ty (try 100 50 for visible movement): ");
    scanf("%d%d", &tx, &ty);

    cleardevice();
    drawAxes();

    // 1. Draw original polygon (RED)
    plotPolygon(x, y, n, midx, midy, RED, "Original");

    // 2. Apply only scaling (BLUE)
    applyTransformation(x, y, n, 0, 0, sx, sy, scaledX, scaledY);
    plotPolygon(scaledX, scaledY, n, midx, midy, BLUE, "Scaled");

    // 3. Apply both scaling and translation (GREEN)
    applyTransformation(x, y, n, tx, ty, sx, sy, transformedX, transformedY);
    plotPolygon(transformedX, transformedY, n, midx, midy, GREEN, "Scaled+Translated");

    // Display transformation parameters
    setcolor(WHITE);
    sprintf(msg, "Scaling: (%.1f, %.1f)", sx, sy);
    outtextxy(10, 10, msg);
    sprintf(msg, "Translation: (%d, %d)", tx, ty);
    outtextxy(10, 30, msg);

    getch();
    closegraph();
}