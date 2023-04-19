#include"wall.h"
#include"food.h"
#include"snake.h"
#include"menu.h"
#include<fstream>
using namespace std;
IMAGE img(1120, 620);
void loadPhoto(int n)//����img��Ӧ��ͼƬ
{
	switch (n)
	{
	case 1: 
	{
		loadimage(&img, _T("1.jpg"), 1120, 620);
		break;
	}
	case 2:
	{
		loadimage(&img, _T("2.jpg"), 1120, 620);
		break;
	}
	case 3:
	{
		loadimage(&img, _T("3.jpg"), 1120, 620);
		break;
	}
	case 4:
	{
		loadimage(&img, _T("4.jpg"), 1120, 620);
		break;
	}
	case 5:
	{
		loadimage(&img, _T("5.jpg"), 1120, 620);
		break;
	}
	}
	// ���û�ͼĿ��Ϊ img ����
	SetWorkingImage(&img);
	if (n == 4)//4ģʽ�Ļ�����Ҫ��Ӧ���ϵ㣬��Ӧ���١�������
	{
		//������
		for (int i = 51; i <= 80; i++)
		{
			for (int j = 1; j < 30; j++)
			{
				putpixel(i * 10 + 5, j * 10 + 5, BLUE);
				putpixel(i * 10, j * 10, BLUE);
			}
		}
		//������
		for (int i = 1; i < 30; i++)
		{
			for (int j = 31; j <= 60; j++)
			{
				putpixel(i * 10 + 5, j * 10 + 5, RED);
				putpixel(i * 10, j * 10, RED);
			}
		}
	}
}

void showPhoto()//��ͼƬ����������Ƶ��ߡ�ǽ��ʳ��չ�ֳ���
{
	// ���û�ͼĿ��Ϊ��ͼ����
	SetWorkingImage();
	// �� img ������ʾ�ڻ�ͼ������
	putimage(0, 0, &img);
	SetWorkingImage(&img);
}

void addVB(bool isPutV = 0,bool isPutBoom=0)//���ý�����ը����ͼƬ
{
	if (isPutV)
	{
		IMAGE V(20, 20);
		loadimage(&V, _T("V.png"), 20, 20);
		putimage(10 * 1, 10 * 1, &V);
	}
	if (isPutBoom)
	{
		IMAGE B(20, 20);
		loadimage(&B, _T("B.png"), 20,20);
		putimage(10 * 10, 10 * 10, &B);
	}
}

void rePhoto(int n)//��ͼƬ����ԭ����ͼƬ���Դﵽˢ�µ�Ч��
{
	switch (n)
	{
	case 1:
	{
		loadimage(&img, _T("1.jpg"), 1120, 620);
		break;
	}
	case 2:
	{
		loadimage(&img, _T("2.jpg"), 1120, 620);

		break;
	}
	case 3:
	{
		loadimage(&img, _T("3.jpg"), 1120, 620);
		break;
	}
	case 4:
	{
		loadimage(&img, _T("4.jpg"), 1120, 620);
		break;
	}
	case 5:
	{
		loadimage(&img, _T("5.jpg"), 1120, 620);
		break;
	}
	}
	if (n == 4)
	{
		for (int i = 51; i <= 80; i++)
		{
			for (int j = 1; j < 30; j++)
			{
				putpixel(i * 10 + 5, j * 10 + 5, BLUE);
				putpixel(i * 10, j * 10, BLUE);
			}
		}
		for (int i = 1; i < 30; i++)
		{
			for (int j = 31; j <= 60; j++)
			{
				putpixel(i * 10 + 5, j * 10 + 5, RED);
				putpixel(i * 10, j * 10, RED);
			}
		}
	}
	putimage(0, 0, &img);
}

