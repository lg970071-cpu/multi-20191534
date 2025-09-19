#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

void moveCursor(int x, int y) {
    printf("\x1b[%d;%dH", y, x);
}

void printBomb(int x, int y, int isExploded) {
    if(isExploded) {
        moveCursor(x - 4, y - 1);
        printf("  ^^^^^^^  ");
        moveCursor(x - 4, y);
        printf(" !!BAM!! ");
        moveCursor(x - 4, y + 1);
        printf("  ^^^^^^^  ");
    } else {
        moveCursor(x, y);
        printf("( b )");
    }
}

typedef struct {
    int x;
    int y;
} Point;

int main() {
    const int FUSE_LENGTH = 68;
    Point path[FUSE_LENGTH];

    printf("\x1b[?25l");
    system("clear");

    const int num_segments = 12;
    int segment_lengths[] = {1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    
    int x = 14, y = 9;
    int path_index = 0;
    int direction = 2; // 0:UP, 1:LEFT, 2:DOWN, 3:RIGHT

    path[path_index].x = x;
    path[path_index].y = y;
    path_index++;

    for (int seg = 0; seg < num_segments; seg++) {
        for (int step = 0; step < segment_lengths[seg]; step++) {
            if (path_index >= FUSE_LENGTH) break;
            
            switch (direction) {
                case 0: y--; break;
                case 1: x--; break;
                case 2: y++; break;
                case 3: x++; break;
            }

            path[path_index].x = x;
            path[path_index].y = y;
            path_index++;
        }
        direction = (direction + 1) % 4;
    }
    
    Point bomb_pos = path[FUSE_LENGTH - 1];
    
    for (int i = 0; i < FUSE_LENGTH - 1; i++) {
        moveCursor(path[i].x, path[i].y);
        printf("#");
    }

    int bomb_x = bomb_pos.x - 2;
    int bomb_y = bomb_pos.y;
    printBomb(bomb_x, bomb_y, 0);
    fflush(stdout);
    
    for (int i = 0; i < FUSE_LENGTH; i++) {
        moveCursor(path[i].x, path[i].y);
        printf("*");
        
        fflush(stdout);
        usleep(200 * 1000);

        moveCursor(path[i].x, path[i].y);
        printf(" ");
    }
    
    moveCursor(bomb_x, bomb_y);
    printf("     ");
    
    printBomb(bomb_x, bomb_y, 1);

    moveCursor(0, 20);
    printf("\x1b[?25h");

    return 0;
}