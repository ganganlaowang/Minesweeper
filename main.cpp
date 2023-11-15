#include "game.h"
//主函数
int main()
{
	HWND hwnd = GetHWnd(); //用于获取绘图窗口句柄,在 Windows 下，句柄是一个窗口的标识，得到句柄后，可以使用 Windows API 中的函数实现对窗口的控制。
	initgraph(SIZE*N, SIZE*(N +2)); //打开一个窗口
	if (MessageBox(hwnd, L"您要开始游戏吗", L"提示", MB_YESNO) == IDNO)//选择NO 则退出游戏 否则继续
		exit(0);
	GameInit();
	putimage(0, 0, &img[12]);
	time(&start_t); //读取游戏开始时间  time() 是指返回January 1 1970 00:00:00 起的当前时间的秒数的函数，主要用来获取当前的系统时间，返回的结果是一个time_t类型
	int flag;
	while (1)
	{
		GameInit();
		while (1)
		{
			DrawMap();
			flag = PlayGame();
			if (flag == 49)  //踩到地雷
			{
				time(&end_t);//读取游戏结束时间
				diff_t = difftime(end_t, start_t);//计算游戏用时
				b = diff_t % 60;//计算所用时间进位后秒数
				a = diff_t / 60;//计算所用时间进位后分钟数
				for (int i = 1; i <= N; i++)
				{
					for (int j = 1; j <= N; j++)
					{
						if (map[i][j] == -1)  //贴上标记的图片
							map[i][j] += 10;//遍历出来未标记的地雷，并使其显示出来
						else if (map[i][j] >= 30 && map[i][j] < 40)//满足错误方格的条件
							map[i][j] += 20;//遍历出错误标记的方格，并用keilboom图片表示
					}
				}
				DrawMap();//绘制出踩到地雷后的现在的游戏画面
				putimage(91, 4, &img[27]);//第91列 第4行 放置图片27
				MessageBox(hwnd, L"你失败了,再接再厉!", L"提示", MB_OK);
				break;
			}
			//hitNum 点开的个数 + NUM雷的数量  = 100
			else if (N*N - hitNum == NUM&&NUM == rhitNum)//点开全部非雷格子且插满正确旗子，则游戏胜利
			{
				time(&end_t);
				diff_t = difftime(end_t, start_t);
				b = diff_t % 60;//计算所用时间进位后秒数
				a = diff_t / 60;//计算所用时间进位后分钟数
				DrawMap();
				putimage(91, 4, &img[28]);
				MessageBox(hwnd, L"你赢了!!", L"提示", MB_OK);
				break;
			}
		}
		a = 0, b = 0, rhitNum = 0;//重置游戏
		if (MessageBox(hwnd, L"再玩一局?", L"", MB_RETRYCANCEL) == IDCANCEL)//点击取消，退出游戏
			break;
		else
			time(&start_t);//重新计时
	}
	closegraph();
	return 0;
}

//游戏初始化
void GameInit()
{
	int i, j, m, n;
	hitNum = 0;
	//随机数种子
	srand((unsigned int)time(NULL));//保证每次随机布置地雷位置不同，使用系统时间来初始化
	//初始化数组
	for (i = 0; i < N + 2; i++)//防止越界
	{
		for (j = 0; j < N + 2; j++)
		{
			map[i][j] = 0;
		}
	}

	//初始化雷 
	for (i = 0; i < NUM;)  //10个循环 10个雷
	{
		m = rand() % N + 1;		//随机的行 1 - 10
		n = rand() % N + 1;    //随机的列 1 - 10
		if (map[m][n] == 0)       //没有埋过雷 ，保证不会出现重复的雷
		{
			map[m][n] = -1;       //二维数组中 -1表示雷
			i++;
		}
	}

	//初始化雷之外的元素  根据雷的分布情况 去填充数组的元素
	for (i = 1; i <= N; i++)  //遍历10行10列
	{
		for (j = 1; j <= N + 1; j++)
		{
			if (map[i][j] == 0)  //不是雷
			{
				//遍历9宫格
				for (m = i - 1; m <= i + 1; m++) //3行
				{
					for (n = j - 1; n <= j + 1; n++) //3列
					{
						if (map[m][n] == -1)  //就是一个雷
						{
							map[i][j]++;
						}
					}
				}
			}
		}
	}

	//载入图片
	loadimage(&img[0], L"./res/0.BMP", SIZE, SIZE);
	loadimage(&img[1], L"./res/1.BMP", SIZE, SIZE);
	loadimage(&img[2], L"./res/2.BMP", SIZE, SIZE);
	loadimage(&img[3], L"./res/3.BMP", SIZE, SIZE);
	loadimage(&img[4], L"./res/4.BMP", SIZE, SIZE);
	loadimage(&img[5], L"./res/5.BMP", SIZE, SIZE);
	loadimage(&img[6], L"./res/6.BMP", SIZE, SIZE);
	loadimage(&img[7], L"./res/7.BMP", SIZE, SIZE);
	loadimage(&img[8], L"./res/8.BMP", SIZE, SIZE);
	loadimage(&img[9], L"./res/雷.BMP", SIZE, SIZE);
	loadimage(&img[10], L"./res/地图.BMP", SIZE, SIZE);
	loadimage(&img[11], L"./res/标记.BMP", SIZE, SIZE);
	loadimage(&img[12], L"./res/框.BMP", SIZE*N, SIZE*2);
	loadimage(&img[13], L"./res/ele0.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[14], L"./res/ele1.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[15], L"./res/ele2.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[16], L"./res/ele3.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[17], L"./res/ele4.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[18], L"./res/ele5.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[19], L"./res/ele6.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[20], L"./res/ele7.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[21], L"./res/ele8.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[22], L"./res/ele9.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[23], L"./res/ele10.BMP", SIZE * 7 / 9, SIZE * 4 / 3);
	loadimage(&img[24], L"./res/clickboom.BMP", SIZE, SIZE);
	loadimage(&img[25], L"./res/keilboom.BMP", SIZE, SIZE);
	loadimage(&img[26], L"./res/smile.BMP", SIZE * 3 / 2, SIZE * 3 / 2);
	loadimage(&img[27], L"./res/lose.BMP", SIZE * 3 / 2, SIZE * 3 / 2);
	loadimage(&img[28], L"./res/proud.BMP", SIZE * 3 / 2, SIZE * 3 / 2);
}

