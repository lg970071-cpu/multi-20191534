#include <stdio.h>
#include <math.h>
#include <unistd.h> // macOS용 usleep 함수를 사용하기 위한 헤더 파일

#define PI 3.14159226535897

void moveCursor(int x, int y)
{
    printf("\x1b[%d;%dH",y,x);
}

// 매개변수 isExploded
// 0: 폭발전 폭탄
// 1: 폭발함
void printBomb(int isExploded)
{
    if(isExploded)
    { 
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!"); 
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else
        printf("(  b  )"); 
}

int main()
{
    // 여기부터 코드를 작성하세요----------------------

    // 심지 시작 위치 설정 (문제에서 주어진 14, 9와는 다르게, 14, 9에서 시작하도록 수정)
    int fuse_x = 14;
    int fuse_y = 9;

    // 폭탄 위치
    int bomb_x = 15;
    int bomb_y = 10;

    // 초기 화면 정리
    printf("\x1b[2J");
    printf("\x1b[H");

    // 폭탄 그리기
    moveCursor(bomb_x, bomb_y);
    printBomb(0);

    // 심지 그리기 (나선형)
    double angle = 0;
    int steps = 50;
    for (int i = 0; i < steps; i++) {
        double radius = 0.3 * angle;
        int x = (int)(radius * cos(angle)) + fuse_x;
        int y = (int)(radius * sin(angle)) + fuse_y;
        moveCursor(x, y);
        printf("#");
        angle += 0.2;
    }

    // 불꽃(*) 초기 위치
    moveCursor(fuse_x, fuse_y);
    printf("*");
    fflush(stdout);

    // 심지 태우기
    angle = 0;
    for (int i = 0; i < steps; i++) {
        // 이전 위치 지우기
        double old_radius = 0.3 * (angle - 0.2);
        int old_x = (int)(old_radius * cos(angle - 0.2)) + fuse_x;
        int old_y = (int)(old_radius * sin(angle - 0.2)) + fuse_y;
        moveCursor(old_x, old_y);
        printf(" ");
        
        // 새 위치에 * 그리기
        double new_radius = 0.3 * angle;
        int new_x = (int)(new_radius * cos(angle)) + fuse_x;
        int new_y = (int)(new_radius * sin(angle)) + fuse_y;
        moveCursor(new_x, new_y);
        printf("*");
        fflush(stdout);
        
        // 폭탄에 도달했는지 확인 (단순하게 좌표 비교)
        if (new_x == bomb_x && new_y == bomb_y) {
            break;
        }

        usleep(200000); // 200ms 대기
        angle += 0.2;
    }

    // 폭파
    moveCursor(bomb_x, bomb_y);
    printBomb(1);
    fflush(stdout);

    // 폭파 후 잠시 대기
    usleep(2000000); // 2초 대기

    // 화면 정리 및 커서 이동
    printf("\x1b[2J");
    printf("\x1b[H");

    // 여기까지 코드를 작성하세요----------------------
    moveCursor(10, 20);
    return 0;
}