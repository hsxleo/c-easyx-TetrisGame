#include<iostream>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")//��Ƶ
using namespace std;

int rotateIndex;  //��ת������±�
int score = 0;  //�÷�
int t = 300;   //�����ӳٵ�ʱ��
int downFlg;  //���������

//������ͼ
int map[20][10] = { 0 };
//����˹����ĸ�������
int block[28][4][4] = {
{
	{1,0,0,0},
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{1,1,0,0},
	{1,0,0,0},
	{1,0,0,0},
	{0,0,0,0},
},{
	{1,1,1,0},
	{0,0,1,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{0,1,0,0},
	{0,1,0,0},
	{1,1,0,0},
	{0,0,0,0},
},{
	{0,0,1,0},
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{1,0,0,0},
	{1,0,0,0},
	{1,1,0,0},
	{0,0,0,0},
},{
	{1,1,1,0},
	{1,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{1,1,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,0,0,0},
},{
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{0,1,0,0},
	{1,1,0,0},
	{1,0,0,0},
	{0,0,0,0},
},{
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{0,1,0,0},
	{1,1,0,0},
	{1,0,0,0},
	{0,0,0,0},
},{
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{1,0,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,0,0,0},
},{
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{1,0,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,0,0,0},
},{
	{0,1,0,0},
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{1,0,0,0},
	{1,1,0,0},
	{1,0,0,0},
	{0,0,0,0},
},{
	{1,1,1,0},
	{0,1,0,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{0,1,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,0,0,0},
},{
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
},{
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
},{
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
},{
	{1,1,0,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0},
}, {
	{1,1,0,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0},
}, {
	{1,1,0,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0},
}, {
	{1,1,0,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0},
}
};
//��������ֵ
void swap (int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}
//���Ƶ�ǰҪ����ķ���
void createBlock (int n) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j + 3] != 2)
				map[i][j + 3] = block[n][i][j];
		}
	}
}
//����������ͼ�ķ���
void drawMap () {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 0) {
				setfillcolor (WHITE);
				solidrectangle (30 * j, 30 * i, 30 * (j + 1), 30 * (i + 1));
			}
			if (map[i][j] == 1) {
				setfillcolor (BLUE);
				fillrectangle (30 * j, 30 * i, 30 * (j + 1), 30 * (i + 1));
			}
			if (map[i][j] == 2) {
				setfillcolor (RED);
				fillrectangle (30 * j, 30 * i, 30 * (j + 1), 30 * (i + 1));
			}
		}

	}
}
//�жϲ�����һ��
void clearLine () {
	for (int i = 0; i < 20; i++) {
		int k = 1;
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 0) {
				k = 0;
			}
		}
		if (k) {
			score += 10;
			for (int j = 0; j < 10; j++) {
				map[i][j] = 0;
			}
			for (int x = i - 1; x >= 0; x--) {
				for (int y = 0; y < 10; y++) {
					swap (map[x][y], map[x + 1][y]);
				}
			}
		}
	}
}
//�䵽����ķ����ɺ�ɫ�����޸��������ֵΪ2
void changeState () {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 1)
				map[i][j] = 2;
		}
	}
	clearLine ();
}
//������ת
void rotateBlock (int n) {
	int a = 20, b = 10;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 1) {
				if (i <= a) {
					a = i;
				}	
				if (j <= b) {
					b = j;
				}	
				break;
			}
		}
	}
	int r = 3;
	if (n >= 20 && n < 24) {
		r = 4;
	}

	//�ж��Ƿ������ת
	for (int i = r; i >= 0; i--) {
		for (int j = r; j >= 0; j--) {
			if (a + i > 19 || b + j > 10 || map[a + i - 1][b + j - 1] == 2) {
				return;
			}
		}
	}
	//����ת���ֵ
	for (int i = r - 1; i >= 0; i--) {
		for (int j = r - 1; j >= 0; j--) {
			map[a + i][b + j] = block[n][i][j];
		}
	}

}
//�ж����·����״̬
void judgeState () {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (i != 19 && map[i][j] == 1 && map[i + 1][j] == 2 || i == 19 && map[i][j] == 1) {
				changeState ();
				downFlg = 1;
			}
		}
	}
}
//�ƶ�����
void move () {
	if (!_kbhit ()) {
		judgeState ();
		//�����ƶ�
		for (int i = 18; i >= 0; i--) {
			for (int j = 9; j >= 0; j--) {
				if (map[i][j] == 1) {
					swap (map[i][j], map[i + 1][j]);
				}
			}
		}
	}
	else {
		int moveFlg = 1;
		int key = _getch ();
		//�ո���ͣ
		if (key == 32) {
			_getch ();
		}
		if (_kbhit ()) {
			int option = _getch ();
			switch (option) {
			case 75://��
				for (int i = 0; i < 20; i++) {
					for (int j = 0; j < 10; j++) {
						if (map[i][j] == 1) {
							if (j == 0 || map[i][j - 1] == 2) {
								moveFlg = 0;
							}
						}
					}
				}
				if (moveFlg) {
					for (int i = 0; i < 20; i++) {
						for (int j = 1; j < 10; j++) {
							if (map[i][j] == 1 && map[i][j - 1] == 0) {
								swap (map[i][j], map[i][j - 1]);
							}
						}
					}
				}
				break;
			case 77://��
				for (int i = 0; i < 20; i++) {
					for (int j = 0; j < 10; j++) {
						if (map[i][j] == 1) {
							if (j == 9 || map[i][j + 1] == 2) {
								moveFlg = 0;
							}
						}
					}
				}
				if (moveFlg) {
					for (int i = 0; i < 20; i++) {
						for (int j = 8; j >= 0; j--) {
							if (map[i][j] == 1 && map[i][j + 1] == 0) {
								swap (map[i][j], map[i][j + 1]);
							}
						}
					}
				}
				break;
			case 72://��
				rotateIndex++;
				rotateBlock (rotateIndex);  //��ת����
				if (rotateIndex % 4 == 3)
					rotateIndex -= 4;
				break;
			case 80://��
				t = 100;  //��������ʱ��
				break;
			}
		}
	}
}
//������һ������
void createNextBlock (int n) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (block[n][i][j] == 0) {
				setfillcolor (WHITE);
				solidrectangle (340 + 30 * j, 50 + 30 * i, 370 + 30 * j, 80 + 30 * i);
			}
			if (block[n][i][j] == 1) {
				setfillcolor (BLUE);
				fillrectangle (340 + 30 * j, 50 + 30 * i, 370 + 30 * j, 80 + 30 * i);
			}
		}
}
//�ж���Ϸ�Ƿ����
int isEnd () {
	for (int j = 0; j < 10; j++) {
		if (map[0][j] == 2) {
			return 1;
		}
	}
	return 0;
}
//������Ϸ����
void drawBackground () {
	setbkcolor (WHITE);
	cleardevice ();
	//����ֱ��
	setlinecolor (BLACK);

	settextcolor (BLACK);
	settextstyle (20, 0, "��������");
	outtextxy (330, 20, "��һ������:");
	outtextxy (330, 290, "��Ϸ˵��");
	outtextxy (330, 320, "��������");
	outtextxy (330, 350, "������������");
	outtextxy (330, 380, "��������");
	outtextxy (330, 410, "��������");
	outtextxy (330, 440, "���ո���ͣ");
	//���Ʒָ���
	line (305, 0, 305, 600);

}

int main () {
	//��������
	mciSendString ("open music.mp3 alias music", nullptr, 0, nullptr);
	mciSendString ("play music repeat", nullptr, 0, nullptr);
	//���ƻ���
	initgraph (500, 600);
	//���Ʊ�������
	drawBackground ();
	//������Ӻ���
	srand ((unsigned int)time (NULL));
	char str[30];
	int n = rand () % 7;
	while (1) {
		sprintf_s (str, "��ǰ�÷֣�%d", score);
		outtextxy (310, 200, str);
		downFlg = 0;
		//����һ������
		createBlock (4 * n);
		rotateIndex = 4 * n;
		//��һ��Ҫ���ɵķ���
		int nNext = rand () % 7;
		createNextBlock (4 * nNext);
		n = nNext;
		//�ж���Ϸ�Ƿ����
		if (isEnd () == 1) break;
		//ѭ������
		t = 300;
		while (true) {
			//����������ͼ
			drawMap ();
			move ();
			Sleep (t);
			if (downFlg) {
				break;
			}
		}

	}
	settextcolor (RED);
	setbkmode (TRANSPARENT);         //���ֱ���͸��
	settextstyle (30, 0, "��������");
	outtextxy (340, 163, "game over!");
	while (1);
	return 0;
}

