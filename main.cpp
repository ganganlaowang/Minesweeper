#include "game.h"
//������
int main()
{
	HWND hwnd = GetHWnd(); //���ڻ�ȡ��ͼ���ھ��,�� Windows �£������һ�����ڵı�ʶ���õ�����󣬿���ʹ�� Windows API �еĺ���ʵ�ֶԴ��ڵĿ��ơ�
	initgraph(SIZE*N, SIZE*(N +2)); //��һ������
	if (MessageBox(hwnd, L"��Ҫ��ʼ��Ϸ��", L"��ʾ", MB_YESNO) == IDNO)//ѡ��NO ���˳���Ϸ �������
		exit(0);
	GameInit();
	putimage(0, 0, &img[12]);
	time(&start_t); //��ȡ��Ϸ��ʼʱ��  time() ��ָ����January 1 1970 00:00:00 ��ĵ�ǰʱ��������ĺ�������Ҫ������ȡ��ǰ��ϵͳʱ�䣬���صĽ����һ��time_t����
	int flag;
	while (1)
	{
		GameInit();
		while (1)
		{
			DrawMap();
			flag = PlayGame();
			if (flag == 49)  //�ȵ�����
			{
				time(&end_t);//��ȡ��Ϸ����ʱ��
				diff_t = difftime(end_t, start_t);//������Ϸ��ʱ
				b = diff_t % 60;//��������ʱ���λ������
				a = diff_t / 60;//��������ʱ���λ�������
				for (int i = 1; i <= N; i++)
				{
					for (int j = 1; j <= N; j++)
					{
						if (map[i][j] == -1)  //���ϱ�ǵ�ͼƬ
							map[i][j] += 10;//��������δ��ǵĵ��ף���ʹ����ʾ����
						else if (map[i][j] >= 30 && map[i][j] < 40)//������󷽸������
							map[i][j] += 20;//�����������ǵķ��񣬲���keilboomͼƬ��ʾ
					}
				}
				DrawMap();//���Ƴ��ȵ����׺�����ڵ���Ϸ����
				putimage(91, 4, &img[27]);//��91�� ��4�� ����ͼƬ27
				MessageBox(hwnd, L"��ʧ����,�ٽ�����!", L"��ʾ", MB_OK);
				break;
			}
			//hitNum �㿪�ĸ��� + NUM�׵�����  = 100
			else if (N*N - hitNum == NUM&&NUM == rhitNum)//�㿪ȫ�����׸����Ҳ�����ȷ���ӣ�����Ϸʤ��
			{
				time(&end_t);
				diff_t = difftime(end_t, start_t);
				b = diff_t % 60;//��������ʱ���λ������
				a = diff_t / 60;//��������ʱ���λ�������
				DrawMap();
				putimage(91, 4, &img[28]);
				MessageBox(hwnd, L"��Ӯ��!!", L"��ʾ", MB_OK);
				break;
			}
		}
		a = 0, b = 0, rhitNum = 0;//������Ϸ
		if (MessageBox(hwnd, L"����һ��?", L"", MB_RETRYCANCEL) == IDCANCEL)//���ȡ�����˳���Ϸ
			break;
		else
			time(&start_t);//���¼�ʱ
	}
	closegraph();
	return 0;
}

