#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>

/* Function prototypes */
void mathToScreen(int mX, int mY, int *sX, int *sY);
void drawGrid();
void drawPolygon(int x[], int y[], int n, int color, char *label);
void transformPolygon(int origX[], int origY[], int transX[], int transY[], int n,
                     double scaleX, double scaleY, int transDx, int transDy);
void animateTransformation(int origX[], int origY[], int n);

int scrCX, scrCY;

int main() {
    int gd = DETECT, gm, errorcode;
    int origX[4] = {70, 90, 90, 70};  // Scaled up by 10 for better visibility
    int origY[4] = {30, 30, 50, 50};
    int transX[4], transY[4];
    int n = 4;
    
    double scaleX = 2.0, scaleY = 2.0;
    int transDx = 10, transDy = 10;  // Increased translation for visibility

    /* Initialize graphics mode */
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    errorcode = graphresult();
    if (errorcode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to exit...");
        getch();
        return 1;
    }

    /* Draw original figure */
    drawGrid();
    drawPolygon(origX, origY, n, BLUE, "Original");
    getch();
    
    /* Calculate final transformed coordinates */
    transformPolygon(origX, origY, transX, transY, n, scaleX, scaleY, transDx, transDy);
    
    /* Show animation of transformations */
    animateTransformation(origX, origY, n);
    
    /* Draw final result */
    cleardevice();
    drawGrid();
    drawPolygon(origX, origY, n, BLUE, "Original");
    drawPolygon(transX, transY, n, GREEN, "Transformed");
    
    /* Display transformation details */
    setcolor(WHITE);
    outtextxy(50, 50, "Transformations Applied:");
    outtextxy(50, 70, "1. Scaling: Sx=2.0, Sy=2.0");
    outtextxy(50, 90, "2. Reflection through origin");
    outtextxy(50, 110, "3. Translation: dx=10, dy=10");
    
    getch();
    closegraph();
    return 0;
}

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
    line(0, scrCY, maxX, scrCY);   /* X-axis */
    line(scrCX, 0, scrCX, maxY);   /* Y-axis */

    setcolor(LIGHTGRAY);
    outtextxy(scrCX + 10, scrCY - 20, "Q1 (+X, +Y)");
    outtextxy(scrCX - 100, scrCY - 20, "Q2 (-X, +Y)");
    outtextxy(scrCX - 100, scrCY + 10, "Q3 (-X, -Y)");
    outtextxy(scrCX + 10, scrCY + 10, "Q4 (+X, -Y)");

    setcolor(YELLOW);
    outtextxy(maxX - 60, scrCY + 5, "X-axis");
    outtextxy(scrCX - 30, 5, "Y-axis");
    outtextxy(scrCX + 5, scrCY + 5, "Origin (0,0)");
}

void drawPolygon(int x[], int y[], int n, int color, char *label) {
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

void transformPolygon(int origX[], int origY[], int transX[], int transY[], int n,
                     double scaleX, double scaleY, int transDx, int transDy) {
    int i;
    for (i = 0; i < n; i++) {
        /* 1. Scaling */
        double tempX = origX[i] * scaleX;
        double tempY = origY[i] * scaleY;

        /* 2. Reflection through origin */
        tempX = -tempX;
        tempY = -tempY;

        /* 3. Translation */
        tempX += transDx;
        tempY += transDy;

        transX[i] = (int)tempX;
        transY[i] = (int)tempY;
    }
}

void animateTransformation(int origX[], int origY[], int n) {
    int i, j;
    int steps = 20;
    int tempX[4], tempY[4];
    
    /* Animation: Scaling */
    for (j = 1; j <= steps; j++) {
        cleardevice();
        drawGrid();
        drawPolygon(origX, origY, n, BLUE, "Original");
        
        for (i = 0; i < n; i++) {
            tempX[i] = origX[i] * (1 + (float)j/steps);  // Scale from 1x to 2x
            tempY[i] = origY[i] * (1 + (float)j/steps);
        }
        drawPolygon(tempX, tempY, n, GREEN, "Scaling");
        delay(150);
    }
    
    /* Animation: Reflection */
    for (j = 1; j <= steps; j++) {
        cleardevice();
        drawGrid();
        drawPolygon(origX, origY, n, BLUE, "Original");
        
        for (i = 0; i < n; i++) {
            tempX[i] = (origX[i] * 2) * (1 - (float)j/steps);  // Flip from + to -
            tempY[i] = (origY[i] * 2) * (1 - (float)j/steps);
        }
        drawPolygon(tempX, tempY, n, RED, "Reflecting");
        delay(150);
    }
    
    /* Animation: Translation */
    for (j = 1; j <= steps; j++) {
        cleardevice();
        drawGrid();
        drawPolygon(origX, origY, n, BLUE, "Original");
        
        for (i = 0; i < n; i++) {
            tempX[i] = -(origX[i] * 2) + (10 * (float)j/steps);
            tempY[i] = -(origY[i] * 2) + (10 * (float)j/steps);
        }
        drawPolygon(tempX, tempY, n, MAGENTA, "Translating");
        delay(150);
    }
}