void putVB(Snake &s,Wall &w)//���ý�����ը������Ϣ��Map��
{
	if (s.getLife() == 2)
	{
		w.putCharInMap(1, 1, '&');
		w.putCharInMap(1, 2, '&');
		w.putCharInMap(2, 1, '&');
		w.putCharInMap(2, 2, '&');
		s.isPutV = 1;
	}
	if (s.getLife() != 2)
	{
		if (w.getCharInMap(1, 1) == '&')
			w.putCharInMap(1, 1, ' ');
		if (w.getCharInMap(1, 2) == '&')
			w.putCharInMap(1, 2, ' ');
		if (w.getCharInMap(2, 1) == '&')
			w.putCharInMap(2, 1, ' ');
		if (w.getCharInMap(2, 2) == '&')
			w.putCharInMap(2, 2, ' ');

		s.isPutV = 0;
	}
	if (s.getLife() == 4)
	{
		w.putCharInMap(10, 10, '!');
		w.putCharInMap(10, 11, '!');
		w.putCharInMap(11, 10, '!');
		w.putCharInMap(11, 11, '!');
		s.isPutBoom = 1;
		//addVB(snake.isPutV,snake.isPutBoom);
	}
	if (s.getLife() != 4 )
	{
		if (w.getCharInMap(10, 10) == '!')
			w.putCharInMap(10, 10, ' ');
		if (w.getCharInMap(10, 11) == '!')
			w.putCharInMap(10, 11, ' ');
		if (w.getCharInMap(11, 10) == '!')
			w.putCharInMap(11, 10, ' ');
		if (w.getCharInMap(11, 11) == '!')
			w.putCharInMap(11, 11, ' ');

		s.isPutBoom = 0;
	}
}

void showAll(Snake& s,  Wall& w, Food& f, Menu& m)//������ͼƬ�л���
{
	rePhoto(s.gameLeve);//ˢ��
	s.drawSnake();//����
	w.drawWall();//ǽ
	w.drawTipUI(s.getSnakeLen(), s.getScore(), m.getScore(s.gameLeve), s.gameLeve, s.getLife());//��ʾ
	f.drawFood();//ʳ��
	addVB(s.isPutV, s.isPutBoom);//������ը��
	showPhoto();//չʾ
}

void showThreeAll(Snake& s, Snake& t,Snake &r, Wall& w, Food& f, Menu& m)
{
	//���ϲ�࣬���Ƕ�չʾ��2��AI��
	rePhoto(s.gameLeve);
	w.drawWall();
	w.drawTipUI(s.getSnakeLen(), s.getScore(), m.getScore(s.gameLeve), s.gameLeve, s.getLife());

	f.drawFood();

	s.drawSnake();
	addVB(s.isPutV, s.isPutBoom);

	t.drawSnake();
	addVB(t.isPutV, t.isPutBoom);

	r.drawSnake();
	addVB(r.isPutV, r.isPutBoom);
	showPhoto();
}

void easyPlay()
{
	system("cls");//����
	loadPhoto(1);//���ر�������

	//ǽ�ĳ�ʼ��
	Wall wall;
	wall.initMap();
	wall.drawWall();

	//ʳ���ʼ��
	Food food(wall);
	food.randomFood();

	//�ߵĳ�ʼ��
	Snake snake(wall, food);
	snake.gameLeve = 1;
	snake.randBron();

	//�˵��ĳ�ʼ������ҪΪ�˻����ʷ��߷�
	Menu menu(wall);
	
	char dir = NULL, d = NULL;
	while (!snake.getIsDead())//���û������
	{
		showAll(snake, wall, food, menu);//��������Ҫչʾ��ͼƬ�����ϵĶ���һ������չʾ����
		dir = _getch();//�ȴ������
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)//�Ƿ������¼��
		{
			d = dir;
		}
		do//���û�������뷽�������û������һֱѭ��
		{
			snake.moveSnake(d);//�ߵ��ƶ�
			snake.sleep();//ͣ��һ��ʱ��
			if (food.num == 0)//���ʳ��Ϊ0�ˣ��ͳ�ʼ��һЩ
				food.randomFood();
			showAll(snake, wall, food, menu);//չʾ�ƶ���Ľ���
		} while (!_kbhit() && !snake.getIsDead());
	}

	if (snake.getIsDead())//���������
	{
		snake.dieNote();//��Ϸ������ʾ
		showPhoto();//����Ϸ������ʾ��ʾ����
		_getch();
		closegraph();//�ر���Ϸ����
		snake.deatorySnake();//�ͷſռ�
		snake.trySaveDate();//��¼����
		
	}
}

