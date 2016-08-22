#pragma once

#include <iostream>
#include <random>

using namespace std;

#define WIDTH 15
#define HEIGHT 10
#define MINECNT 20 // 지뢰의 개수

enum Tile
{
	MINE = 9
};

class MineMap
{
private:
	inline void zeroSetMap() { for (int i = 0; i < HEIGHT; ++i) for (int j = 0; j < WIDTH; ++j) map[i][j] = NULL; }
	inline void drawMap();
	void createMap(), createMines(), createCntMines();

public:
	MineMap();

	int map[HEIGHT][WIDTH];
};

