#pragma once
#include"Wall.h"
class Food
{
private:
	//����ʳ���λ��
	int foodPlaceX[50];
	int foodPlaceY[50];

	int allNum;//ʳ������
	int isEat[150][150];//��¼��λ�õ�ʳ���Ƿ񱻳Ե���
public:
	Food(Wall& tempwall);
	bool randomFood();//�������ʳ��
	void addFood(int x, int y);//��x,yλ������ʳ��
	void clearFood(int level);//��������е�ʳ��
	void eatFood(int x,int y);//��¼x,yλ�õ�ʳ�ﱻ�Ե���
	void drawFood();//չʾʳ��
	COORD getAfood();//���һ�����ʳ���λ����Ϣ
	bool checkIsEat(COORD p);//���x,yλ�õ�ʳ���Ƿ񱻳���
	int num;//��¼��ǰʳ������
	Wall& wall;
};

COORD Food::getAfood()//���һ�����ʳ���λ����Ϣ
{
	while(1)
	{
		int i = rand() % allNum;//������ʳ�����������һ��
		if (wall.getCharInMap(foodPlaceX[i], foodPlaceY[i]) == '$'&&!isEat[foodPlaceX[i]][ foodPlaceY[i]])//�ж�ʳ���Ƿ��ڣ����ھͷ�����Ϣ
		{
			COORD a;
			a.X = foodPlaceX[i];
			a.Y = foodPlaceY[i];
			return a;
		}
	}
}

bool Food::checkIsEat(COORD p)//���x,yλ�õ�ʳ���Ƿ񱻳���
{
	if (isEat[p.X][p.Y])
		return 1;
	else
		return 0;
}

Food::Food(Wall& tempwall) :wall(tempwall)//��ʼ��
{
	memset(foodPlaceX, 0, sizeof(foodPlaceX));
	memset(foodPlaceY, 0, sizeof(foodPlaceY));
	memset(isEat, 1, sizeof(isEat));
}

bool Food::randomFood()
{
	bool isBornFood = 0, isBreak = 0;//�Ƿ�ɹ�������ʳ��Ƿ���Ҫ����ѭ��
	num = 0;//ʳ������Ϊ0
	
	//��Ҫ�ж��Ƿ��пռ����ʳ��Լ������Բ�����С��5��ʳ�������
	for (int x = 1; x <= wall.COL; x++)
	{
		for (int y = 1; y <= wall.ROW; y++)
		{
			if (wall.getCharInMap(x, y) == ' ')//�����һ���ǿյģ���˵�����ٿ��Բ���һ��ʳ��
			{
				isBornFood = 1;
				num++;
			}
			if (num >= 5)//������Դ���5�ˣ���˵�����ü����ж��ˣ�ֱ������ѭ��
			{
				isBreak = 1;
				break;
			}
		}
		if (isBreak)
			break;
	}

	if (!isBornFood)//���û�гɹ�����ʳ���˵��ʧ���ˣ��ͷ���0
		return 0;

	srand((unsigned int)time(NULL));//ˢ���������
	int placeN = 0;
	int n = rand() % num + 1;//�����ʳ������
	num = n;
	for (int i = 0; i < n; i++)//�����n��ʳ�����Ϣ
	{
		while (1)
		{
			int x = rand() % wall.COL + 1;//�����ʳ���λ��x
			int y = rand() % wall.ROW + 1;//�����ʳ���λ��y
			if (wall.getCharInMap(x, y) == ' ')//�������������λ��ԭ����û�ж����Ļ����Ͱ�ʳ��������λ�ã�������ͼ��
			{
				wall.putCharInMap(x, y, '$');//������š�ͼƬ
				isEat[x][y] = 0;
				foodPlaceX[placeN] = x;//��¼��ȥ
				foodPlaceY[placeN] = y;//��¼��ȥ
				placeN++;//��¼���м�����Чʳ����Ϣ
				break;
			}
		}
	}
	allNum = num;//��¼��ԭ��ʳ��������
	return 1;
}

void Food::addFood(int x, int y)//��x��y����ʳ��
{
	//��¼x,y����ʳ����Ϣ
	foodPlaceX[allNum] = x;
	foodPlaceY[allNum] = y;
	wall.putCharInMap(x, y, '$');
	isEat[x][y] = 0;
	num++;//����ʳ�������+1
	allNum++;//��ʳ�������+1
}

void Food::clearFood(int level)//�����ʳ���ͼ��
{

	for (int i = 0; i < allNum; i++)//��map�м�¼���⼸���ʳ�ﶼû���ˣ�����' '
	{
		if (!isEat[foodPlaceX[i]][foodPlaceY[i]])//����Ǹ�û�б��Ե������滻
		{
			wall.putCharInMap(foodPlaceX[i], foodPlaceY[i], ' ');
			isEat[foodPlaceX[i]][foodPlaceY[i]] = 1;
		}
	}
	//��¼������0
	allNum = 0;
	num = 0;
}

void Food::eatFood(int x,int y)//��¼�Ե���x,y����ʳ��
{
	num--;
	isEat[x][y] = 1;
}

void Food::drawFood()//չʾʳ��
{
	IMAGE zhizhu(10, 10);
	loadimage(&zhizhu, _T("zhizhu.jpg"), 10, 10);
	for (int i = 0; i < allNum; i++)
	{
		if (!isEat[foodPlaceX[i]][foodPlaceY[i]])//���û�б��Ե���չʾ
		{
			putimage(10 * foodPlaceX[i], 10 * foodPlaceY[i], &zhizhu);
		}
	}
}