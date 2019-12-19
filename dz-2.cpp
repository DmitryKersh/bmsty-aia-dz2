#include <string>
#include <iostream>
//#include "Game.cpp"
#include "Grid.h"

using std::endl;
using std::cin;
using std::cout;

const string layout1 = "O-----O---------O------O-----O-O-O-----O---O-----O-----O---OOO---O---------O-O---O----------------OO";

extern int ai_if_hit(Grid &target, int previous);
extern int ai_random(Grid &target);
extern void mark_killed(Grid &locator, Grid &field);
extern void place_ships_to_grid(Grid &target, Tile::states default_tile);
extern bool is_killed(Grid &target, char column_c, int row);
int main()
{
	cout << HINT;
	Grid player_grid1("player - himself");
	Grid player_grid2("player - bot");
	Grid bot_grid1("bot - himself", layout1);
	Grid bot_grid2("bot - player");

    place_ships_to_grid(player_grid1, Tile::free);
	//mark_killed(player_grid2,bot_grid1);

	while(player_grid1.Count_ships() || bot_grid1.Count_ships())
	{
		char column_c;
		int row;
		do {
			mark_killed(player_grid2,bot_grid1);
			player_grid2.Display();
			cout << "Enter <char column><int row> to shoot" << endl;
			cin >> column_c >> row;

		} while(player_grid2.Shoot(bot_grid1, column_c, row) == 4);
        int res = 0;
        int hit_number = 0;
        bool hit = false;
        int ai_decision;
        int saved_decision;

		do {
			if(hit) ai_decision = ai_if_hit(bot_grid2,saved_decision);
                else ai_decision = ai_random(bot_grid2);
            saved_decision = ai_decision;

			res = bot_grid2.Shoot(player_grid1,(char)(saved_decision/10 + 'a'), saved_decision % 10);
			if(res == 4)
            {
                hit = true;
                hit_number = saved_decision;
            }
                else hit = false;
			bot_grid2.Display();
			mark_killed(bot_grid2,player_grid1);
		} while (res == 4);
		cout << "NEXT TURN\n";
	}
}
