#include <iostream>
#include <Windows.h>
#include <random>

using namespace std;

#define WIDTH 15
#define HEIGHT 10
#define MINECNT 20 // 지뢰의 개수

enum Tile
{
	MINE = 9
};

int map[HEIGHT][WIDTH];

inline void zeroSetMap() { for (int i = 0; i < HEIGHT; ++i) for (int j = 0; j < WIDTH; ++j) map[i][j] = NULL; }
inline void drawMap();
void createMap(), createMines(), createCntMines();

void createMap()
{
	zeroSetMap();
	
	createMines();
	createCntMines();
}
void createMines()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> widthDist(0, WIDTH - 1);
	uniform_int_distribution<> heightDist(0, HEIGHT - 1);

	int width, height, nMine = MINECNT;

	while (nMine)
	{
		do
		{
			width = widthDist(gen);
			height = heightDist(gen);
		} while (map[height][width] == MINE);

		map[height][width] = MINE;
		
		--nMine;
	}
}
void createCntMines()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (map[i][j] == 0)
			{
				// 맨 위 처리x
				if (i != 0) 
					if (map[i - 1][j]     == MINE) ++map[i][j];
		
				// 맨 왼쪽 처리x
				if (j != 0) 
				{
					if (map[i - 1][j - 1] == MINE) ++map[i][j];
					if (map[i]    [j - 1] == MINE) ++map[i][j];
					if (map[i + 1][j - 1] == MINE) ++map[i][j];
				}

				// 맨 오른쪽 처리x
				if (j != WIDTH - 1) 
				{
					if (map[i - 1][j + 1] == MINE) ++map[i][j];
					if (map[i]    [j + 1] == MINE) ++map[i][j];
					if (map[i + 1][j + 1] == MINE) ++map[i][j];
				}

				// 맨 아래 처리x
				if (i != HEIGHT - 1) 
					if (map[i + 1][j]     == MINE) ++map[i][j];
			}
		}
	}
}

inline void drawMap()
{
	int cntMine = 0;

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			cout << map[i][j] << " ";

			if (map[i][j] == 9) ++cntMine;
		}
		cout << endl;
	}
	cout << "cntMine: " << cntMine << endl;
}

int main()
{
	while (1)
	{
		createMap();

		drawMap();

		system("pause");
		system("cls");
	}
	return 0;
}