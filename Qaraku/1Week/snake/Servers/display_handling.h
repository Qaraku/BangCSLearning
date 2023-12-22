#include "game_logic.h"
void print_snake()
{
    gotoxy(snake.x * 2, snake.y);
    color(5);
    printf("☯"); // ●
    gotoxy(0, ROWS);
}

void print_wall()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (face[i][j] == WALL && (i == 0 || i == ROWS))
            {
                printf("■ ");
            }
            else if (face[i][j] == WALL)
            {
                printf("■ ");
            }
            else
            {
                printf("  ");
            }
        }
    }
}
