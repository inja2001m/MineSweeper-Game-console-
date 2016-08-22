#include "MineGenerator.h"
#include <conio.h>
#include <Windows.h>

MineMap realMap;
char blindMap[HEIGHT][WIDTH];

void init()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			blindMap[i][j] = '#';
			cout << blindMap[i][j] << " ";
		}
		cout << endl;
	}
}

void update()
{
	static int keyXpos, keyYpos;

	while (_kbhit())
	{
		switch (_getch())
		{
		case 72: if (keyYpos > 0)      keyYpos -= 2; break;
		case 75: if (keyXpos < WIDTH)  keyXpos -= 2; break;
		case 77: if (keyXpos > 0)      keyYpos += 2; break;
		case 80: if (keyYpos < HEIGHT) keyYpos += 2; break;
		default: break;
		}
	}
}

void render()
{

}

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
	init();

	return 0;
}