#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>  // Added for delay()

#define LEFT 1    // 0001
#define RIGHT 2   // 0010
#define BOTTOM 4  // 0100
#define TOP 8     // 1000

int xmin, ymin, xmax, ymax;

// Function to compute the region code for a point (x, y)
int computeCode(int x, int y) {
    int code = 0;
    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= TOP;
    else if (y > ymax) code |= BOTTOM;
    return code;
}

void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            // Both points inside: trivially accept
            accept = 1;
            break;
        } else if (code1 & code2) {
            // Logical AND is not 0: trivially reject
            break;
        } else {
            int code_out;
            int x, y;

            // At least one endpoint is outside the clipping rectangle
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP) {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (code_out & BOTTOM) {
                // point is below the clip rectangle
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (code_out & RIGHT) {
                // point is to the right of clip rectangle
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (code_out & LEFT) {
                // point is to the left of clip rectangle
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            // Replace point outside clipping rectangle with intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    // Draw clipping window
    rectangle(xmin, ymin, xmax, ymax);

    if (accept) {
        setcolor(GREEN);
        line(x1, y1, x2, y2);
        outtextxy(10, 10, "Line after clipping (GREEN)");
    } else {
        outtextxy(10, 10, "Line rejected (outside clipping window)");
    }
}

void main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2;

    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%d %d %d %d", &xmin, &ymin, &xmax, &ymax);

    printf("Enter line endpoints (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // Draw clipping window
    setcolor(WHITE);
    rectangle(xmin, ymin, xmax, ymax);

    // Draw original line in RED
    setcolor(RED);
    line(x1, y1, x2, y2);
    outtextxy(10, 20, "Original line (RED)");

    delay(3000);  // Now works correctly

    cleardevice();

    // Perform clipping and draw clipped line
    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
}