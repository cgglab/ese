#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>  // Required for delay()

#define MAX 10
#define PI 3.14159

// Function Prototypes
void drawAxes();
void drawPolygon(int x[], int y[], int n, int color);
void shear(int x[], int y[], int n, float shx, float shy);
void rotate(int x[], int y[], int n, float angle_deg);
int round(float num);  // Custom round() for Turbo C++

void drawAxes() {
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;
    setcolor(LIGHTGRAY);
    line(0, midy, getmaxx(), midy);  // X-axis
    line(midx, 0, midx, getmaxy());  // Y-axis
}

void drawPolygon(int x[], int y[], int n, int color) {
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;
    setcolor(color);
    for (int i = 0; i < n; i++) {
        line(midx + x[i], midy - y[i], midx + x[(i + 1) % n], midy - y[(i + 1) % n]);
    }
}

void shear(int x[], int y[], int n, float shx, float shy) {
    int xs[MAX], ys[MAX];
    for (int i = 0; i < n; i++) {
        xs[i] = x[i] + shx * y[i];
        ys[i] = y[i] + shy * x[i];
        x[i] = xs[i];
        y[i] = ys[i];
    }
}

void rotate(int x[], int y[], int n, float angle_deg) {
    float angle_rad = angle_deg * PI / 180;
    int xr[MAX], yr[MAX];
    for (int i = 0; i < n; i++) {
        xr[i] = round(x[i] * cos(angle_rad) - y[i] * sin(angle_rad));
        yr[i] = round(x[i] * sin(angle_rad) + y[i] * cos(angle_rad));
        x[i] = xr[i];
        y[i] = yr[i];
    }
}

// Custom round() function (Turbo C++ lacks math.h's round())
int round(float num) {
    return (int)(num < 0 ? num - 0.5 : num + 0.5);
}

int main() {
    int gd = DETECT, gm;
    int x[MAX], y[MAX], x_shear[MAX], y_shear[MAX], x_rotate[MAX], y_rotate[MAX];
    int n;
    float shx, shy, angle;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Draw axes dividing screen into four quadrants
    drawAxes();

    // Input
    printf("Enter number of vertices (3-10): ");
    scanf("%d", &n);

    printf("Enter coordinates (x y) for each vertex:\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
        x_shear[i] = x[i];  // Copy for shearing
        y_shear[i] = y[i];
        x_rotate[i] = x[i]; // Copy for rotation
        y_rotate[i] = y[i];
    }

    printf("Enter shearing factors (shx shy): ");
    scanf("%f %f", &shx, &shy);

    printf("Enter rotation angle (degrees): ");
    scanf("%f", &angle);

    // Draw original polygon (WHITE)
    drawPolygon(x, y, n, WHITE);
    outtextxy(getmaxx() / 2 + 10, getmaxy() / 2 - 20, "Original (White)");

    // Apply shearing (RED)
    shear(x_shear, y_shear, n, shx, shy);
    drawPolygon(x_shear, y_shear, n, RED);
    outtextxy(getmaxx() / 2 + 10, getmaxy() / 2 + 10, "Sheared (Red)");

    delay(2000);  // Pause to see shearing

    // Apply rotation (GREEN)
    rotate(x_rotate, y_rotate, n, angle);
    drawPolygon(x_rotate, y_rotate, n, GREEN);
    outtextxy(getmaxx() / 2 + 10, getmaxy() / 2 + 30, "Rotated (Green)");

    getch();
    closegraph();
    return 0;
}