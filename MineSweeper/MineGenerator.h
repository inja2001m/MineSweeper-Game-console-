#pragma once

#include <iostream>
#include <random>

using namespace std;

#define WIDTH 15
#define HEIGHT 10
#define MINECNT 20 // Total Mine

enum Tile
{
	MINE = 9
};

class Mine
{
public:
	int value;
	bool state = false;
};
class MineMap
{
private:
	inline void zeroSetMap() { for (int i = 0; i < HEIGHT; ++i) for (int j = 0; j < WIDTH; ++j) map[i][j].value = NULL; }
	inline void drawMap();
	void createMap(), createMines(), createCntMines();

public:
	MineMap();
	
	Mine map[HEIGHT][WIDTH];
};

