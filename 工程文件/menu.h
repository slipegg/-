#pragma once
#include<iostream>
#include<Windows.h>
#include<ctime>
#include<iomanip>
#include"Wall.h"
class Menu
{
private:
	string leveStr[6];//�ȼ����
	int choseNum;//ѡ��Ĳ˵���������
	int choseLeveNum;//ѡ�����Ϸ�ȼ�����
	int sumHis;//��ʷ��¼����
	void drawChose(int n);//��ѡ��>  <���
	struct Record//��߷�
	{
		string name;
		int score;
	}record[10];
	//��ʷ��¼����
	struct hisDate
	{
		int hlevel;
		string hname;
		int hscore;
		struct hisDate* next;
	}h[10];
	void deleteHis(int n);//ɾ����ʷ����
	hisDate* head;//ͷ��
public:
	bool isChoose;//�Ƿ�ѡ����
	bool isFinish;//�жϲ˵������Ƿ������
	void drawMenu();//���˵�����
	int chooseFunct();//ѡ��˵�����
	void showScore();//չʾ��߼�¼
	int getScore(int level);//�õ�����
	int chosePlayLeve();//ѡ����Ϸ�ȼ�
	void readHistory();//�Ķ���ʷ��¼
	void drawHistory();//������ʷ��¼
	void drawChoseHistory(int n);//����ѡ��>   
	void findName();//��������
	Menu(Wall& tempwall);
	Wall& wall;
};
Menu::Menu(Wall& tempwall) :wall(tempwall)
{

	CONSOLE_CURSOR_INFO cursor;           //���ṹ 
	cursor.dwSize = 10;

	HANDLE outsys = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������
	cursor.bVisible = 0;                  //0Ϊ���ع��
	SetConsoleCursorInfo(outsys, &cursor);//�������ع�꺯�� 

	//��ʼ��һЩ����
	choseNum = 1;
	isFinish = 0;
	isChoose = 0;
	choseLeveNum = 1;
	sumHis = 0;
	head = NULL;
	leveStr[1] = "���Ű�";
	leveStr[2] = "���װ�";
	leveStr[3] = "�߼���";
	leveStr[4] = "Ȥζ��";
	leveStr[5] = "���ϰ�";
}

void Menu::drawMenu()//���ƽ���
{
	system("mode con cols=150 lines=44");//�ı���
	wall.goMapXY(wall.COL / 2 , 10);
	cout << "̰����!";
	wall.goMapXY(wall.COL / 2, 12);
	cout << "��ʼ��Ϸ";
	wall.goMapXY(wall.COL / 2, 14);
	cout << "ѡ���Ѷ�";
	wall.goMapXY(wall.COL / 2, 16);
	cout << "��߷���";
	wall.goMapXY(wall.COL / 2, 18);
	cout << "��ʷ��¼";
	wall.goMapXY(wall.COL / 2, 20);
	cout << "�˳���Ϸ";
}

void Menu::drawChose(int n)//����ѡ��>  < ��ע�⵽�����µ�֮ǰ�Ǻ��ڸǵ�
{
	wall.goMapXY(wall.COL / 2 - 2, 10+2*n);
	putchar('>');
	wall.goMapXY(wall.COL / 2 + 9, 10+2*n);
	putchar('<');
	wall.goMapXY(wall.COL / 2 - 2, 8+2*n);
	putchar(' ');
	wall.goMapXY(wall.COL / 2 + 9, 8+2*n);
	putchar(' ');
	wall.goMapXY(wall.COL / 2 - 2, 12+2*n);
	putchar(' ');
	wall.goMapXY(wall.COL / 2 + 9, 12+2*n);
	putchar(' ');
}

int Menu::chooseFunct()//ѡ��˵�����
{
	drawChose(choseNum);//����ѡ��> <
	//�������¼�����

	int ch1 = 0;
	int ch2 = 0;
	while (!isChoose)//��û��ѡ��
	{
		ch1 = _getch();
		if (ch1 == '\r')//�س�����ʾѡ����
		{
			isChoose = 1;
			break;
		}if (ch1 == 224)//��ʾ���������¼�
		{
			ch2 = _getch();//��һ�ε���getch()������ֵ224

			switch (ch2)//�ڶ��ε���getch()
			{
			case 72://�ϼ���ѡ��-1
			{
				if (choseNum > 1)//ѡ������ֲ���Խ��
				{
					choseNum--;
				}
				break;
			}
			case 80://�¼���ѡ��+1
			{
				if (choseNum < 5)//ѡ������ֲ���Խ��
				{
					choseNum++;
				}
				break;
			}
			}
			drawChose(choseNum);//����ѡ��
		}
	}
	return choseNum;//����ѡ��
}

