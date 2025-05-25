#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define MAX 20

struct Point {
    int x, y;
};

int xmin, xmax, ymin, ymax;

int insideLeft(struct Point p) { return p.x >= xmin; }
int insideRight(struct Point p) { return p.x <= xmax; }
int insideBottom(struct Point p) { return p.y <= ymax; }
int insideTop(struct Point p) { return p.y >= ymin; }

struct Point intersect(struct Point p1, struct Point p2, char edge) {
    struct Point i;
    float m;

    if (p1.x != p2.x)
        m = (float)(p2.y - p1.y) / (p2.x - p1.x);
    else
        m = 99999;

    switch (edge) {
        case 'l':
            i.x = xmin;
            i.y = p1.y + (xmin - p1.x) * m;
            break;
        case 'r':
            i.x = xmax;
            i.y = p1.y + (xmax - p1.x) * m;
            break;
        case 'b':
            i.y = ymax;
            if (m != 0)
                i.x = p1.x + (ymax - p1.y) / m;
            else
                i.x = p1.x;
            break;
        case 't':
            i.y = ymin;
            if (m != 0)
                i.x = p1.x + (ymin - p1.y) / m;
            else
                i.x = p1.x;
            break;
    }

    return i;
}

void clipPolygon(struct Point in[], int n, struct Point out[], int *outlen, char edge) {
    struct Point s, p, ipt;
    int i, k;
    int insideS = 0, insideP = 0;

    s = in[n - 1];
    k = 0;

    for (i = 0; i < n; i++) {
        p = in[i];

        if (edge == 'l') {
            insideS = insideLeft(s);
            insideP = insideLeft(p);
        } else if (edge == 'r') {
            insideS = insideRight(s);
            insideP = insideRight(p);
        } else if (edge == 'b') {
            insideS = insideBottom(s);
            insideP = insideBottom(p);
        } else if (edge == 't') {
            insideS = insideTop(s);
            insideP = insideTop(p);
        }

        if (insideP) {
            if (!insideS) {
                ipt = intersect(s, p, edge);
                out[k++] = ipt;
            }
            out[k++] = p;
        } else if (insideS) {
            ipt = intersect(s, p, edge);
            out[k++] = ipt;
        }

        s = p;
    }

    *outlen = k;
}

void drawPolygon(struct Point poly[], int n, int color) {
    int i;
    setcolor(color);
    for (i = 0; i < n; i++) {
        line(poly[i].x, poly[i].y, poly[(i + 1) % n].x, poly[(i + 1) % n].y);
    }
}

void main() {
    int gd = DETECT, gm;
    struct Point polygon[MAX], temp1[MAX], temp2[MAX];
    int n, i;
    int temp_n1, temp_n2;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%d%d", &polygon[i].x, &polygon[i].y);
    }

    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%d%d%d%d", &xmin, &ymin, &xmax, &ymax);

    for (i = 0; i < n; i++)
        temp1[i] = polygon[i];
    temp_n1 = n;

    drawPolygon(polygon, n, WHITE);
    setcolor(RED);
    rectangle(xmin, ymin, xmax, ymax);

    clipPolygon(temp1, temp_n1, temp2, &temp_n2, 'l');
    clipPolygon(temp2, temp_n2, temp1, &temp_n1, 'r');
    clipPolygon(temp1, temp_n1, temp2, &temp_n2, 'b');
    clipPolygon(temp2, temp_n2, temp1, &temp_n1, 't');

    drawPolygon(temp1, temp_n1, GREEN);

    outtextxy(10, 10, "White: Original | Green: Clipped | Red: Window");

    getch();
    closegraph();
}
