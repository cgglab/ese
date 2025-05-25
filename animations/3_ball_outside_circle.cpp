#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <dos.h>  

#define PI 3.1416  

// Midpoint circle algorithm
void midpointCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 1 - r;

    while (x <= y) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void main() {  
    int gd = DETECT, gm;  
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");  

    int R = 100, r = 10, x = 300, y = 250;  
    double angle = 0;  
    int direction = 1;  

    while (!kbhit()) {  
        cleardevice();  

        // Draw big circle with midpoint circle algorithm
        midpointCircle(x, y, R);

        // Calculate position of small circle (satellite)
        int cx = x + (R + r + 5) * cos(angle * PI / 180);  
        int cy = y + (R + r + 5) * sin(angle * PI / 180);  

        // Draw small circle with midpoint circle algorithm
        midpointCircle(cx, cy, r);

        // Update angle  
        angle += direction * 2;  
        if (angle >= 360) angle -= 360;  
        if (angle < 0) angle += 360;  

        // Reverse direction at bounds  
        if (angle >= 360 || angle <= 0) {  
            direction *= -1;  
        }  

        delay(30);  
    }  

    getch();  
    closegraph();  
}
