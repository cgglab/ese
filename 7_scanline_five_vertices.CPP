#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>    // For delay()  

#define MAX_VERTICES 10

// Bubble sort for x-intersections
void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Scan Line Fill function
void scanLineFill(int x[], int y[], int n) {
    int i, j, scan_y, count;
    int ymax, ymin;
    int xi[MAX_VERTICES];

    ymin = y[0];
    ymax = y[0];
    for (i = 1; i < n; i++) {
        if (y[i] < ymin)
            ymin = y[i];
        if (y[i] > ymax)
            ymax = y[i];
    }

    for (scan_y = ymin; scan_y <= ymax; scan_y++) {
        count = 0;
        for (i = 0; i < n; i++) {
            j = (i + 1) % n;
            if (y[i] != y[j]) {
                if ((scan_y >= y[i] && scan_y < y[j]) || (scan_y >= y[j] && scan_y < y[i])) {
                    xi[count] = x[i] + (scan_y - y[i]) * (x[j] - x[i]) / (y[j] - y[i]);
                    count++;
                }
            }
        }
        sort(xi, count);
        for (i = 0; i < count; i += 2) {
            line(xi[i], scan_y, xi[i + 1], scan_y);
            delay(50);  // Adds delay for visual effect
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int x[5], y[5];
    int i;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter 5 vertices of the polygon (x y):\n");
    for (i = 0; i < 5; i++) {
        printf("Point %d: ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    setcolor(WHITE);
    for (i = 0; i < 5; i++) {
        line(x[i], y[i], x[(i + 1) % 5], y[(i + 1) % 5]);
    }

    setcolor(GREEN);
    scanLineFill(x, y, 5);

    getch();
    closegraph();
    return 0;
}
