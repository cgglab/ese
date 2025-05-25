#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#define MAX 10
#define PI 3.14159

/* Function prototypes */
void drawAxes();
void drawPolygon(int x[], int y[], int n, int color, int midx, int midy, char* label);
void translate(int x[], int y[], int n, int tx, int ty);
void rotate(int x[], int y[], int n, float angle_deg, int cx, int cy);
int round(float num);

int round(float num) {
    return (int)(num < 0 ? num - 0.5 : num + 0.5);
}

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

void translate(int x[], int y[], int n, int tx, int ty) {
    int i;
    for (i = 0; i < n; i++) {
        x[i] += tx;
        y[i] += ty;
    }
}

void rotate(int x[], int y[], int n, float angle_deg, int cx, int cy) {
    float angle_rad = angle_deg * PI / 180;
    float cos_theta = cos(angle_rad);
    float sin_theta = sin(angle_rad);
    int i;
    int x_new, y_new;
    
    for (i = 0; i < n; i++) {
        // Translate point to origin
        x[i] -= cx;
        y[i] -= cy;
        
        // Apply rotation
        x_new = round(x[i] * cos_theta - y[i] * sin_theta);
        y_new = round(x[i] * sin_theta + y[i] * cos_theta);
        
        // Translate back
        x[i] = x_new + cx;
        y[i] = y_new + cy;
    }
}

int main() {
    int gd = DETECT, gm;
    int x[MAX], y[MAX], translated[MAX], rotated[MAX];
    int n, tx, ty, i;
    float angle;
    int midx, midy;
    char msg[100];

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;
    drawAxes();

    // Input
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter coordinates of the polygon:\n");
    for (i = 0; i < n; i++) {
        printf("Point %d (x y): ", i + 1);
        scanf("%d%d", &x[i], &y[i]);
        // Make copies for transformations
        translated[i] = x[i];
        rotated[i] = x[i];
    }

    printf("Enter translation values (Tx Ty): ");
    scanf("%d%d", &tx, &ty);

    printf("Enter rotation angle (in degrees): ");
    scanf("%f", &angle);

    // Draw original
    drawPolygon(x, y, n, WHITE, midx, midy, "Original");

    // Draw translated only
    for (i = 0; i < n; i++) {
        translated[i] = x[i];
    }
    translate(translated, y, n, tx, ty);
    drawPolygon(translated, y, n, BLUE, midx, midy, "Translated");

    // Draw rotated only (around origin)
    for (i = 0; i < n; i++) {
        rotated[i] = x[i];
    }
    rotate(rotated, y, n, angle, 0, 0);
    drawPolygon(rotated, y, n, RED, midx, midy, "Rotated");

    // Display transformation parameters
    setcolor(WHITE);
    sprintf(msg, "Translation: (%d, %d)", tx, ty);
    outtextxy(10, 10, msg);
    sprintf(msg, "Rotation: %.1f degrees", angle);
    outtextxy(10, 30, msg);

    getch();
    closegraph();
    return 0;
}