#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>

#define MAX 10000

typedef struct {
    int x, y;
} Point;

Point stack[MAX];
int top = -1;

void push(Point p) {
    if (top < MAX - 1) {
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

int isStackEmpty() {
    return top == -1;
}

void boundaryFill(int x, int y, int fillc, int boundaryc) {
    Point p = {x, y};
    push(p);

    while (!isStackEmpty()) {
        Point curr = pop();
        int curr_color = getpixel(curr.x, curr.y);

        if (curr_color != boundaryc && curr_color != fillc) {
            putpixel(curr.x, curr.y, fillc);
            delay(1);  // Optional: visualize

            Point temp;
            temp.x = curr.x + 1; temp.y = curr.y; push(temp);
            temp.x = curr.x - 1; temp.y = curr.y; push(temp);
            temp.x = curr.x; temp.y = curr.y + 1; push(temp);
            temp.x = curr.x; temp.y = curr.y - 1; push(temp);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    int n, x[20], y[20], i;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter vertices (x y):\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    for (i = 0; i < n - 1; i++) {
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }
    line(x[n - 1], y[n - 1], x[0], y[0]);

    int fill_color = RED;
    int boundary_color = WHITE;

    int seed_x, seed_y;
    printf("Enter seed point inside polygon (x y): ");
    scanf("%d %d", &seed_x, &seed_y);

    boundaryFill(seed_x, seed_y, fill_color, boundary_color);

    getch();
    closegraph();
    return 0;
}
