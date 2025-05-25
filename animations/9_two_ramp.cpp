#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <math.h>

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); // Adjust path if needed

    // Triangle vertices
    int A_x = 80,  A_y = 150;
    int B_x = 280, B_y = 300;
    int C_x = 400, C_y = 150;

    // Base points for the two triangles
    int base_y = 300;

    // Ball params
    int radius = 10;
    float pos = (float)A_x;  // ball x position
    float y;                 // ball y position
    int step = 2;            // speed

    // Slopes for inclined lines
    float m1 = (float)(B_y - A_y) / (B_x - A_x);
    float m2 = (float)(C_y - B_y) / (C_x - B_x);

    while (!kbhit())
    {
        cleardevice();

        // Draw first triangle edges (A-B-base line)
        setcolor(WHITE);
        line(A_x, A_y, B_x, B_y);          // left slope
        line(B_x, B_y, A_x, base_y);       // left base
        line(A_x, base_y, A_x, A_y);       // left vertical side (optional)
        // Or simply:
        // line(A_x, base_y, B_x, base_y);  // base of triangle, horizontal line

        // Draw second triangle edges (B-C-base line)
        line(B_x, B_y, C_x, C_y);          // right slope
        line(C_x, C_y, C_x, base_y);       // right vertical side (optional)
        line(B_x, base_y, C_x, base_y);    // base of right triangle

        // Update ball y position on slopes
        if (pos <= B_x)
            y = A_y + m1 * (pos - A_x);
        else
            y = B_y + m2 * (pos - B_x);

        // Draw ball
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        fillellipse((int)pos, (int)(y - radius), radius, radius);

        // Move ball
        pos += step;
        if (pos > C_x)
            pos = A_x;

        delay(20);
    }

    getch();
    closegraph();
    return 0;
}