void hardPlay()
{
	//��easyPlay��ͬ���ֲ���׸����
	system("cls");
	loadPhoto(2);

	Wall wall;
	wall.initMap();
	wall.drawWall();

	Food food(wall);
	food.randomFood();

	Snake snake(wall, food);
	snake.gameLeve = 2;
	snake.randBron();

	Menu menu(wall);
	char dir = NULL, d = NULL;
	bool isGameOver = 0;//�����Ƿ��в���ʳ����ߵĿռ���������Ϸ�Ƿ���Լ�������
	while (!isGameOver)
	{
		showAll(snake, wall, food, menu);
		dir = _getch();
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)
		{
			d = dir;
		}
		do
		{
			snake.moveSnake(d);
			snake.sleep();
			if (food.num == 0)
			{
				if (!snake.randBron())
					isGameOver = 1;
			}
			showAll(snake, wall, food, menu);
			showPhoto();
		} while (!_kbhit() && !snake.getIsDead());

		if (snake.getIsDead())//�������
		{
			snake.snakeToWall();//�������Ϊǽ
			//ˢ��ʳ��
			food.clearFood(snake.gameLeve);
			if (!food.randomFood())//���µ���ʳ����ʧ�ܣ���Ϸ����
				isGameOver = 1;

			snake.deatorySnake();//�ͷſռ�
			snake.initSnake();//��ʼ��һЩ����
			if (!snake.randBron())//���µ����ߣ����ʧ����Ϸ����
				isGameOver = 1;
		}
	}
	snake.dieNote();
	showPhoto();
	_getch();
	closegraph();
	snake.trySaveDate();
}

void hhhardPlay()
{
	//��easyPlay��ͬ���ֲ���׸����
	system("cls");
	loadPhoto(3);

	Wall wall;
	wall.initMap();
	wall.drawWall();

	Food food(wall);
	food.randomFood();

	Snake snake(wall, food);
	snake.gameLeve = 3;
	snake.randBron();

	Menu menu(wall);
	wall.drawTipUI(snake.getSnakeLen(), snake.getScore(), menu.getScore(snake.gameLeve), snake.gameLeve, snake.getLife());
	char dir = NULL, d = NULL;
	bool isGameOver = 0;
	while (!isGameOver && snake.getLife())//�ж���Ϸ���������ݣ��Ƿ��߻�������ֵ���Ƿ��п��Բ����ߺ�ʳ��Ŀռ�
	{
		showAll(snake, wall, food, menu);
		dir = _getch();
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)
		{
			d = dir;
		}
		do
		{
			snake.moveSnake(d);
			snake.sleep();
			if (food.num == 0)
			{
				if (!snake.randBron())
					isGameOver = 1;
			}
			showAll(snake, wall, food, menu);
		} while (!_kbhit() && !snake.getIsDead());

		if (snake.getIsDead())
		{
			//��������ˢ��ʳ��
			food.clearFood(snake.gameLeve);
			if (!food.randomFood())
				isGameOver = 1;
			//������
			snake.snakeToFood();//����ת��Ϊʳ��
			snake.deatorySnake();//�ͷſռ�
			snake.initSnake();
			if (!snake.randBron())
				isGameOver = 1;
		}
	}
	snake.dieNote();
	showPhoto();
	_getch();
	closegraph();
	snake.trySaveDate();
}

void funPlay(int n)
{
	//��easyPlay��ͬ���ֲ���׸����
	system("cls");
	loadPhoto(4);

	Wall wall;
	wall.initMap();

	Food food(wall);
	food.randomFood();

	Snake snake(wall, food);
	snake.gameLeve = n;
	snake.randBron();

	Menu menu(wall);

	char dir = NULL, d = NULL;
	int sleepChange = 0;//ͣ��ʱ��ı䣬��Ӧ���٣�������
	bool isGameOver = 0;
	while (!isGameOver&&snake.getLife()>0)
	{
		showAll(snake, wall, food, menu);
		dir = _getch();
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)
		{
			d = dir;
		}
		do
		{
			snake.moveSnake(d);
			snake.sleep();
			if (food.num == 0)
			{
				if (!snake.randBron())
					isGameOver = 1;
			}
			showAll(snake, wall, food, menu);
		} while (!_kbhit() && !snake.getIsDead());

		if (snake.getLife() && snake.getIsDead())
		{
			snake.snakeToNull();//������
			//ˢ��ʳ��
			food.clearFood(snake.gameLeve);
			if (!food.randomFood())
				isGameOver = 1;
			//ˢ����
			snake.deatorySnake();
			if (!snake.randBron())
				isGameOver = 1;

			putVB(snake, wall);//�ж��Ƿ�Ҫ���ý�����ը��
		}
	}

		snake.dieNote();
		showPhoto();
		_getch();
		closegraph();
		snake.deatorySnake();
		snake.trySaveDate();
}

