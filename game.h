#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>//easyX图形界面库

#define  N		10
#define  SIZE	21     //图片的宽度
#define  NUM    10   //雷的总数

int		map[N + 2][N + 2];
IMAGE	img[50];  //0 1 2 3 4 5 6 7 8 雷 地图 标记 
int     hitNum;   //已经点开方格的数量
int		rhitNum = 0;  //右键点击数量
time_t start_t, end_t, diff_t;
int a = 0, b = 0;//a是分钟 b是秒数

void	GameInit();
void	DrawMap();
int		PlayGame();
void fun(int x, int y);
