#pragma once

#include <iostream>
#include <random>

using namespace std;

#define WIDTH 5
#define HEIGHT 5
#define MINECNT 1 // Total Mine

enum Tile
{
	MINE = 9
};

class Mine
{
public:
	int value;
	bool isState = false;
	bool isVisible = false;
};
class MineMap
{
private:
	inline void zeroSetMap() { for (int i = 0; i < HEIGHT; ++i) for (int j = 0; j < WIDTH; ++j) map[i][j].value = NULL; }
	//inline void drawMap();
	void createMap(), createMines(), createCntMines();

public:
	MineMap();
	void drawMap();
	
	Mine map[HEIGHT][WIDTH];
};

