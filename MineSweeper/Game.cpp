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

void find0Tile(int x, int y)
{
	realMap.map[y - 1][x / 2].isVisible = true;

	if (realMap.map[y - 1][x / 2].value != 0)
	{
		gotoxy(x, y);
		cout << realMap.map[y - 1][x / 2].value;

		return;
	}

	if (y - 1 > 0          && !realMap.map[y - 1 - 1][x / 2].isVisible) find0Tile(x, y - 1);  // Up 
	if (x / 2 > 0          && !realMap.map[y - 1][x / 2 - 1].isVisible) find0Tile(x - 2, y);  // Left
	if (x / 2 < WIDTH - 1  && !realMap.map[y - 1][x / 2 + 1].isVisible) find0Tile(x + 2, y);  // Right
	if (y - 1 < HEIGHT - 1 && !realMap.map[y - 1 + 1][x / 2].isVisible) find0Tile(x, y + 1);  // Down

	gotoxy(x, y);
	cout << ".";
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
				cout << "M ";
			else 
				cout << blindMap[i][j] << " ";
		}
		cout << endl;
	}
}
bool update()
{
	switch (_getch())
	{
	case 72: if (keyYpos > 1)              keyYpos -= 1; break; // Up
	case 75: if (keyXpos > 1)              keyXpos -= 2; break; // Left
	case 77: if (keyXpos < WIDTH * 2 - 2)  keyXpos += 2; break; // Right
	case 80: if (keyYpos < HEIGHT)         keyYpos += 1; break; // Down
	case 32:  // space(Select)
		if (!realMap.map[keyYpos - 1][keyXpos / 2].isVisible)
		{
			if (realMap.map[keyYpos - 1][keyXpos / 2].value == Tile::MINE)
			{
				realMap.map[keyYpos - 1][keyXpos / 2].isVisible = true;
				return true;
			}
			else if (realMap.map[keyYpos - 1][keyXpos / 2].value == 0)
			{
				find0Tile(keyXpos, keyYpos);
			}

			realMap.map[keyYpos - 1][keyXpos / 2].isVisible = true;
		}
		break; 
	case 122: // z(Check Mine)
		if (realMap.map[keyYpos - 1][keyXpos / 2].isVisible == false)
			realMap.map[keyYpos - 1][keyXpos / 2].isState = !realMap.map[keyYpos - 1][keyXpos / 2].isState; 
		break; 
	default: break;
	}

	return false;
}
void render()
{
	static int oldKeyXpos = 1, oldKeyYpos = 1;
	
	gotoxy(oldKeyXpos, oldKeyYpos);
	if (realMap.map[oldKeyYpos - 1][oldKeyXpos / 2].isState == true)
		cout << "!";
	else if (realMap.map[oldKeyYpos - 1][oldKeyXpos / 2].isVisible == true)
	{
		if (realMap.map[oldKeyYpos - 1][oldKeyXpos / 2].value == 0)
			cout << ".";
		else
			cout << realMap.map[oldKeyYpos - 1][oldKeyXpos / 2].value;
	}
	else
		cout << "#";

	gotoxy(keyXpos, keyYpos);
	if (realMap.map[keyYpos - 1][keyXpos / 2].isState == true)
		cout << "!";
	else if (realMap.map[keyYpos - 1][keyXpos / 2].isVisible == true)
	{ } // Change when push the space bar
	else
		cout << "M";

	oldKeyXpos = keyXpos;
	oldKeyYpos = keyYpos;
}

void inGame()
{
	bool isdead = false;

	init();
	do
	{
		isdead = update();
		render();
	} while (isdead == false);
}

int main()
{
	inGame();

	gotoxy(1, 20);
	cout << "게임오버!";
	_getch();

//	realMap.drawMap();

	return 0;
}