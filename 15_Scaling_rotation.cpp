#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#define MAX 10
#define PI 3.14159

void drawAxes() {
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;

    setcolor(LIGHTGRAY);
    line(0, midy, getmaxx(), midy);  // X-axis
    line(midx, 0, midx, getmaxy());  // Y-axis
}

void drawPolygon(int x[], int y[], int n, int color, int midx, int midy, char* label) {
    int i;
    setcolor(color);
    for (i = 0; i < n; i++) {
        line(midx + x[i], midy - y[i], midx + x[(i + 1) % n], midy - y[(i + 1) % n]);
    }
    outtextxy(midx + x[0] + 10, midy - y[0] - 10, label);
}

void scale(int x[], int y[], int n, float sx, float sy) {
    int i;
    for (i = 0; i < n; i++) {
        x[i] = x[i] * sx;
        y[i] = y[i] * sy;
    }
}

void rotate(int x[], int y[], int n, float angle_deg) {
    float angle_rad = angle_deg * PI / 180;
    int i;
    int xr[MAX], yr[MAX];

    for (i = 0; i < n; i++) {
        xr[i] = x[i] * cos(angle_rad) - y[i] * sin(angle_rad);
        yr[i] = x[i] * sin(angle_rad) + y[i] * cos(angle_rad);
        x[i] = xr[i];
        y[i] = yr[i];
    }
}

int main() {
    int gd = DETECT, gm;
    int x[MAX], y[MAX], scaled[MAX], rotated[MAX], scaled_rotated[MAX];
    int n, i;
    float sx, sy, angle;
    int midx, midy;
    char msg[100];

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    drawAxes();  // Show 4 quadrants

    // -------- Input from user --------
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter coordinates of the polygon:\n");
    for (i = 0; i < n; i++) {
        printf("Point %d (x y): ", i + 1);
        scanf("%d%d", &x[i], &y[i]);
        // Make copies for transformations
        scaled[i] = x[i];
        rotated[i] = x[i];
        scaled_rotated[i] = x[i];
    }

    printf("Enter scaling factors (Sx Sy): ");
    scanf("%f%f", &sx, &sy);

    printf("Enter rotation angle (in degrees): ");
    scanf("%f", &angle);

    // -------- Draw Original --------
    drawPolygon(x, y, n, WHITE, midx, midy, "Original");

    // -------- Apply Scaling --------
    for (i = 0; i < n; i++) {
        scaled[i] = x[i];
    }
    scale(scaled, y, n, sx, sy);
    drawPolygon(scaled, y, n, BLUE, midx, midy, "Scaled");

    // -------- Apply Rotation --------
    for (i = 0; i < n; i++) {
        rotated[i] = x[i];
    }
    rotate(rotated, y, n, angle);
    drawPolygon(rotated, y, n, RED, midx, midy, "Rotated");

    // -------- Apply Both Scaling and Rotation --------
    for (i = 0; i < n; i++) {
        scaled_rotated[i] = x[i];
    }
    scale(scaled_rotated, y, n, sx, sy);
    rotate(scaled_rotated, y, n, angle);
    drawPolygon(scaled_rotated, y, n, GREEN, midx, midy, "Scaled & Rotated");

    // Display transformation parameters
    setcolor(WHITE);
    sprintf(msg, "Scaling: (%.1f, %.1f)", sx, sy);
    outtextxy(10, 10, msg);
    sprintf(msg, "Rotation: %.1f degrees", angle);
    outtextxy(10, 30, msg);

    getch();
    closegraph();
    return 0;
}