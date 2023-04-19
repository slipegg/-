#pragma once
#include"Wall.h"
#include"Food.h"
#include<fstream>
#include<iostream>
using namespace std;
class Snake
{
private:
	int len;//�ߵĳ���

	//��¼�����ݵĽڵ�
	struct snakeDate
	{
		int x;
		int y;
		snakeDate* next;
	};

	snakeDate* shead;//��ͷ
	int life;//�ߵ�����
	void move(int dx, int dy);//�ƶ�����
	int score;//�÷�
	char predir;//��һ���ƶ��ķ���
	bool isDead;//�ж����Ƿ��Լ�������
	int sleepChange;//ͣ��ʱ���޸�
public:
	Snake(Wall& tempWall, Food& food);
	Wall& wall;
	Food& food;
	int gameLeve;//��Ϸ�ȼ�
	bool isPutV;//�Ƿ���ý�����Ʒ
	bool isPutBoom;//�Ƿ����ը��
	enum//���÷����
	{
		UP = 'w',
		DOWN = 's',
		LEFT = 'a',
		RIGHT = 'd'
	};

	void initSnake();//���³�ʼ���ߵ�һЩ����
	bool randBron();//�������������
	bool getIsDead();//�õ����Ƿ�����
	int getScore();//�õ�����
	int getSnakeLen();//�õ��ߵĳ���
	int getLife();//�õ��ߵ�����ֵ
	int getHeadX();//�õ���ͷ��λ��x
	int getHeadY();//�õ���ͷ��λ��y
	void moveSnake(char dir);//���ݷ�λ�ƶ���
	void sleep();//����ֹͣʱ��
	void deatorySnake();//ɾ�������������
	void trySaveDate();//���Ա�����Ϸ��¼
	void snakeToWall();//������ת��Ϊǽ
	void snakeToFood();//�������Ϊʳ��
	void snakeToNull();//������ת��Ϊ��
	void dieNote();//������Ϸ��������ʾ
	void downLife(int n);//��������
	void drawSnake();//����
};

//��ʼ���ߵ�һЩ��Ϣ
Snake::Snake(Wall& tempWall, Food& tempFood) : wall(tempWall), food(tempFood)
{
	shead = new snakeDate;//������ͷ�Ŀռ�

	//��ʼһЩ��Ϣ
	isDead = false;//û����
	len = 4;//����4
	score = 0;//����0
	life = 5;//����ֵ��5
	predir = UP;//һ��ʼ֮ǰ�ķ�������
	gameLeve = 1;//��ʼĬ��ѡ���һ����Ϸ
	isPutV = 0;//���Ž���
	isPutBoom = 0;//����ը��
	sleepChange = 0;
}

void Snake::initSnake()
{
	isDead = false;//��Ϊû��
	predir = UP;//һ��ʼ��������
}

int Snake::getSnakeLen()//�õ��߳�
{
	return len;
}

