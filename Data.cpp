//保存游戏数据的代码文件
#include <conio.h>
#include <Windows.h>
#include <iostream>


#define UP	  0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

//清理光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

class _TanksClass
{
public:

	
	//用来存储坦克相关的结构体
	typedef struct _TANKINFO
	{
		//存储坐标
		COORD pos;
		//存储方向
		int nDir;
		//血量
		int nHP;
		//攻击力量
		int nATK;
		//等级
		int nLevel;
		//速度
		int nSpeed;
		//移动过的时间
		int nClock;
		//随机移动步数
		int nOper[10];

	}TANKINFO;

	//用来存储子弹信息的结构体
	typedef struct _BULLETINFO
	{
		//存储坐标
		COORD pos;
		//存储方向
		int nDir;
		//血量
		int nHP;
		//攻击力量
		int nATK;
		//等级
		int nLevel;
		//速度
		int nSpeed;
		//移动过的时间
		int nLastClock;
		//子弹颜色
		int nColor;
		//存储子弹样式
		char cBuller = '◯';

	}BULLETINFO;

	//定义坦克结构体的对象
	TANKINFO g_stcTank;

	//定义子弹结构体的对象
	BULLETINFO g_stcBullet;

	//获取键盘输入控制坦克方向
	void InPut()
	{
		//控制方向的循环已废弃
		/*while (true)
		{*/

		//通过接受键盘输入判断坦克方向
			cInput = GetOper();
			switch (cInput)
			{
			case 'w':
				//判断之前输入的方向与现在输入的方向是否相同，
				if (g_stcTank.nDir != 0 )
				{
					//不相同将方向转为输入的方向
					g_stcTank.nDir = UP;
				}
				else
				{
					//相同向同方向移动坐标
					g_stcTank.pos.Y--;
				}
				break;
			case 's':
				if (g_stcTank.nDir != 1)
				{
					g_stcTank.nDir = DOWN;
				}
				else
				{
					g_stcTank.pos.Y++;
				}
				break;
			case 'a':
				if (g_stcTank.nDir != 2)
				{
					g_stcTank.nDir = LEFT;
				}
				else
				{
					g_stcTank.pos.X--;
				}
				break;
			case 'd':
				if (g_stcTank.nDir != 3)
				{
					g_stcTank.nDir = RIGHT;
				}
				else
				{
					g_stcTank.pos.X++;
				}
				break;
			case 'j':
				g_stcBullet.nSpeed = 100;
				g_stcBullet.nLastClock = clock();
				switch (g_stcTank.nDir)
				{
				case UP:
					g_stcBullet.nDir = g_stcTank.nDir;
					g_stcBullet.pos.X = g_stcTank.pos.X;
					g_stcBullet.pos.Y = g_stcTank.pos.Y - 2;
					break;
				case DOWN:
					g_stcBullet.nDir = g_stcTank.nDir;
					g_stcBullet.pos.X = g_stcTank.pos.X;
					g_stcBullet.pos.Y = g_stcTank.pos.Y + 2;
					break;
				case LEFT:
					g_stcBullet.nDir = g_stcTank.nDir;
					g_stcBullet.pos.X = g_stcTank.pos.X - 2;
					g_stcBullet.pos.Y = g_stcTank.pos.Y;
					break;
				case RIGHT:
					g_stcBullet.nDir = g_stcTank.nDir;
					g_stcBullet.pos.X = g_stcTank.pos.X + 2;
					g_stcBullet.pos.Y = g_stcTank.pos.Y;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		/*}*/
	}
	
	//绘制坦克
	void TankDraw(TANKINFO g_stcTank)
	{
		////将方向信息存入nDir变量中
		//int nDir = g_stcTank.nDir;
		////将核心x坐标信息存入x1变量中
		//int x1 = g_stcTank.pos.X;
		////将核心x坐标信息存入x1变量中
		//int y1 = g_stcTank.pos.Y;

		//通过循环对什么方向的坦克进行绘制
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				//g_stcTank.nDir记录方向
				if (Tanks[g_stcTank.nDir][y][x] != 0)
				{
					//g_stcTank.pos.X和g_stcTank.pos.Y记录中心坐标
					WriteChar(g_stcTank.pos.X - 1 + x, g_stcTank.pos.Y - 1 + y, "□");
				}
			}
		}
	}

