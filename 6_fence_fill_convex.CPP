#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>

#define MAX 10000
#define MAX_VERTICES 10

typedef struct {
    int x, y;
} Point;

Point stack[MAX];
int top = -1;

void push(Point p)
{
    if(top < MAX - 1)
    {
        top++;
        stack[top] = p;
    }
}

Point pop()
{
    Point p = {-1, -1};
    if(top >= 0)
    {
        p = stack[top];
        top--;
    }
    return p;
}

int isStackEmpty()
{
    return top == -1;
}

void fenceFill(int x, int y, int fenceC, int fillC)
{
    Point p = {x, y};
    push(p);
    while(!isStackEmpty())
    {
        Point curr = pop();

        if(curr.x < 0 || curr.x >= getmaxx() || curr.y < 0 || curr.y >= getmaxy())
            continue;

        int curr_color = getpixel(curr.x, curr.y);

        if(curr_color != fenceC && curr_color != fillC)
        {
            putpixel(curr.x, curr.y, fillC);
            delay(1);  // animation delay

            Point right = {curr.x + 1, curr.y};
            Point left = {curr.x - 1, curr.y};
            Point up = {curr.x, curr.y + 1};
            Point down = {curr.x, curr.y - 1};

            push(right);
            push(left);
            push(up);
            push(down);
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    int n, i;
    int fenceC = WHITE, fillC = YELLOW;
    int seedX, seedY;
    int x[MAX_VERTICES], y[MAX_VERTICES];

    printf("Enter number of vertices (3 to %d): ", MAX_VERTICES);
    scanf("%d", &n);
    if(n < 3 || n > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter coordinates (x y) of vertices:\n");
    for(i = 0; i < n; i++) {
        printf("Vertex %d: ", i+1);
        scanf("%d %d", &x[i], &y[i]);
    }

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    setcolor(fenceC);
    // Draw polygon edges
    for(i = 0; i < n; i++) {
        line(x[i], y[i], x[(i+1) % n], y[(i+1) % n]);
    }

    printf("Enter seed point inside polygon to fill (x y): ");
    scanf("%d %d", &seedX, &seedY);

    fenceFill(seedX, seedY, fenceC, fillC);

    getch();
    closegraph();
    return 0;
}