//�ƶ�
void Snake::move(int dx, int dy)
{
	bool isputhead = 1;//�Ƿ�Ҫ������ͷ

	snakeDate* p = shead, * pre = NULL;
	p = new snakeDate;//pΪ�����ƶ�������ͷ����Ϣ
	p->x = shead->x + dx;
	p->y = shead->y + dy;
	p->next = shead;

	shead = p;//shead����Ϊ��ͷ��Ϣ
	while (p->next != NULL)//pתΪ�������һ���������Ϣ
	{
		pre = p;
		p = p->next;
	}

	if (gameLeve == 4)
	{
		if (shead->x > 50 && shead->y < 30)
			sleepChange--;
		else
		{
			if (shead->x < 30 && shead->y > 30)
				sleepChange++;
			else
			{
				sleepChange = 0;
			}
		}
	}

	if (wall.getCharInMap(shead->x, shead->y) == ' '||(shead->x==p->x&&shead->y==p->y))//���ǰ���ǿհ�
	{
		wall.putCharInMap(p->x, p->y, ' ');//���һλ��Ϊ�հ�
		delete p;//ɾ�������һ���ڵ�
		pre->next = NULL;//��һ����Ϊ���һ��
	}
	
	if (wall.getCharInMap(shead->x, shead->y) == '$')//����Ե���ʳ��
	{
		food.eatFood(shead->x, shead->y);//��¼����ʳ�ﱻ����
		len++;//����+1
		score+=10;//�ɼ�+10
	}

	if (wall.getCharInMap(shead->x, shead->y) == '&')//����Ե��˽���
	{
		isPutV = 0;//���ٷŽ���
		len++;//����+1
		life += 3;//����+3
		score += 50;//�ɼ�+50
	}

	if (wall.getCharInMap(shead->x, shead->y) == '!')//����Ե���ը��
	{
		isPutBoom = 0;//���ٷ�ը��
		isDead = 1;//����
		life -= 3;//����-3
		score =0;//��������
	}

	//ײ��ǽ
	if (gameLeve == 4)//�����Ϸ�汾Ϊ���İ�
	{
		if (wall.getCharInMap(shead->x, shead->y) == '#')//����ײǽ��
		{
			isDead = TRUE;//�������
			if (shead->y > 59)//���ײ�������ǽ������-2
			{
				life-=2;
				return;
			}

			if (shead->y < 1)//���ײ�������ǽ
			{
				int d = 3;//�߳�����3
				len = len  - d;
				if (len >=1)//���������Ȼ��
				{
					isDead = FALSE;//��Ϊû��
					score -= 5;//����-5
					p = shead->next;//��Ϊͷ�Ѿ���ǽ���ˣ��ʹ���һ����ʼ
					while (p != NULL)
					{
						if (d > 0)//��d>0
						{
							wall.putCharInMap(p->x, p->y, ' ');//��¼�����Ϊ��
							shead = p->next;//�����ֻ���ͷ
						}
						else
						{
							wall.putCharInMap(p->x, p->y, '*');//չʾ����
						}
						d--;
						p = p->next;
					}
				}
				else//���û������
				{
					life--;//����-1
					len = 4;//���ȹ�4��Ϊ�˺���ʾ����
				}
				return;
			}
			
			life--;//�������������λ��ײǽ��������-1
		}
	}
	else//������ǵ��İ�
	{
		if (wall.getCharInMap(shead->x, shead->y) == '#')//ײǽ
		{
			isDead = TRUE;//����
			life--;//����-1
			return;
		}
	}

	if (wall.getCharInMap(shead->x, shead->y) == '*')//����Ե����Լ�����Ϊ�Ѿ���ǰ���������һλ׷β�����⣬���õ�������
	{
		isDead = TRUE;//����
		life--;//����-1
		return;
	}

	//��ʣ���������Ƴ���
	p = shead;
	while (p != NULL)
	{
		wall.putCharInMap(p->x, p->y, '*');
		p = p->next;
	}
}

void Snake::moveSnake(char dir)//�ƶ���
{
	//ȷ�������Ƿ���
	if ((predir == UP && dir == DOWN) || (predir == DOWN && dir == UP) || (predir == LEFT && dir == RIGHT) || (predir == RIGHT && dir == LEFT))
	{
		dir = predir;
	}

	//��ͬ�ķ���ͬ���ƶ�
	switch (dir)
	{
	case UP:
	{
		move(0, -1);
		break;
	}
	case DOWN:
	{
		move(0, 1);
		break;
	}
	case RIGHT:
	{
		move(1, 0);
		break;
	}
	case LEFT:
	{
		move(-1, 0);
		break;
	}
	}
	predir = dir;//����֮ǰ���ƶ�����
}

void Snake::sleep()//��Ϣʱ��
{
	//��ͬ�ȼ���Ӧ��ͬ
	switch (gameLeve)
	{
	case 1:
	{
		Sleep(60);
		break;
	}
	case 2:
	{
		Sleep(50);
		break;
	}
	case 3:
	{
		Sleep(40);
		break;
	}
	case 4://ģʽ4��Ϊ�м��ٺͼ���������Ϣʱ��Ҫ�仯
	{
		int s = 100 + sleepChange;
		if (s < 3)
			s = 2;
		Sleep(s);
		break;
	}
	case 5:
	{
		Sleep(10);
		break;
	}
	}
}

void Snake::trySaveDate()//���Դ�����Ϣ
{
	//���ļ�
	fstream fscore("record.txt");
	fstream fhis("history.txt");

	if (!fscore.is_open())
	{
		cout << "�򿪼�¼�ļ���ʧ��";
		return;
	}
	if (!fhis.is_open())
	{
		cout << "����ʷ��¼�ļ�ʧ��";
		return;
	}

	string name[6] = { " ","---","---","---" ,"---","---" };//��ʼ���飬��ֹû�м�¼��ʱ���������
	int userScore[6] = { 0 };

	for (int i = 1; i <= 5; i++)//��ȡ��¼
	{
		fscore >> name[i] >> userScore[i];
	}

	if (userScore[gameLeve] < score)//��������˼�¼
	{
		wall.goMapXY(50, 25);
		cout << "���Ѿ����Ƽ�¼�ˣ�������������Ĵ���";//��ʾ
		wall.goMapXY(50, 27);
		cin >> name[gameLeve];//��������
		userScore[gameLeve] = score;
		fscore.clear();
		fscore.seekp(0, ios::beg);//�ص���¼�ļ���ͷ����������
		for (int i = 1; i <= 5; i++)
		{
			fscore << name[i] << " " << userScore[i] << " ";
		}
		fhis.seekp(0, ios::end);//ȥ����ʷ��¼��β����¼����
		fhis << " " << gameLeve << " " << name[gameLeve] << " " << score;
	}
	else//���û�д�������,ֻ��¼����ʷ�ĵ�
	{
		wall.goMapXY(50, 25);
		cout << "�������������";
		wall.goMapXY(50, 27);
		cin >> name[gameLeve];
		fhis.seekp(0, ios::end);
		fhis << " " << gameLeve << " " << name[gameLeve] << " " << score;
	}
	//�ر��ļ�
	fscore.close();
	fhis.close();

}

