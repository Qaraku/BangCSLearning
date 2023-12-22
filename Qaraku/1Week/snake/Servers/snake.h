// snake程序必须头文件引入，必要参数定义
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define ROWS 40 // 屏幕行数
#define COLS 40 // 屏幕列数
// define some status
#define KONG 0
#define HEAD 1
#define FOOD 2
#define WALL 3
#define BODY 5
// define some operations
#define Esc 27
#define Space 32
#define Tab 9
#define Enter 13
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
int face[ROWS][COLS];
struct Snake
{
    int len;
    int x;
    int y;
} snake;
struct Snake_Body
{
    int x;
    int y;
} body[ROWS * COLS];