//��Ϸ��ʼ��
void GameInit()
{
	int i, j, m, n;
	hitNum = 0;
	//���������
	srand((unsigned int)time(NULL));//��֤ÿ��������õ���λ�ò�ͬ��ʹ��ϵͳʱ������ʼ��
	//��ʼ������
	for (i = 0; i < N + 2; i++)//��ֹԽ��
	{
		for (j = 0; j < N + 2; j++)
		{
			map[i][j] = 0;
		}
	}

	//��ʼ���� 
	for (i = 0; i < NUM;)  //10��ѭ�� 10����
	{
		m = rand() % N + 1;		//������� 1 - 10
		n = rand() % N + 1;    //������� 1 - 10
		if (map[m][n] == 0)       //û������� ����֤��������ظ�����
		{
			map[m][n] = -1;       //��ά������ -1��ʾ��
			i++;
		}
	}

	//��ʼ����֮���Ԫ��  �����׵ķֲ���� ȥ��������Ԫ��
	for (i = 1; i <= N; i++)  //����10��10��
	{
		for (j = 1; j <= N + 1; j++)
		{
			if (map[i][j] == 0)  //������
			{
				//����9����
				for (m = i - 1; m <= i + 1; m++) //3��
				{
					for (n = j - 1; n <= j + 1; n++) //3��
					{
						if (map[m][n] == -1)  //����һ����
						{
							map[i][j]++;
						}
					}
				}
			}
		}
	}

	//����ͼƬ
	loadimage(&img[0], L"./res/0.BMP", SIZE, SIZE);
	loadimage(&img[1], L"./res/1.BMP", SIZE, SIZE);
	loadimage(&img[2], L"./res/2.BMP", SIZE, SIZE);
	loadimage(&img[3], L"./res/3.BMP", SIZE, SIZE);
	loadimage(&img[4], L"./res/4.BMP", SIZE, SIZE);
	loadimage(&img[5], L"./res/5.BMP", SIZE, SIZE);
	loadimage(&img[6], L"./res/6.BMP", SIZE, SIZE);
	loadimage(&img[7], L"./res/7.BMP", SIZE, SIZE);
	loadimage(&img[8], L"./res/8.BMP", SIZE, SIZE);
	loadimage(&img[9], L"./res/��.BMP", SIZE, SIZE);
	loadimage(&img[10], L"./res/��ͼ.BMP", SIZE, SIZE);
	loadimage(&img[11], L"./res/���.BMP", SIZE, SIZE);
	loadimage(&img[12], L"./res/��.BMP", SIZE*N, SIZE*2);
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

//���Ƶ�ͼ 
void DrawMap()
{
	
	putimage(91,4, &img[26]);
	putimage(5 + SIZE * 7 / 9, 5, &img[23]);
	putimage(185 - SIZE * 14 / 9, 5, &img[23]);
	putimage(185 - SIZE * 7 / 3 + 1, 5, &img[23]);
	switch ((NUM-rhitNum)%10)//ʣ������
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
	switch ((NUM - rhitNum) / 10)//ʣ������
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
	switch (b / 10)//��ʮλ������
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
	switch (b % 10)//����λ������
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
	switch (a % 10)//������
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

	//����ͼ����ͼƬ
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j] == 49)  //���ϲȵ����׵�ͼƬ
				putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[24]);
			else if (map[i][j] > 50)  //���ϱ�Ǵ���ĵ���ͼƬ
				putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[25]);
			else if (map[i][j] >= 29 && map[i][j] < 40)  //���ϱ�ǵ�ͼƬ
				putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[11]);
			else if (map[i][j] <= 20)
			{
				switch (map[i][j])  //���ݶ�ά�����Ԫ��������  ����
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
					putimage((i - 1) * SIZE, (j + 1) * SIZE, &img[10]);  //�հ׵ķ�����ƽ�ȥ
					break;
				}
			}
		}
	}
}

//����Ϸ
int PlayGame()
{
	//����һ�������Ϣ
	MOUSEMSG msg = { 0 };
	msg = GetMouseMsg();  //��ȡ�����Ϣ
	switch (msg.uMsg)  //��굱ǰ�������Ϣ��ʲô
	{
		//����������  ��������
	case WM_LBUTTONDOWN:  //  L left   BUTTON ��ť  DOWN ��
		if (map[msg.x / SIZE + 1][msg.y / SIZE - 1] == 0) 
		{
			fun(msg.x / SIZE + 1, msg.y / SIZE - 1);
		}
		else if (map[msg.x / SIZE + 1][msg.y / SIZE - 1] == -1) //�ȵ���
			map[msg.x / SIZE + 1][msg.y / SIZE - 1] += 50;
		else if (map[msg.x / SIZE + 1][msg.y / SIZE - 1] < 9)  //����������������-1 0 1 2 3 4 5 6 7 8  
		{
			map[msg.x / SIZE + 1][msg.y / SIZE - 1] += 10;// ����
			hitNum++;
		}
		return map[msg.x / SIZE + 1][msg.y / SIZE - 1]; //���ص㵽�������Ϣ
		break;
		//�����Ҽ����  ��Ƿ��� ����ȷ����
	case WM_RBUTTONDOWN:
		if (map[msg.x / SIZE + 1][msg.y / SIZE - 1] < 9)  //û�б�������
		{
			map[msg.x / SIZE + 1][msg.y / SIZE - 1] += 30;
			rhitNum++;
		}
		else if (map[msg.x / SIZE + 1][msg.y / SIZE - 1]>20)  //�Ѿ�����ǵ�
		{
			map[msg.x / SIZE + 1][msg.y / SIZE - 1] -= 30;
			rhitNum--;
		}
		return 0;
		break;
	}
}

//չ����Χ�ǵ��׵ķ���
void fun(int x, int y)
{
	//�ȴ���������0
	map[x][y] += 10;
	hitNum++;
	//�ݹ飬չ�������ǵ��׷���
	for (int m = x - 1; m <= x + 1; m++)
	{
		for (int n = y - 1; n <= y + 1; n++)
		{
			if (m >= 1 && m <= N && n >= 1 && n <= N)
			{
				if (map[m][n] < 9)  //û�з�����
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