	//清理坦克
	void TanksClear()
	{
		/*int nDir = g_stcTank.nDir;*/
		//与绘制坦克一样
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				WriteChar(g_stcTank.pos.X - 1 + x, g_stcTank.pos.Y - 1 + y, "  ");
			}
		}
	}

	//坦克移动
	/*void TanksMove()
	{
		switch (g_stcTank.nDir)
		{
		case 0:
			Tanks[g_stcTank.nDir][g_stcTank.pos.Y--][g_stcTank.pos.X];
			break;
		case 1:
			Tanks[g_stcTank.nDir][g_stcTank.pos.Y++][g_stcTank.pos.X];
			break;
		case 2:
			Tanks[g_stcTank.nDir][g_stcTank.pos.Y][g_stcTank.pos.X--];
			break;
		case 3:
			Tanks[g_stcTank.nDir][g_stcTank.pos.Y][g_stcTank.pos.X++];
			break;
		default:
			break;
		}
	}*/

	//子弹移动
	void BulletMove()
	{
		if (clock() - g_stcBullet.nLastClock > g_stcBullet.nSpeed)
		{
			BulletClear();
			g_stcBullet.nLastClock = clock();
			switch (g_stcBullet.nDir)
			{
			case UP:
				g_stcBullet.pos.Y--;
				break;
			case DOWN:
				g_stcBullet.pos.Y++;
				break;
			case LEFT:
				g_stcBullet.pos.X--;
				break;
			case RIGHT:
				g_stcBullet.pos.X++;
				break;
			default:
				break;
			}
			BulletDraw();
		}
	}

	//绘制子弹
	void BulletDraw()
	{
		WriteChar(g_stcBullet.pos.X, g_stcBullet.pos.X,"●");
	}

	//擦除子弹
	void BulletClear()
	{
		WriteChar(g_stcBullet.pos.X, g_stcBullet.pos.Y, "  ");
	}

	//整个坦克调用函数
	void TanksPort()
	{
		//初始化坦克x轴坐标
		g_stcTank.pos.X = 10;
		//初始化坦克y轴坐标
		g_stcTank.pos.Y = 20;
		//初始化坦克方向
		g_stcTank.nDir = UP;
		//初始打印坦克
		TankDraw(g_stcTank);
		while (true)
		{
			//清除坦克
			TanksClear();

			//擦除子弹
			//获取键盘输入控制方向
			InPut();
			/*TanksMove();*/
			//打印坦克
			TankDraw(g_stcTank);

			//控制子弹
			BulletMove();
			//控制循环速度
			Sleep(100);
		}
	}

private:

	//坦克上下左右方向的形状
	int Tanks[4][3][3] =
	{
		{
			{0,1,0},
			{1,1,1},
			{1,0,1}
		},
		{
			{1,0,1},
			{1,1,1},
			{0,1,0}
		},
		{
			{0,1,1},
			{1,1,0},
			{0,1,1}
		},
		{
			{1,1,0},
			{0,1,1},
			{1,1,0}
		}
	};

	//字符类型输出到坐标
	void WriteChar(int x, int y, const char* szBuf)
	{
		COORD pos = { x * 2,y };
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut, pos);
		std::cout << szBuf;
	}

	//判断获取键盘输入并输入到缓冲区用来控制坦克方向
	char GetOper()
	{
		//判断是否有按键输入并输入到缓冲区没有输入时一直是哪一个按键
		if (_kbhit())
		{
			//返回获取的按键输入不会对缓冲区刷新
			return _getch();
		}
		else
		{
			//没有按键输入返回零
			return 0;
		}
	}

	//用于存储坦克方向
	char cInput = 0;
	
};

_TanksClass tanke;
int main ()
{
	HideCursor();
	
	tanke.TanksPort();

}