void Menu::showScore()//չʾ��߷���
{
	system("cls");
	//���ļ�
	fstream fscore("record.txt");
	if (!fscore.is_open())
	{
		cout << "�򿪼�¼�ļ���ʧ��";
		return;
	}
	for (int i = 1; i <= 5; i++)
		fscore >> record[i].name >> record[i].score;
	fscore.close();

	for (int i = 1; i <= 5; i++)//����ʷ��߷ִ�ӡ��ȥ
	{
		wall.goMapXY(wall.COL / 2, 3 + 2 * i);
		cout << leveStr[i] << setw(5) << record[i].name << "  " << record[i].score;
	}

	wall.goMapXY(wall.COL / 2, 30);
	cout << "�����������";
	_getch();
}


int Menu::getScore(int level)//�õ�����
{
	return record[level].score;
}

int Menu::chosePlayLeve()//ѡ����Ϸ�ȼ�
{
	//����ѡ��
	system("cls");
	wall.goMapXY(wall.COL / 2, 12);
	cout << leveStr[1];
	wall.goMapXY(wall.COL / 2, 14);
	cout << leveStr[2];
	wall.goMapXY(wall.COL / 2, 16);
	cout << leveStr[3];
	wall.goMapXY(wall.COL / 2, 18);
	cout << leveStr[4];
	wall.goMapXY(wall.COL / 2, 20);
	cout << leveStr[5];
	wall.goMapXY(wall.COL / 2, 22);
	cout << "���ز˵�";
	wall.goMapXY(wall.COL / 2 + 40, 12);
	cout << "��ǰѡ��ģʽ��" << leveStr[choseLeveNum];

	drawChose(choseLeveNum);//����ѡ���>   

	int choseNow = choseLeveNum;
	int ch1 = 0;
	int ch2 = 0;
	while (1)
	{
		ch1 = _getch();
		if (ch1 == '\r')//�س�����ʾѡ����
		{
			if (choseNow != 6)
			{
				choseLeveNum = choseNow;
				//��һ����ʾ��ѡ���ģʽ
				wall.goMapXY(wall.COL / 2 + 40, 12);
				cout << "��ǰѡ��ģʽ��" << leveStr[choseLeveNum];
				continue;
			}
			else//ѡ���˷��ز˵�
			{
				drawMenu();
				break;
			}
		}
		if (ch1 == 224)//���¼�
		{
			ch2 = _getch();//��һ�ε���getch()������ֵ224
			switch (ch2)//�ڶ��ε���getch()
			{
			case 72://�ϼ������ܳ�������
			{
				if (choseNow > 1 && choseNow <= 6)
				{
					choseNow--;
				}
				break;
			}
			case 80://�¼����ܳ�������
			{
				if (choseNow < 6 && choseNow >= 1)
				{
					choseNow++;
				}
				break;
			}
			}
			drawChose(choseNow);
		}
	}
	return choseLeveNum;
}

void Menu::drawChoseHistory(int n)//����ѡ���>
{

	wall.goMapXY(wall.COL / 2 - 2, 5 + 2 * n);
	cout << '>';
	wall.goMapXY(wall.COL / 2 - 2, 5 + 2 * (n - 1));
	cout << ' ';
	wall.goMapXY(wall.COL / 2 - 2, 5 + 2 * (n + 1));
	cout << ' ';
}

void Menu::deleteHis(int n)//ɾ����һ����ʷ��¼
{
	hisDate* p = head->next, * pre = head;
	int i = 1;
	while (i != sumHis + 1 - n)//���ҵ���һ����ע��õ���n�ǵ��򣬵������������
	{
		pre = p;
		p = p->next;
		i++;
	}
	pre->next = p->next;
	delete p;
	sumHis--;
}

void Menu::drawHistory()//������ʷ��¼
{
	system("cls");
	hisDate* p = head->next, * q = NULL;
	//������Ϣ
	wall.goMapXY(wall.COL, 20);
	cout << "��ɾ������ɾ����ѡ��";
	wall.goMapXY(wall.COL / 2, 3);
	cout << "����";
	wall.goMapXY(wall.COL / 2, 5);
	cout << "��ѯ";
	int n = 1;
	while (p != NULL)
	{
		if (sumHis + 1 - n < 19)
		{
			wall.goMapXY(wall.COL / 2, 5 + 2 * (sumHis + 1 - n));
			cout << sumHis + 1 - n << "   �汾��" << leveStr[p->hlevel] << "   �û�����" << p->hname << "   �÷֣�" << p->hscore;
		}
		p = p->next;
		n++;
	}
}

