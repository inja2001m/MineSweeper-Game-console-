#include "MineGenerator.h"
#include <conio.h>
#include <Windows.h>

MineMap realMap;
char blindMap[HEIGHT][WIDTH];
int keyXpos, keyYpos;

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init()
{
	keyXpos = keyYpos = 1;
	
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			blindMap[i][j] = '#';

			if(i == 0 && j == 0) 
				cout << "H ";
			else 
				cout << blindMap[i][j] << " ";
		}
		cout << endl;
	}
}

void update()
{
	switch (_getch())
	{
	case 72: if (keyYpos > 1)              keyYpos -= 1; break; // Up
	case 75: if (keyXpos > 1)              keyXpos -= 2; break; // Left
	case 77: if (keyXpos < WIDTH * 2 - 2)  keyXpos += 2; break; // Right
	case 80: if (keyYpos < HEIGHT)         keyYpos += 1; break; // Down
	case 32:  break; // space(Select)
	case 122: realMap.map[keyYpos - 1][keyXpos / 2].state = !realMap.map[keyYpos - 1][keyXpos / 2].state; break; // z(Check Mine)
	default: break;
	}
}

void render()
{
	static int oldKeyXpos = 1, oldKeyYpos = 1;
	
	gotoxy(oldKeyXpos, oldKeyYpos);
	if (realMap.map[oldKeyYpos - 1][oldKeyXpos / 2].state == true)
		cout << "!";
	else
		cout << "#";

	gotoxy(keyXpos, keyYpos);
	if (realMap.map[keyYpos - 1][keyXpos / 2].state == true)
		cout << "!";
	else
		cout << "M";

	oldKeyXpos = keyXpos;
	oldKeyYpos = keyYpos;
}

int main()
{
	init();

	while (1)
	{
		update();
		render();
	}

	//while (1)
	//{
	//	switch (_getch())
	//	{
	//	case 122:
	//		cout << "asdasd" << endl; break;
	//	}
	//}

	return 0;
}