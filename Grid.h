#pragma once
#include "Tile.h"
#include <iostream>
#include <map>

using std::map;
using std::string;

const string HINT = "YOU HAVE 4 1-SHIPS, 3 2-SHIPS, 2 3-SHIPS AND A 4-SHIP\nTO PLACE A SHIP ENTER <SIZE><ORIENTATION (H/V)><ROW><COLUMN>\n";

class Grid
{
public:
	Grid(string owner);
	~Grid();

	string owner;
	map<int, Tile> tiles;

	void Display();
	int Place_ship(int size, char orientation, int row, int column);
	int Shoot(Grid target, char column, int row);
	int Count_ships();
};