void Snake::snakeToWall()//�������Ϊǽ
{
	snakeDate* p = shead->next;
	int x, y;
	while (p != NULL)//����
	{
		x = p->x;
		y = p->y;
		wall.putCharInMap(x, y, '#');
		wall.addWall(x, y);
		p = p->next;
	}
}

void Snake::snakeToFood()//�����Ϊʳ��
{

	snakeDate* p = shead->next;
	int x, y;

	while (p != NULL)//����
	{
		x = p->x;
		y = p->y;
		food.addFood(x, y);
		p = p->next;
	}
}

int Snake::getLife()//�õ�����
{
	return life;
}


bool Snake::randBron()//���������
{
	bool isBorn = 0;//�ж��Ƿ����㹻�ռ���Բ�����
	int bornPlaceX[500] = { 0 }, placeN = 0;//��¼���Ե�����ͷ��x

	//��Ϊ�ǲ������·�����ߣ���������Ҫ��3���ո�
	for (int i = 1; i <= wall.COL; i++)
	{
		for (int j = 1; j <= wall.ROW - 3; j++)
		{
			if (wall.getCharInMap(i, j) == ' ' && wall.getCharInMap(i, j + 1) == ' ' && wall.getCharInMap(i, j + 2) == ' ' && wall.getCharInMap(i, j + 3) == ' ')
			{
				isBorn = 1;
				bornPlaceX[placeN++] = i;
				break;
			}
		}
	}

	if (isBorn)
	{
		isDead = false;//��Ϊû��
		predir = UP;//һ��ʼ��������

		//�ڿ��Ե�����ͷ��x�������λ��
		srand((unsigned int)time(NULL));
		int x = bornPlaceX[rand() % placeN];
		int y = rand() % (wall.ROW - 3) + 1;//�߳�Ϊ4
		while (1)
		{
			//�����ж���һ�������Ƿ����˳����������
			if (wall.getCharInMap(x, y) == ' ' && wall.getCharInMap(x, y + 1) == ' ' && wall.getCharInMap(x, y + 2) == ' ' && wall.getCharInMap(x, y + 3) == ' ')
				break;
			y = rand() % (wall.ROW - 3) + 1;//�߳�Ϊ4
		}

		len = 4;//����

		//�ڵ�ͼ�б���ߵ�λ��
		shead = new snakeDate;
		shead->x = x;
		shead->y = y;
		shead->next = NULL;
		wall.putCharInMap(shead->x, shead->y, '*');
		snakeDate* now = NULL;
		snakeDate* pre = shead;
		for (int i = 1; i < 4; i++)
		{
			wall.putCharInMap(x, y + i, '*');
			now = new snakeDate;
			now->x = x;
			now->y = y + i;
			pre->next = now;
			pre = now;
		}
		now->next = NULL;
		return 1;
	}
	else
		return 0;//û�пռ��������
}

void Snake::deatorySnake()//���ٵ��ߵ�����ռ�
{
	snakeDate* p = shead, * k = NULL;
	while (p != NULL)
	{
		k = p;
		p = p->next;
		delete k;
	}
}

void Snake::dieNote()//��Ϸ������ʾ
{
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(50, 0, _T("����"));
	outtextxy(450, 200, _T("��Ϸ����"));
	outtextxy(450, 300, _T("�����������"));
}

void Snake::snakeToNull()//���������ĵط��ı�Ǳ��
{
	snakeDate* p = shead->next;
	int x, y;

	while (p != NULL)
	{
		x = p->x;
		y = p->y;
		wall.putCharInMap(x, y, ' ');
		p = p->next;
	}
}

int Snake::getHeadX()//�õ�ͷλ��X
{
	return shead->x;
}

int Snake::getHeadY()//�õ�ͷλ��Y
{
	return shead->y;
}

void Snake::downLife(int n)//����ʲôn
{
	life -= n;
}

int Snake::getScore()//�õ�����
{
	return score;
}

bool Snake::getIsDead()//�õ��Ƿ�������Ϣ
{
	return isDead;
}

void Snake::drawSnake()//���ߵ�ͼ��
{
	snakeDate* p = shead;
	while (p != NULL)
	{
		IMAGE wowo(10, 10);
		loadimage(&wowo, _T("wowo.jpg"), 10, 10);
		putimage(10 * p->x, 10 *p-> y, &wowo);
		p = p->next;
	}
}