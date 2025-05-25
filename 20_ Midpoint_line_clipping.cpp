#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>  // for delay()

#define L 1 // Left
#define R 2 // Right
#define B 4 // Bottom
#define T 8 // Top

int xMin, yMin, xMax, yMax;

int getOutcode(int x, int y) {
    int code = 0;
    if (x < xMin) code |= L;
    else if (x > xMax) code |= R;
    if (y < yMin) code |= B;
    else if (y > yMax) code |= T;
    return code;
}

void clipLine(int x1, int y1, int x2, int y2) {
    int outcode1 = getOutcode(x1, y1);
    int outcode2 = getOutcode(x2, y2);
    int accept = 0;

    while (1) {
        if ((outcode1 | outcode2) == 0) {
            accept = 1;
            break;
        } else if ((outcode1 & outcode2) != 0) {
            break;
        } else {
            int x, y;
            int outcodeOut = outcode1 ? outcode1 : outcode2;

            if (outcodeOut & T) {
                x = x1 + (x2 - x1) * (yMax - y1) / (y2 - y1);
                y = yMax;
            } else if (outcodeOut & B) {
                x = x1 + (x2 - x1) * (yMin - y1) / (y2 - y1);
                y = yMin;
            } else if (outcodeOut & R) {
                y = y1 + (y2 - y1) * (xMax - x1) / (x2 - x1);
                x = xMax;
            } else {
                y = y1 + (y2 - y1) * (xMin - x1) / (x2 - x1);
                x = xMin;
            }

            if (outcodeOut == outcode1) {
                x1 = x;
                y1 = y;
                outcode1 = getOutcode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                outcode2 = getOutcode(x2, y2);
            }
        }
    }

    if (accept) {
        setcolor(WHITE);  // Keep the same white color as original
        line(x1, y1, x2, y2);
        outtextxy(50, 60, "Clipped Line (WHITE) - Outside portion removed");
    } else {
        outtextxy(50, 60, "Line completely outside window - Nothing to display");
    }
}

int main() {
    int gd = DETECT, gm;
    int lx1, ly1, lx2, ly2;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter clipping window bottom-left (x y): ");
    scanf("%d %d", &xMin, &yMin);
    printf("Enter clipping window top-right (x y): ");
    scanf("%d %d", &xMax, &yMax);
    printf("Enter line start point (x y): ");
    scanf("%d %d", &lx1, &ly1);
    printf("Enter line end point (x y): ");
    scanf("%d %d", &lx2, &ly2);

    cleardevice();

    // Draw the clipping window
    setcolor(YELLOW);
    rectangle(xMin, yMin, xMax, yMax);
    outtextxy(50, 20, "Clipping Window (YELLOW)");

    // Draw the original line
    setcolor(WHITE);
    line(lx1, ly1, lx2, ly2);
    outtextxy(50, 40, "Original Line (WHITE)");

    delay(2000); // 2 seconds pause

    // Clear only the line by redrawing the rectangle and clipping window
    cleardevice();
    setcolor(YELLOW);
    rectangle(xMin, yMin, xMax, yMax);
    outtextxy(50, 20, "Clipping Window (YELLOW)");

    // Call clipping function to draw clipped line
    clipLine(lx1, ly1, lx2, ly2);

    getch();
    closegraph();
    return 0;
}