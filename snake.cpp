// snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define SNAKE_NUM 500  //蛇的最大节数
#define SNAKE_L 640
#define SNAKE_W 480
//蛇的结构
struct Sneak
{
    int size;
    int dir;
    int speed;
    POINT coor[SNAKE_NUM];
}snake;
struct Food
{
    bool flag;//食物是否被吃
    int dir;//食物半径
    int x;
    int y;
    DWORD color;//食物颜色
}food;
enum DIR //枚举蛇的方向
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};
void FoodInit()
{
    srand(GetTickCount());//设置种子
    //初始化食物，rand（）随机产生一个整数，如果没有设置随机数种子，每次产生的都是固定的整数
    //设置种子需要头文件stdlib.h
    food.x = rand() % SNAKE_L;
    food.y = rand() % SNAKE_W;
    food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
    food.dir = 10;
    food.flag = true;
}
//数据的初始化
void GameInit()
{
    //播放背景音乐
    mciSendString("open ./love.mp3 alias BGM",0,0,0);
    mciSendString("play BGM repeat",0,0,0);
    initgraph(SNAKE_L, SNAKE_W); //init初始化graph窗口
   // srand(GetTickCount());//设置种子
    //初始化蛇
    snake.size = 3;
    snake.speed = 10;
    snake.dir=RIGHT; 
    for (int i = 0; i < snake.size; i++)
    {
        snake.coor[i].x=40-10*i;
        snake.coor[i].y=10;
    }
    //初始化食物，rand（）随机产生一个整数，如果没有设置随机数种子，每次产生的都是固定的整数
    //设置种子需要头文件stdlib.h
 /*  food.x = rand() % SNAKE_L;
    food.y = rand() % SNAKE_W;
    food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
    food.dir = 10;
    food.flag = true;
*/ 
    FoodInit();
}

void GameDraw() 
{
    //双缓冲绘图，防止闪屏
    BeginBatchDraw();
    //设置背景颜色
    setbkcolor(RGB(87, 163, 30));
    cleardevice();  //是用当前背景色清空屏幕，并将当前点移至 (0, 0)。
    //绘制蛇
    for(int i=0;i<snake.size;i++){
        solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
    }
    if (food.flag)
    {
        solidcircle(food.x, food.y, food.dir);
    }
    EndBatchDraw();
}
//移动蛇
void SnakeMove()
{
    for (int i = snake.size - 1; i > 0; i--)
    {
        snake.coor[i] = snake.coor[i - 1];
    }

    switch (snake.dir)
    {
    case RIGHT:
            snake.coor[0].x += snake.speed;
        break;
    case LEFT:
            snake.coor[0].x -= snake.speed;
        break;
    case UP:
        snake.coor[0].y -= snake.speed;
        break;
    case DOWN:
        snake.coor[0].y += snake.speed;
        break;
    }
    if (snake.coor[0].x < 0) snake.coor[0].x = SNAKE_L;
    if (snake.coor[0].y < 0) snake.coor[0].y = SNAKE_W;
    if (snake.coor[0].x > SNAKE_L) snake.coor[0].x = 0;
    if (snake.coor[0].y > SNAKE_W) snake.coor[0].y = 0;
}
//按键改变方向
void KeyControl()
{
    //判断是否有按键,有按键返回true
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
        case 'W':
        case 72: //72 80 75 77  “上下左右”键返回的getch（）键值
            if(snake.dir!=DOWN) snake.dir = UP;
            break;
        case 'a':
        case'A':
        case 75:
            if(snake.dir!=RIGHT) snake.dir = LEFT;
            break;
        case 's':
        case'S':
        case 80:
            if(snake.dir!=UP)snake.dir = DOWN;
            break;
        case 'd':
        case'D':
        case 77:
            if(snake.dir!=LEFT)snake.dir = RIGHT;
            break;
        case ' ':
            while (_getch() != ' ') break;//空格暂停
        }
    }

}
//吃食物判定
void EatFood()
{
    if (food.flag==true&&snake.coor[0].x < food.x + food.dir && snake.coor[0].y < food.y + food.dir
        && snake.coor[0].x>food.x - food.dir && snake.coor[0].y>food.y - food.dir)
    {
        food.flag = false;
        snake.size++;
    }
    if (!food.flag)
    {
        FoodInit();
    }

}

int main()
{
    GameInit(); GameDraw();
    while (1) { 
        GameDraw();
        KeyControl();
        SnakeMove();
        EatFood();
        Sleep(20);
    }
    return 0;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
