#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double height;
    double width;

    Color color;

    /*
     * If use int as the type, the height of the pyramid will not be consistent so it will shake in the center.
     * Using double like the example above solves the problem.

    int x;
    int y;
    int height;
    int width;

    */

} rect;

int main() {

    int width = 800, height = 700;

    InitWindow(width, height, "genereate bricks with malloc()");

    // n:       how many disks you want
    // stop:    the maximum number of disks
    int n = 3, stop = 60;
    const int max_width = 500;

    // double because we have to calculate the disk height as double 
    const double max_height = 500;
    const int begin_x = (width - max_width)/2;

    rect * disk_p = (rect*)malloc(sizeof(rect) * n);

    for ( int i = 0 ; i < n ; ++i ) {
        disk_p[i].x = begin_x + (max_width/2 - max_width/2 * (i+1) / n);
        disk_p[i].y = 50 + (max_height  / n) * i;
        disk_p[i].width = max_width * ( i+1 ) / n;
        disk_p[i].height = (double)max_height / n;
        disk_p[i].color = (i%2) ? BLUE : SKYBLUE;
    }

    SetTargetFPS(60);

    double waitTime = 0.3;

    Vector2 LineBeginP = {disk_p[n-1].x - 20, disk_p[0].y };
    Vector2 LineEndP   = {disk_p[n-1].x - 20, disk_p[n-1].y + disk_p[n-1].height };

    while (!WindowShouldClose()) {

        BeginDrawing();
        
            ClearBackground(WHITE);

            DrawLineEx(LineBeginP, LineEndP, 5, RED);

            for ( int i = 0 ; i < n ; ++i ) {
                rect disk = disk_p[i];
                
                Vector2 vPos = {disk.x, disk.y};
                Vector2 vSize = {disk.width, disk.height};
                DrawRectangleV(vPos, vSize, disk.color);
            
            }

            WaitTime(waitTime);

            if ( n < stop) ++n;

            
            // re-allocate the memory since n changes
            disk_p = (rect*)realloc(disk_p, sizeof(rect) * n);
            
            // update variable
            for ( int i = 0 ; i < n ; ++i ) {
                disk_p[i].x = begin_x + (max_width/2 - max_width/2 * (i+1) / n);
                disk_p[i].y = 50 + (max_height  / n) * i;
                disk_p[i].width = max_width * ( i+1 ) / n;
                disk_p[i].height = max_height / n;
                disk_p[i].color = (i%2) ? BLUE : SKYBLUE;
            }

            // display current information
            char msg_n[100], msg_mem_size[100];
            sprintf(msg_n,        "n = %d", n);
            sprintf(msg_mem_size, "memory usage = %.3fKB", (int)sizeof(rect) * n / 1024.f );

            DrawText(msg_n, 200, 500 + 60, 40, BLUE);
            DrawText(msg_mem_size, 200, 550 + 60, 40, BLUE);


        EndDrawing();
    }

    free(disk_p);

    CloseWindow();

    return 0;
}
