#include <graphics.h>
#include <conio.h>
#include <dos.h>    // For delay()
#include <stdio.h>
#include <stdlib.h> // For exit()

#define MAX_VERTICES 20
#define MAX_STACK 10000

struct Point {
    int x, y;
};

Point stack[MAX_STACK];
int top = -1;

void push(Point p) {
    if (top < MAX_STACK - 1) {
        top++;
        stack[top] = p;
    }
}

Point pop() {
    Point p = {-1, -1};
    if (top >= 0) {
        p = stack[top];
        top--;
    }
    return p;
}

int isEmpty() {
    return (top == -1);
}

void boundaryFill(int x, int y, int fill_color, int boundary_color) {
    Point p = {x, y};
    push(p);

    while (!isEmpty()) {
        Point curr = pop();
        int curr_color = getpixel(curr.x, curr.y);

        if (curr_color != boundary_color && curr_color != fill_color) {
            putpixel(curr.x, curr.y, fill_color);
            delay(1);  // Small delay for animation

            Point p1;
            p1.x = curr.x + 1;
            p1.y = curr.y;
            push(p1);

            p1.x = curr.x - 1;
            p1.y = curr.y;
            push(p1);

            p1.x = curr.x;
            p1.y = curr.y + 1;
            push(p1);

            p1.x = curr.x;
            p1.y = curr.y - 1;
            push(p1);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int n, i;
    int x[MAX_VERTICES], y[MAX_VERTICES];
    int fill_color = RED, boundary_color = WHITE;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter number of vertices (max 10): ");
    scanf("%d", &n);

    if (n > 10) {
        printf("Too many vertices!\n");
        getch();
        closegraph();
        return 0;
    }

    printf("Enter coordinates (x y) of each vertex:\n");
    for (i = 0; i < n; i++) {
        printf("Point %d: ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    setcolor(boundary_color);
    for (i = 0; i < n; i++) {
        line(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
    }

    int seed_x, seed_y;
    printf("Enter seed point inside polygon (x y): ");
    scanf("%d %d", &seed_x, &seed_y);

    boundaryFill(seed_x, seed_y, fill_color, boundary_color);

    getch();
    closegraph();
    return 0;
}
