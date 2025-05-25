#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

int midx, midy, radius;
float h_angle, m_angle, s_angle;
struct time t;
int i;

void drawClock()
{
    circle(midx, midy, radius);
    circle(midx, midy, radius + 5);

    for(i = 1; i <= 12; i++)
    {
        int x = midx + (int)((radius - 20) * cos(i * 30 * 3.14159 / 180 - 3.14159 / 2));
        int y = midy + (int)((radius - 20) * sin(i * 30 * 3.14159 / 180 - 3.14159 / 2));
        circle(x, y, 2);  // Small circle for each hour
    }
}

void drawHands()
{
    int s_x, s_y, m_x, m_y, h_x, h_y;

    gettime(&t); // Get current time

    // Convert time to angles (in radians)
    s_angle = t.ti_sec * 6 * 3.14159 / 180 - 3.14159 / 2;
    m_angle = t.ti_min * 6 * 3.14159 / 180 - 3.14159 / 2;
    h_angle = (t.ti_hour % 12 + t.ti_min / 60.0) * 30 * 3.14159 / 180 - 3.14159 / 2;

    // Second hand coordinates
    s_x = midx + (int)((radius - 10) * cos(s_angle));
    s_y = midy + (int)((radius - 10) * sin(s_angle));

    // Minute hand coordinates
    m_x = midx + (int)((radius - 20) * cos(m_angle));
    m_y = midy + (int)((radius - 20) * sin(m_angle));

    // Hour hand coordinates
    h_x = midx + (int)((radius - 40) * cos(h_angle));
    h_y = midy + (int)((radius - 40) * sin(h_angle));

    // Draw second hand
    setcolor(RED);
    line(midx, midy, s_x, s_y);

    // Draw minute hand
    setcolor(GREEN);
    line(midx, midy, m_x, m_y);

    // Draw hour hand
    setcolor(BLUE);
    line(midx, midy, h_x, h_y);
}

void main(void)
{
    int gd = DETECT, gm;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;
    radius = 100;

    while (!kbhit())
    {
        cleardevice();      // Clear screen
        drawClock();        // Draw clock outline
        drawHands();        // Draw hands
        delay(1000);        // Update every second
    }

    getch();                // Wait for key press
    closegraph();           // Close graphics
}