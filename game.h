#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>//easyXͼ�ν����

#define  N		10
#define  SIZE	21     //ͼƬ�Ŀ��
#define  NUM    10   //�׵�����

int		map[N + 2][N + 2];
IMAGE	img[50];  //0 1 2 3 4 5 6 7 8 �� ��ͼ ��� 
int     hitNum;   //�Ѿ��㿪���������
int		rhitNum = 0;  //�Ҽ��������
time_t start_t, end_t, diff_t;
int a = 0, b = 0;//a�Ƿ��� b������

void	GameInit();
void	DrawMap();
int		PlayGame();
void fun(int x, int y);
