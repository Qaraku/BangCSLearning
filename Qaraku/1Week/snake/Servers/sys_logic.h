#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "snake.h"
void print_item(char a)
{
    printf("%c", a);
}
void gotoxy(int x, int y)
{
    COORD coord = {x, y}; // 坐标从 0 开始
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, coord);
}
void HideCursor()
{
    CONSOLE_CURSOR_INFO curInfo;                     // 定义光标信息的结构体变量
    curInfo.dwSize = 1;                              // 如果没赋值的话，光标隐藏无效
    curInfo.bVisible = FALSE;                        // 将光标设置为不可见
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    SetConsoleCursorInfo(handle, &curInfo);          // 设置光标信息
}
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); // 颜色设置
    // 注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}
void formatConsole()
{
    char chCmd[32];
    system("color 0a");
    system("title 贪吃蛇");
    sprintf(chCmd, "mode con cols=%d lines=%d", COLS * 2, ROWS + 2);
    system(chCmd);
}