char getAIdir(Snake &snake,Wall &wall,Food &food, COORD p,char pre)//��ȡAI����ʳ��ķ���
{
	char d = pre;
	if (p.X < snake.getHeadX())//�����ʳ���������
	{
		if (pre == snake.RIGHT)//���ԭ���������˶�����ʱ���������Ч�ģ��ͼ��һ�����£������ϻ����ߣ��õ���ͷ
		{
			if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '*')
				d = snake.UP;
			if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '*')
				d = snake.DOWN;
		}
		else
		{
			if (wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) == '#' || wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) == '*')//������������ϰ�
			{
				if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '*')//���ϰ�ȫ������ʱ����
					d = snake.UP;
				else
				{
					if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '*')//���°�ȫ������ʱ����
						d = snake.DOWN;
				}
			}
			else//�������ȫ
				d = snake.LEFT;
		}
	}
	//���������
	//���ұ�
	if (p.X > snake.getHeadX())
	{
		if (pre == snake.LEFT)
		{
			if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '*')
				d = snake.UP;
			if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '*')
				d = snake.DOWN;
		}
		else
		{
			if (wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) == '#' || wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) == '*')
			{
				int x = snake.getHeadX() + 1;
				int y = snake.getHeadY();
				char t = wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY());
				if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '*')
					d = snake.UP;
				else
				{
					if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '*')
						d = snake.DOWN;
				}
			}
			else
				d = snake.RIGHT;
		}
	}

	if (p.X == snake.getHeadX())
	{
		//������
		if (p.Y < snake.getHeadY())
		{
			if (pre == snake.DOWN)
			{
				if (wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '*')
					d = snake.LEFT;
				if (wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '*')
					d = snake.RIGHT;
			}
			else
			{
				if (wall.getCharInMap(snake.getHeadX() , snake.getHeadY()-1) == '#' || wall.getCharInMap(snake.getHeadX() , snake.getHeadY()-1 )== '*')
				{
					if (wall.getCharInMap(snake.getHeadX()-1, snake.getHeadY() ) != '#' && wall.getCharInMap(snake.getHeadX()-1, snake.getHeadY() ) != '*')
						d = snake.LEFT;
					else
					{
						if (wall.getCharInMap(snake.getHeadX()+1, snake.getHeadY() ) != '#' && wall.getCharInMap(snake.getHeadX()+1, snake.getHeadY()) != '*')
							d = snake.RIGHT;
					}
				}
				else
					d = snake.UP;
			}
		}
		//������
		if (p.Y > snake.getHeadY())
		{
			if (pre == snake.UP)
			{
				if (wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '*')
					d = snake.LEFT;
				if (wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '*')
					d = snake.RIGHT;
			}
			else
			{
				if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) == '#' || wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) == '*')
				{

					if (wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '*')
						d = snake.LEFT;
					else
					{
						if (wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '*')
							d = snake.RIGHT;
					}
				}
				else
					d = snake.DOWN;
			}
		}

	}
	return d;
}