//绘制地图 
void DrawMap()
{
	
	putimage(91,4, &img[26]);
	putimage(5 + SIZE * 7 / 9, 5, &img[23]);
	putimage(185 - SIZE * 14 / 9, 5, &img[23]);
	putimage(185 - SIZE * 7 / 3 + 1, 5, &img[23]);
	switch ((NUM-rhitNum)%10)//剩余雷数
	{
	case 0:
		putimage(185, 5, &img[13]);
		break;
	case 9:
		putimage(185, 5, &img[22]);
		break;
	case 8:
		putimage(185, 5, &img[21]);
		break;
	case 7:
		putimage(185, 5, &img[20]);
		break;
	case 6:
		putimage(185, 5, &img[19]);
		break;
	case 5:
		putimage(185, 5, &img[18]);
		break;
	case 4:
		putimage(185, 5, &img[17]);
		break;
	case 3:
		putimage(185, 5, &img[16]);
		break;
	case 2:

		putimage(185, 5, &img[15]);
		break;
	case 1:

		putimage(185, 5, &img[14]);
		break;
	default:
		putimage(185, 5, &img[23]);
		
	}
	switch ((NUM - rhitNum) / 10)//剩余雷数
	{	
	case 0:
		putimage(185 - SIZE * 7 / 9, 5, &img[13]);
		break;
	case 1:
		putimage(185 - SIZE * 7 / 9, 5, &img[14]);
		break;
	case 2:
		putimage(185 - SIZE * 7 / 9, 5, &img[15]);
		break;
	case 3:
		putimage(185 - SIZE * 7 / 9, 5, &img[16]);
		break;
	case 4:
		putimage(185 - SIZE * 7 / 9, 5, &img[17]);
		break;
	case 5:
		putimage(185 - SIZE * 7 / 9, 5, &img[18]);
		break;
	case 6:
		putimage(185 - SIZE * 7 / 9, 5, &img[19]);
		break;
	case 7:
		putimage(185 - SIZE * 7 / 9, 5, &img[20]);
		break;
	case 8:
		putimage(185 - SIZE * 7 / 9, 5, &img[21]);
		break;
	case 9:
		putimage(185 - SIZE * 7 / 9, 5, &img[22]);
		break;
	default:
		putimage(185 - SIZE * 7 / 9, 5, &img[23]);
		break;
	}
	switch (b / 10)//贴十位的秒数
	{
	case 0:
		putimage(5 + SIZE * 14 / 9, 5, &img[13]);
		break;
	case 1:
		putimage(5 + SIZE * 14 / 9, 5, &img[14]);
		break;
	case 2:
		putimage(5 + SIZE * 14 / 9, 5, &img[15]);
		break;
	case 3:
		putimage(5 + SIZE * 14 / 9, 5, &img[16]);
		break;
	case 4:
		putimage(5 + SIZE * 14 / 9, 5, &img[17]);
		break;
	case 5:
		putimage(5 + SIZE * 14 / 9, 5, &img[18]);
		break;
	}
	switch (b % 10)//贴个位的秒数
	{
	case 0:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[13]);
		break;
	case 1:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[14]);
		break;
	case 2:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[15]);
		break;
	case 3:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[16]);
		break;
	case 4:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[17]);
		break;
	case 5:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[18]);
		break;
	case 6:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[19]);
		break;
	case 7:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[20]);
		break;
	case 8:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[21]);
		break;
	case 9:
		putimage(5 + SIZE * 7 / 3 - 1, 5, &img[22]);
		break;
	}
	switch (a % 10)//贴分钟
	{
	case 0:
		putimage(5, 5, &img[13]);
		break;
	case 1:
		putimage(5, 5, &img[14]);
		break;
	case 2:
		putimage(5, 5, &img[15]);
		break;
	case 3:
		putimage(5, 5, &img[16]);
		break;
	case 4:
		putimage(5, 5, &img[17]);
		break;
	case 5:
		putimage(5, 5, &img[18]);
		break;
	case 6:
		putimage(5, 5, &img[19]);
		break;
	case 7:
		putimage(5, 5, &img[20]);
		break;
	case 8:
		putimage(5, 5, &img[21]);
		break;
	case 9:
		putimage(5, 5, &img[22]);
		break;
	}

	//贴地图方格图片
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j] == 49)  //贴上踩到地雷的图片
				putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[24]);
			else if (map[i][j] > 50)  //贴上标记错误的地雷图片
				putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[25]);
			else if (map[i][j] >= 29 && map[i][j] < 40)  //贴上标记的图片
				putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[11]);
			else if (map[i][j] <= 20)
			{
				switch (map[i][j])  //根据二维数组的元素来绘制  加密
				{
				case 9:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[9]);
					break;
				case 10:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[0]);
					break;
				case 11:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[1]);
					break;
				case 12:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[2]);
					break;
				case 13:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[3]);
					break;
				case 14:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[4]);
					break;
				case 15:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[5]);
					break;
				case 16:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[6]);
					break;
				case 17:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[7]);
					break;
				case 18:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[8]);
					break;
				default:
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[10]);  //空白的方块绘制进去
					break;
				}
			}
		}
	}
}

