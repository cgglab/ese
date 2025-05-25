#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>

// Function for Bresenham's Circle Drawing Algorithm
void bresenhamCircle(int xc, int yc, int r){

    int x = 0;
    int y = r;

    int s = 3 - (2*r);

    do{
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);
        putpixel(xc - y, yc + x, WHITE);

        if (s <= 0) {
            s += (4*x) + 6;
        }
        else
        {
            s += (4*x) - (4*y) + 10;
            y--;
        }
        x++;
    }while(x <= y);

}

// Function for Midpoint Circle Drawing Algorithm
void midCircle(int xc, int yc, int r){

    int x = 0;
    int y = r;

    int p = 1 - r;

    do{
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);
        putpixel(xc - y, yc + x, WHITE);

        if (p <= 0){
            p += (2*x) + 3;
        }
        else
        {
            p += (2*x) - (2*y) + 5;
            y--;
        }
        x++;
    }while(x <= y);
}

int main() {
    // ALL variable declarations MUST be at the very beginning of the function
    int gd = DETECT, gm;
    int xc, yc, r, choice; // MOVED these declarations here!

    // IMPORTANT: Change this path to your BGI directory (e.g., "C:\\TURBOC3\\BGI")
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter the center coordinates (xc yc): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter the radius (r): ");
    scanf("%d", &r);

    printf("\nChoose the Circle Drawing Algorithm:\n");
    printf("1. Bresenham's Algorithm\n");
    printf("2. Midpoint Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        bresenhamCircle(xc, yc, r);
    } else if (choice == 2) {
        midCircle(xc, yc, r);
    } else {
        printf("Invalid choice!\n");
    }

    getch(); // Wait for a key press to close the graphics window
    closegraph(); // Close the graphics mode
    return 0;
}