void AI()
{
	system("cls");
	loadPhoto(5);

	Wall wall;
	wall.initMap();

	Food food(wall);
	food.randomFood();

	//�˿��Ƶ���
	Snake snake(wall, food);
	snake.gameLeve = 5;
	snake.randBron();

	//������2��AI��
	Snake two(wall, food);
	two.gameLeve = 1;
	two.randBron();

	Snake three(wall, food);
	three.gameLeve = 1;
	three.randBron();

	Menu menu(wall);

	char dir = NULL, d = snake.UP,d3=three.UP,pre3=three.UP,d2=two.UP,pre2=two.UP;
	int sleepChange = 0;

	COORD f3 = food.getAfood(), f2 = food.getAfood();//�ֱ��������ʳ��λ����Ϣ

	while (snake.getLife() > 0)
	{
		showThreeAll(snake,two,three, wall, food, menu);//ר������չʾ���ǵĻ���

		dir = _getch();
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)
		{
			d = dir;
		}
		do//�����ѭ������һ��
		{
			//�˿��Ƶ�
			snake.moveSnake(d);
			if (food.num == 0)
				food.randomFood();

			//AI��2��
			if (food.checkIsEat(f2))//�ж�֮ǰ�������Ǹ�ʳ����û�б��Ե�
			{
				f2 = food.getAfood();//������Ե��ˣ�������һ��
			}
			d2 = getAIdir(two, wall, food, f2, pre2);//ˢ�»�÷���
			two.moveSnake(d2);//�ƶ�
			if (food.num == 0)//�����������ʳ��Ϊ0�ˣ���ˢ��ʳ��
				food.randomFood();
			if (two.getLife() && two.getIsDead())
			{
				two.snakeToNull();
				two.deatorySnake();
				two.randBron();
			}

			//��AI2��ͬ
			if (food.checkIsEat(f3))
			{
				f3 = food.getAfood();

			}
			d3 = getAIdir(three, wall, food, f3, pre3);
			three.moveSnake(d3);
			if (food.num == 0)
				food.randomFood();
			if (three.getLife() && three.getIsDead())
			{
				three.snakeToNull();
				three.deatorySnake();
				three.randBron();
			}

			snake.sleep();//ֻҪһ��ͣ��һ��
			showThreeAll(snake, two, three, wall, food, menu);
			//ר��ˢ��֮ǰAI�߷���
			pre3 = d3;
			pre2 = d2;

		} while (!_kbhit() && !snake.getIsDead());

		
		if (snake.getLife() && snake.getIsDead())
		{
			snake.snakeToNull();
			snake.deatorySnake();
			snake.randBron();
		}



	}
	//��Ϸ����
	snake.dieNote();
	showPhoto();
	_getch();
	closegraph();
	snake.deatorySnake();
	two.deatorySnake();
	three.deatorySnake();
	snake.trySaveDate();
}

void play(int gameleve)//���ݲ�ͬѡ�񣬽��벻ͬ��Ϸ
{
	initgraph(1120, 620);//�����´���
	//����ѡ��
	switch (gameleve)
	{
	case 1:
	{
		easyPlay();
		break;
	}
	case 2:
	{
		hardPlay();
		break;
	}
	case 3:
	{
		hhhardPlay();
		break;
	}
	case 4:
	{
		funPlay(4);
		break;
	}
	case 5:
	{
		AI();
		break;
	}
	}
	closegraph();
}

int main()
{
	//_mkdir("d:\\snakeDate");
	//��Ҫ��Ϊ�˳��δ򿪵�ʱ�򴴽�2�����ļ�
	ofstream out("record.txt", ios::app);
	ofstream hout("history.txt", ios::app);

	if (!out.is_open())
	{
		cout << "���������ļ�ʧ��";
		return -1;
	}
	if (!hout.is_open())
	{
		cout << "������ʷ�ļ�ʧ��";
		return -1;
	}

	out.close();
	hout.close();

	Wall wall;
	Menu  menu(wall);
	int chose;
	int gameLeve = 1;//��ʼ��Ϸ�ȼ�Ϊ1
	menu.drawMenu();
	while (TRUE)
	{
		chose = menu.chooseFunct();//ѡ��˵�����
		switch (chose)
		{
		case 1://ѡ����Ϸ
		{
			play(gameLeve);//��Ϸ
			menu.drawMenu();//���ز˵�����
			menu.isChoose = 0;
			break;
		}
		case 2:
		{
			gameLeve = menu.chosePlayLeve();//��ȡ��ѡ����Ϸ�ȼ�����������˷��ز˵�
			menu.isChoose = 0;
			break;
		}
		case 3:
		{
			menu.showScore();//չʾ��ʷ��¼
			menu.drawMenu();//����
			menu.isChoose = 0;
			break;
		}
		case 4:
		{
			menu.readHistory();//չʾ��ʷ��¼
			menu.isChoose = 0;
			break;
		}
		case 5:
			return 0;//�������
		}
	}
	return 0;
}
