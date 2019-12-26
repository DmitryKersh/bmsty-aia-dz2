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
    int last_hit; int res = 0; int ai_decision;
    bool shot_is_not_random = false;

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
            res = (player_grid2.Shoot(bot_grid1, column_c, row));
            mark_killed(player_grid2,bot_grid1);
            player_grid2.Display();
		} while (res == 4);

		do {
            if(shot_is_not_random)
            {
                ai_decision = ai_if_hit(player_grid1,last_hit);
                if(ai_decision == 222)
                {
                    ai_decision = ai_random(player_grid1);
                    shot_is_not_random = true;
                }
            }
            else ai_decision = ai_random(player_grid1);
            res = bot_grid2.Shoot(player_grid1,(char)(ai_decision/10 + (int)'a'), ai_decision%10);
            if(res == 4)
            {
                shot_is_not_random = true;
                last_hit = ai_decision;
            }

			mark_killed(bot_grid2,player_grid1);
            bot_grid2.Display();
		} while (res == 4);
		cout << "NEXT TURN\n";
	}
}
