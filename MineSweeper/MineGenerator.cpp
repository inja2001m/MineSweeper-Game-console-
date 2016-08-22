#include "MineGenerator.h"

MineMap::MineMap()
{
	createMap();
}

void MineMap::createMap()
{
	zeroSetMap();

	createMines();
	createCntMines();
}

void MineMap::createMines()
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

void MineMap::createCntMines()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (map[i][j] == 0)
			{
				// At the top process X
				if (i != 0)
					if (map[i - 1][j] == MINE) ++map[i][j];

				//  At the left process X
				if (j != 0)
				{
					if (map[i - 1][j - 1] == MINE) ++map[i][j];
					if (map[i][j - 1] == MINE) ++map[i][j];
					if (map[i + 1][j - 1] == MINE) ++map[i][j];
				}

				//  At the right process X
				if (j != WIDTH - 1)
				{
					if (map[i - 1][j + 1] == MINE) ++map[i][j];
					if (map[i][j + 1] == MINE) ++map[i][j];
					if (map[i + 1][j + 1] == MINE) ++map[i][j];
				}

				//  At the bottom process X
				if (i != HEIGHT - 1)
					if (map[i + 1][j] == MINE) ++map[i][j];
			}
		}
	}
}

inline void MineMap::drawMap()
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
