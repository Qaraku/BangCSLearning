
#include "../Servers/display_handling.h"
// #define ROWS 40
// #define COLS 80

// 一维数组
// 	setvbuf(stdout, NULL, _IOFBF, 4096); // 1：修改刷新模式为手动刷新
// 	//然后画你要画的东西
// 	printf("...");
// 	fflush(stdout); // 2：清空并输出缓冲区的内容
// 	setvbuf(stdout, NULL, _IOLBF, 4096); // 3：刷新模式改回去
// }

int main()
{
    char key = 0;
    int *t = NULL;
    init_face();
    init_snake();
    print_snake();
    formatConsole();
    print_wall();
    HideCursor();
    srand((unsigned int)time(NULL));
    RandFOOD();
    print_food(food.x, food.y);
    do
    {

        if (!food.exist)
        {
            RandFOOD();
            print_food(food.x, food.y);
        }
        key = getch();
        move_snake(key);
        Judge_Sfood();
        print_snake();
        setbuf(stdin, NULL);
        gotoxy(0, ROWS);
        printf("%d %d   ", snake.x, snake.y);
        for (int i = 0; i < snake.len; i++)
        {
            printf("x:%d y:%d ", body[i].x, body[i].y);
        }
        continue;
    } while (key != Esc);
    exit(0);
}

// gotoxy(0, ROWS);
// printf("%d", rand());