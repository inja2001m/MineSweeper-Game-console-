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
				// 盖 困 贸府x
				if (i != 0)
					if (map[i - 1][j] == MINE) ++map[i][j];

				// 盖 哭率 贸府x
				if (j != 0)
				{
					if (map[i - 1][j - 1] == MINE) ++map[i][j];
					if (map[i][j - 1] == MINE) ++map[i][j];
					if (map[i + 1][j - 1] == MINE) ++map[i][j];
				}

				// 盖 坷弗率 贸府x
				if (j != WIDTH - 1)
				{
					if (map[i - 1][j + 1] == MINE) ++map[i][j];
					if (map[i][j + 1] == MINE) ++map[i][j];
					if (map[i + 1][j + 1] == MINE) ++map[i][j];
				}

				// 盖 酒贰 贸府x
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
