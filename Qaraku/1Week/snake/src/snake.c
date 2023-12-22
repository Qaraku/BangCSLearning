
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
    init_face();
    init_snake();
    formatConsole();
    print_wall();
    HideCursor();
    do
    {

        key = getch();
        move_snake(key);
        print_snake();
        // gotoxy(0, ROWS);
        printf("%d", rand());
        // RandFOOD();
        setbuf(stdin, NULL);
        continue;
    } while (key != Esc);
    exit(0);
}