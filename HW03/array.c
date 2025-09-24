#include <stdio.h>
#include <stdlib.h>

#define Key_a 97
#define Key_z 122

int swap(char* a, char* b)
{
    char c;
    c = *a;
    *a = *b;
    *b = c;
    return 0; // swap 함수는 반환형이 int이므로 0을 반환하도록 수정
}

int main()
{
    char random[Key_z - Key_a + 1];
    int length = Key_z - Key_a + 1; // 배열의 길이를 변수에 저장

    // 배열 초기화
    int i = 0;
    for (i = 0; i < length; i++)
    {
        random[i] = 0;
    }

    // 배열에 알파벳 무작위로 채우기
    for (i = 0; i < length; i++)
    {
        while (1)
        {
            int rand_index = rand() % length;
            if (random[rand_index] == 0)
            {
                random[rand_index] = (char)(i + Key_a);
                break;
            }
        }
    }

    // 버블 정렬 적용
    for (i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            // 현재 요소가 다음 요소보다 크면 (알파벳 순서로 뒤에 있으면)
            if (random[j] > random[j + 1])
            {
                // 두 요소의 위치를 교환
                swap(&random[j], &random[j + 1]);
            }
        }
    }

    // 정렬된 결과 출력
    printf("\t\trandom\n");
    for (i = 0; i < length; i++)
    {
        printf("\n\t%d\t%c", i, random[i]);
    }

    return 0;
}