//玩游戏
int PlayGame()
{
	//定义一个鼠标消息
	MOUSEMSG msg = { 0 };
	msg = GetMouseMsg();  //获取鼠标消息
	switch (msg.uMsg)  //鼠标当前的鼠标消息是什么
	{
		//鼠标的左键点击  翻开方格
	case WM_LBUTTONDOWN:  //  L left   BUTTON 按钮  DOWN 下
		if (map[msg.x / SIZE + 1][msg.y / SIZE - 1] == 0) 
		{
			fun(msg.x / SIZE + 1, msg.y / SIZE - 1);
		}
		else if (map[msg.x / SIZE + 1][msg.y / SIZE - 1] == -1) //踩到雷
			map[msg.x / SIZE + 1][msg.y / SIZE - 1] += 50;
		else if (map[msg.x / SIZE + 1][msg.y / SIZE - 1] < 9)  //表明方格代表的数字-1 0 1 2 3 4 5 6 7 8  
		{
			map[msg.x / SIZE + 1][msg.y / SIZE - 1] += 10;// 解密
			hitNum++;
		}
		return map[msg.x / SIZE + 1][msg.y / SIZE - 1]; //返回点到方格的信息
		break;
		//鼠标的右键点击  标记方格 代表确认雷
	case WM_RBUTTONDOWN:
		if (map[msg.x / SIZE + 1][msg.y / SIZE - 1] < 9)  //没有被翻开的
		{
			map[msg.x / SIZE + 1][msg.y / SIZE - 1] += 30;
			rhitNum++;
		}
		else if (map[msg.x / SIZE + 1][msg.y / SIZE - 1]>20)  //已经被标记的
		{
			map[msg.x / SIZE + 1][msg.y / SIZE - 1] -= 30;
			rhitNum--;
		}
		return 0;
		break;
	}
}

//展开周围非地雷的方块
void fun(int x, int y)
{
	//先打开这个点击的0
	map[x][y] += 10;
	hitNum++;
	//递归，展开其他非地雷方格
	for (int m = x - 1; m <= x + 1; m++)
	{
		for (int n = y - 1; n <= y + 1; n++)
		{
			if (m >= 1 && m <= N && n >= 1 && n <= N)
			{
				if (map[m][n] < 9)  //没有翻开的
				{
					if (map[m][n] != 0)
					{
						map[m][n] += 10;
						hitNum++;
					}
					else
					{
						fun(m, n);
					}
				}
			}
		}
	}
}
