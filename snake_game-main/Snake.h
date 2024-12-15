//
// Created by g1874 on 24-11-30.
//

#ifndef C_SNAKE_MASTER_SNAKE_H
#define C_SNAKE_MASTER_SNAKE_H
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#ifdef _WIN32
#include <conio.h>  // Windows系统特有的conio.h头文件
    #include <windows.h>
#else
#include <sys/select.h> // select 函数和 fd_set 的定义
#include <termios.h>  //Linux
#include <unistd.h>
#endif

// 跨平台清屏
void clearScreen();
// 跨平台设置光标可见性
void setCursorVisibility(int visible);
// 跨平台 Sleep 函数，参数单位为毫秒
void crossPlatformSleep(int milliseconds);
// 跨平台的getch实现
char myGetch();
// 跨平台实现的_kbhit函数
int myKbhit();
//跨平台gotoxy实现
void gotoxy(int x, int y);

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define PAUSE ' '
#define WIDTH 52
#define HEIGHT 27
#define NAME_SIZE 128
#define MAX_PLAYER 1024
#define MAX_OBT 4

// * 链表实现贪吃蛇身体
typedef struct Snake
{
    int x;
    int y;
    struct Snake *next;
}Snake;
// * 将食物的坐标和分数存在一个结构体里面，食物的分数高低由难度决定
typedef struct Food
{
    int x;
    int y;
    int score;
}Food;

typedef struct PlayerInfo
{
    char name[NAME_SIZE];
    int high_score;
    int play_times;
}Player;

typedef struct Obstacle
{
    int x;
    int y;
}Obstacle;

// ************************************************************************
// *
// * 游戏中的全局变量
// *
// ************************************************************************
extern char cGameScene[HEIGHT][WIDTH];             // 设计游戏场景大小为 50 x 25
extern char cUserName[NAME_SIZE];
extern int iTotalScore;
extern int iLastScore;
extern int iTotalTimes ;
extern int iDifficulty ;
extern int iRefreshTimes[4];
extern int iGameOver;
extern int iFoodSpawned ;
extern char cControl;
extern Snake *head, *tail;
extern Food food;
extern int iCountObt;
extern Obstacle *obstacles;
// ************************************************************************
// *
// * 游戏中的全局函数
// *
// ************************************************************************
void initGame();             // 初始化游戏场景，和全局变量
void refreshScreen();        // 每一帧的屏幕刷新
void gameLoop();             // 游戏逻辑主循环

void enterUsername();                            // 刚进入游戏时，选择是新建玩家还是读取存档
void startMenu();                                // 开始游戏后的选择菜单
void chooseDifficulty();                         // 选择游戏难度
void displayScoreBoard();                        // 显示排行榜
void myInfo();                                   // 显示我的信息
void gameOver();                                 // 游戏结束页面
void updateScoreBoard();                         // 更新排行榜
void spawnFood();
void updateSnakeShape();
extern void game_main();


//需要实现的函数
extern int randInt(int min, int max);
extern int ifGameOver();
extern void sortPlayerList (Player * playerList , int iPlayerCount);
extern void headChange(char cControl);



#endif //C_SNAKE_MASTER_SNAKE_H
