#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>

void initializeGraphics() {
    int gd = DETECT, gm, errorcode;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    
    errorcode = graphresult();
    if (errorcode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1);
    }
}

void drawAxes() {
    int midx = getmaxx()/2;
    int midy = getmaxy()/2;
    
    setcolor(WHITE);
    line(0, midy, getmaxx(), midy);
    line(midx, 0, midx, getmaxy());
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(midx + 20, 20, "Q1");
    outtextxy(20, 20, "Q2");
    outtextxy(20, midy + 20, "Q3");
    outtextxy(midx + 20, midy + 20, "Q4");
}

void drawPolygon(int *points, int n, int color) {
    int i;  // Declare i here instead of in the for loop
    setcolor(color);
    for(i = 0; i < n-1; i++) {
        line(points[2*i], points[2*i+1], points[2*i+2], points[2*i+3]);
    }
    line(points[2*(n-1)], points[2*(n-1)+1], points[0], points[1]);
}

void reflectX(int *y, int centerY) {
    *y = 2*centerY - *y;
}

void reflectY(int *x, int centerX) {
    *x = 2*centerX - *x;
}

void getPolygonPoints(int *points, int n) {
    int i;  // Declare i here
    printf("Enter coordinates for %d vertices (x y format):\n", n);
    for(i = 0; i < n; i++) {
        printf("Vertex %d: ", i+1);
        scanf("%d %d", &points[2*i], &points[2*i+1]);
    }
}

int main() {
    int n, i;  // Declare all loop variables at the start
    int points[20], pointsY[20], pointsX[20], pointsB[20];
    int centerX, centerY;
    
    printf("Enter number of vertices for polygon (3-10): ");
    scanf("%d", &n);
    
    if(n < 3 || n > 10) {
        printf("Number of vertices must be between 3 and 10\n");
        getch();
        return 1;
    }
    
    getPolygonPoints(points, n);
    
    initializeGraphics();
    
    centerX = getmaxx() / 2;
    centerY = getmaxy() / 2;
    
    // Adjust coordinates
    for(i = 0; i < n; i++) {
        points[2*i] += centerX;
        points[2*i+1] = centerY - points[2*i+1];
    }
    
    drawAxes();
    drawPolygon(points, n, GREEN);
    
    // Y-reflection
    for(i = 0; i < 2*n; i++) pointsY[i] = points[i];
    for(i = 0; i < n; i++) reflectY(&pointsY[2*i], centerX);
    drawPolygon(pointsY, n, RED);
    
    // X-reflection
    for(i = 0; i < 2*n; i++) pointsX[i] = points[i];
    for(i = 0; i < n; i++) reflectX(&pointsX[2*i+1], centerY);
    drawPolygon(pointsX, n, BLUE);
    
    // Both reflections
    for(i = 0; i < 2*n; i++) pointsB[i] = points[i];
    for(i = 0; i < n; i++) {
        reflectX(&pointsB[2*i+1], centerY);
        reflectY(&pointsB[2*i], centerX);
    }
    drawPolygon(pointsB, n, YELLOW);
    
    // Labels
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(points[0], points[1]-20, "Original");
    outtextxy(pointsY[0]-30, pointsY[1]-20, "Y-reflect");
    outtextxy(pointsX[0], pointsX[1]+10, "X-reflect");
    outtextxy(pointsB[0]-30, pointsB[1]+10, "Both");
    
    getch();
    closegraph();
    return 0;
}