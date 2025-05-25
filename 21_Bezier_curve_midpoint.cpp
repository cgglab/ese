#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h> // For delay()

struct P {
    int x, y;
};

void drawP(int x, int y) {
    putpixel(x, y, WHITE);
}

void bezier(struct P p0, struct P p1, struct P p2, struct P p3, int i) {
    if (i == 0) {
        line(p0.x, p0.y, p3.x, p3.y);
        return;
    }

    struct P q0, q1, q2, r0, r1, s0;

    q0.x = (p0.x + p1.x) / 2;
    q0.y = (p0.y + p1.y) / 2;

    q1.x = (p1.x + p2.x) / 2;
    q1.y = (p1.y + p2.y) / 2;

    q2.x = (p2.x + p3.x) / 2;
    q2.y = (p2.y + p3.y) / 2;

    r0.x = (q0.x + q1.x) / 2;
    r0.y = (q0.y + q1.y) / 2;

    r1.x = (q1.x + q2.x) / 2;
    r1.y = (q1.y + q2.y) / 2;

    s0.x = (r0.x + r1.x) / 2;
    s0.y = (r0.y + r1.y) / 2;

    bezier(p0, q0, r0, s0, i - 1);
    bezier(s0, r1, q2, p3, i - 1);
}

int main() {
    int gd = DETECT, gm;
    int k;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    struct P p[4];
    printf("Enter 4 control points (x y):\n");
    for (k = 0; k < 4; k++) {
        printf("Point %d: ", k + 1);
        scanf("%d %d", &p[k].x, &p[k].y);
    }

    int it;
    printf("Enter number of iterations (1-4): ");
    scanf("%d", &it);

    if (it < 1 || it > 4) {
        printf("Invalid iterations. Using 4.\n");
        it = 4;
    }

    cleardevice();

    setcolor(YELLOW);
    for (k = 0; k < 4; k++) {
        circle(p[k].x, p[k].y, 3);
        putpixel(p[k].x, p[k].y, YELLOW);
    }
    outtextxy(10, 10, "Control Points (Yellow Circles)");

    setcolor(WHITE);
    line(p[0].x, p[0].y, p[1].x, p[1].y);
    line(p[1].x, p[1].y, p[2].x, p[2].y);
    line(p[2].x, p[2].y, p[3].x, p[3].y);
    outtextxy(10, 25, "Control Polygon (White)");

    setcolor(RED);
    bezier(p[0], p[1], p[2], p[3], it);
    outtextxy(10, 40, "Bezier Curve (Red)");

    getch();
    closegraph();
    return 0;
}