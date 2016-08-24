#include "MineGenerator.h"
#include <conio.h>
#include <Windows.h>

MineMap realMap;
int keyXpos, keyYpos;
int oldKeyXpos, oldKeyYpos;
int totalTileCnt, totalMineCnt;

enum PlayState
{
	GAMEOVER = 0,
	GAMECLEAR = 1,
	GAMING = 2
};

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void find0Tile(int x, int y)
{
	realMap.map[y - 1][x / 2].isVisible = true;
	--totalTileCnt;

	if (realMap.map[y - 1][x / 2].isState == true)
	{
		realMap.map[y - 1][x / 2].isState = false;
		++totalMineCnt;
	}
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
	system("cls");

	keyXpos = keyYpos = oldKeyXpos = oldKeyYpos = 1;
	
	gotoxy(WIDTH * 2 + 10, 2);
	cout << " 忙式式式式式式式式式忖";
	gotoxy(WIDTH*2 + 10, 3);
	cout << " H曳Move: Arrow      弛T";
	gotoxy(WIDTH*2 + 10, 4);
	cout << " O曳Select: Space bar弛";
	gotoxy(WIDTH*2 + 10, 5);
	cout << " W曳Check the mine: Z弛O";
	gotoxy(WIDTH * 2 + 10, 6);
	cout << " 戌式式式式式式式式式戎";

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH * 2; j += 2)
		{
			gotoxy(j + 1, i + 1);
			if (i == 0 && j == 0) cout << 'M';
			else cout << '#';
		}
	}

	totalTileCnt = WIDTH * HEIGHT;
	totalMineCnt = MINECNT;

	realMap.createMap();

	gotoxy(1, HEIGHT + 2);
	cout << "The number of mines: " << totalMineCnt << " ";
}
int update()
{
	// Game clear code
	if (totalTileCnt == MINECNT)
	{
		return PlayState::GAMECLEAR;
	}
	
	// Input the key code
	switch (_getch())
	{
	case 72: if (keyYpos > 1)              keyYpos -= 1; break; // Up
	case 75: if (keyXpos > 1)              keyXpos -= 2; break; // Left
	case 77: if (keyXpos < WIDTH * 2 - 2)  keyXpos += 2; break; // Right
	case 80: if (keyYpos < HEIGHT)         keyYpos += 1; break; // Down
	case 32:  // space(Select)
		if (realMap.map[keyYpos - 1][keyXpos / 2].isState == false)
		{
			if (realMap.map[keyYpos - 1][keyXpos / 2].isVisible == false)
			{
				if (realMap.map[keyYpos - 1][keyXpos / 2].value == Tile::MINE)
				{
					realMap.map[keyYpos - 1][keyXpos / 2].isVisible = true;
					--totalTileCnt;
					return PlayState::GAMEOVER;
				}
				else if (realMap.map[keyYpos - 1][keyXpos / 2].value == 0)
				{
					find0Tile(keyXpos, keyYpos);
				}
				else
				{
					realMap.map[keyYpos - 1][keyXpos / 2].isVisible = true;
					--totalTileCnt;
				}
			}
		}
		break; 
	case 122: // z(Check Mine)
		if (realMap.map[keyYpos - 1][keyXpos / 2].isVisible == false && totalMineCnt > 0 || 
			(totalMineCnt == 0 && realMap.map[keyYpos - 1][keyXpos / 2].isState == true))
		{
			realMap.map[keyYpos - 1][keyXpos / 2].isState = !realMap.map[keyYpos - 1][keyXpos / 2].isState;

			if (realMap.map[keyYpos - 1][keyXpos / 2].isState == true)
				--totalMineCnt;
			else
				++totalMineCnt;
		}
		break; 
	default: break;
	}

	return PlayState::GAMING;
}
void render()
{
	if (totalMineCnt >= 0)
	{
		gotoxy(1, HEIGHT + 2);
		cout << "The number of mines: " << totalMineCnt << " ";
	}

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
	int isState;

	init();
	do
	{
		isState = update();
		render();
	} while (isState == PlayState::GAMING);

	if (isState == PlayState::GAMECLEAR)
	{
		gotoxy(25, HEIGHT + 9);
		cout << "≠GAME CLEAR≠";
	}
	else if (isState == PlayState::GAMEOVER)
	{
		printf("\a");

		gotoxy(27, HEIGHT + 6);
		cout << "9 = Mine";

		gotoxy(27, HEIGHT + 9);
		cout << "GAME OVER";

		for (int i = 0; i < HEIGHT; ++i)
		{
			for (int j = 0, k = 0; j < WIDTH * 2 - 1; j += 2, ++k)
			{
				if (realMap.map[i][k].isState == true || realMap.map[i][k].isVisible == false)
				{
					gotoxy(j + 1, i + 1);
					if(realMap.map[i][k].value != 0) cout << realMap.map[i][k].value;
					else cout << ".";
				}
			}
		}
	}
}

int main()
{
	while (1)
	{
		inGame();

		gotoxy(25, HEIGHT + 11);
		cout << "RESTART = ANY KEY";
		gotoxy(25, HEIGHT + 12);
		cout << "ESC     = EXIT";

		if (_getch() == 27) return 0;

	}
	return 0;
}