void Menu::findName()//��ѡ���˲�ѯ
{
	system("cls");

	wall.goMapXY(wall.COL / 2, 5);
	cout << "������Ҫ��ѯ��������֣�";
	wall.goMapXY(wall.COL / 2, 7);
	string fin;
	cin >> fin;
	hisDate* p = head->next;
	//���Բ���������֣�ֻ��һ����
	while (p != NULL && p->hname != fin)
	{
		p = p->next;
	}
	wall.goMapXY(wall.COL / 2, 9);
	if (p != NULL)//����ҵ���
	{
		cout << "�汾��" << leveStr[p->hlevel] << "   �û�����" << p->hname << "   �÷֣�" << p->hscore;//�����Ϣ
		wall.goMapXY(wall.COL / 2, 11);
		cout << "�Ƿ��޸�������������ո�ȷ����������������";//ѯ���Ƿ�Ҫ����
		if (_getch() == ' ')//�ո�ȷ�ϸ���
		{
			//�����滻�µ�����
			wall.goMapXY(wall.COL / 2, 13);
			cout << "�������µ����֣�";
			string newname;
			cin >> newname;
			p->hname = newname;
			wall.goMapXY(wall.COL / 2, 15);
			//����
			cout << "����ɣ������������";
			_getch();
		}
	}
	else//û�ҵ�
	{
		cout << "δ�ҵ�" << "  �����������";
	}
}

void Menu::readHistory()//�Ķ���ѡ����ʷ��¼
{
	system("cls");

	//���ļ�
	fstream fhistory("history.txt");
	if (!fhistory.is_open())
	{
		cout << "�򿪼�¼�ļ���ʧ��";
		return;
	}

	head = new hisDate;
	hisDate* p = head, * q = NULL;
	sumHis = 0;

	while (fhistory.peek() != EOF)//����ʷ��Ϣ���뵽������ȥ
	{
		q = new hisDate;
		p->next = q;
		p = q;
		fhistory >> p->hlevel >> p->hname >> p->hscore;
		sumHis++;
	}
	p->next = NULL;
	drawHistory();

	//ɾ������
	int ch1 = 0;
	int ch2 = 0;
	bool isChooseHis = 0;
	int choseNumHis = -1;
	while (!isChooseHis)
	{
		drawChoseHistory(choseNumHis);
		ch1 = _getch();
		if (ch1 == '\r' && choseNumHis < 1)//�س�ѡ��
		{
			if (choseNumHis == -1)//����
			{
				drawMenu();
				break;
			}

			if (choseNumHis == 0)//������ʷ��¼
			{
				findName();
				drawHistory();//����֮�󷵻�
				continue;
			}
		}
		if (ch1 == 8)//��delete����ɾ��
		{
			wall.goMapXY(wall.COL / 2 + 60, 25);
			cout << "�Ƿ�ȷ��ɾ����";
			wall.goMapXY(wall.COL / 2 + 60, 27);
			cout << "���س���ȷ�ϣ�����������ȡ��";
			char a = _getch();
			if (a == '\r')
			{
				deleteHis(choseNumHis);//ɾ��
				drawHistory();//���»�����ʷ��¼
			}
			continue;
		}
		if (ch1 == 224)//�����¼�
		{
			ch2 = _getch();//��һ�ε���getch()������ֵ224
			switch (ch2)//�ڶ��ε���getch()
			{
			case 72://�¼�
			{
				if (choseNumHis > -1)
				{
					choseNumHis--;
				}
				break;
			}
			case 80://�ϼ�
			{
				if (choseNumHis < 18 && choseNumHis < sumHis)
				{
					choseNumHis++;
				}
				break;
			}
			default:break;
			}
		}
	}

	//�ر������´򿪣�Ϊ���ڴ򿪵�ʱ���ԭ�����ļ�������գ���������
	fhistory.close();

	ofstream whistory("history.txt");
	if (!whistory.is_open())
	{
		cout << "д���¼�ļ�ʧ��";
		return;
	}

	p = head->next;
	while (p != NULL)//д��ԭ���ļ�¼�������и���
	{
		whistory << " " << p->hlevel << " " << p->hname << " " << p->hscore;
		p = p->next;
	}
	whistory.close();
}