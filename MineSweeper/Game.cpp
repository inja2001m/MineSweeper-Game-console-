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