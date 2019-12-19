#include <string>
#include <iostream>
//#include "Game.cpp"
#include "Grid.h"

using std::endl;
using std::cin;
using std::cout;

const string layout1 = "O-----O---------O------O-----O-O-O-----O---O-----O-----O---OOO---O---------O-O---O----------------OO";
extern void place_ships_to_grid(Grid target, Tile::states default_tile);
extern bool is_killed(Grid &target, char column_c, int row);
int main()
{
	cout << HINT;
	Grid player_grid1("player - himself"/*, true*/);
	Grid player_grid2("player - bot"/*, false*/);
	Grid bot_grid1("bot - himself", layout1);
	bot_grid1.Display();
	Grid bot_grid2("bot - player"/*, true*/);
	bot_grid1.Display();
	
	/*
	place_ships_to_grid(player_grid1, Tile::free);

	// AI's installation needed here

	while ((player_grid1.Count_ships > 0) && (bot_grid.Count_ships > 0))
	{
		int row;
		char column_c;
		int res;
		do
		{
			cout << "Shoot! <char column> <int row>" << endl;
			cin >> column_c >> row;
			res = player_grid1.Shoot(bot_grid, column_c, row);
		} while ((res == 4) || (res == 1));
		
	}
	*/
}
