//#include "Grid.h"
#include "Game.cpp"
#include <string>
#include <iostream>

using std::cin;
using std::cout;

int main()
{

	cout << HINT;
	Grid player_grid("player");
	player_grid.Place_ship(4, 'h', 3, 3);
	player_grid.Place_ship(2, 'v', 1, 1);
	player_grid.Place_ship(1, 'h', 8, 1);
	player_grid.Display();
}
