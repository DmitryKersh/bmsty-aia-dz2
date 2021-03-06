#ifndef GAME_CPP
#define GAME_CPP

#include <iostream>
#include "Grid.h"

using std::endl;
using std::cin;
using std::cout;



void place_ships_to_grid(Grid &target, Tile::states default_tile)
{
	char orientation;
	char column_c;
	int row;
	cout << "enter <h-horizontal,v-vertical><char column> <int row> for each ship; for 1-ship don't enter first param" << endl;

	cout << "4-ship:"  << endl;
	cin >> orientation >> column_c >> row;
	target.Place_ship(4, orientation, row, column_c);
	target.Display();
	for (int i = 0; i < 2; i++)
	{
		cout << "3-ship:" << endl;
		cin >> orientation >> column_c >> row;
		target.Place_ship(3, orientation, row, column_c);
		target.Display();
	}
	for (int i = 0; i < 3; i++)
	{
		cout << "2-ship:" << endl;
		cin >> orientation >> column_c >> row;
		target.Place_ship(2, orientation, row, column_c);
		target.Display();
	}

	for (int i = 0; i < 4; i++)
	{
		cout << "1-ship:" << endl;
		cin >> column_c >> row;
		target.Place_ship(1, 'h', row, column_c);
		target.Display();
	}
	for (int i = 0; i < 100; i++)
		if (target.tiles[i].state != Tile::ship) target.tiles[i].state = default_tile;
	target.Display();
}

bool is_killed (Grid &target, char column_c, int row)//that algorithm really sucks
{
	row--;
	int column = (int)column_c - (int)'a';
	if (target.tiles[10 * row + column].state != Tile::shot) return false;
	//cout << row << column << ' ';
	if (row != 0)
	{
		Tile* tile = &(target.tiles[10 * (row - 1) + column]);
		if (tile->state == Tile::ship) return false;
		if ((tile->state == Tile::shot) && (row - 1 != 0))
		{
			Tile* tile2 = &(target.tiles[10 * (row - 2) + column]);
			if (tile2->state == Tile::ship) return false;
			if ((tile2->state == Tile::shot) && (row - 2 != 0))
			{
				Tile* tile3 = &(target.tiles[10 * (row - 3) + column]);
				if (tile3->state == Tile::ship) return false;
				if (tile3->state == Tile::shot) return true;				
			}
		}				
	}
	if (column != 0)
	{
		Tile* tile = &(target.tiles[10 * row + column - 1]);
		if (tile->state == Tile::ship) return false;
		if ((tile->state == Tile::shot) && (column - 1 != 0))
		{
			Tile* tile2 = &(target.tiles[10 * row + column - 2]);
			if (tile2->state == Tile::ship) return false;
			if ((tile2->state == Tile::shot) && (column - 2 != 0))
			{
				Tile* tile3 = &(target.tiles[10 * row + column - 3]);
				if (tile3->state == Tile::ship) return false;
				if (tile3->state == Tile::shot) return true;
			}
		}
	}
	if (row != 9)
	{
		Tile* tile = &(target.tiles[10 * (row + 1) + column]);
		if (tile->state == Tile::ship) return false;
		if ((tile->state == Tile::shot) && (row + 1 != 9))
		{
			Tile* tile2 = &(target.tiles[10 * (row + 2) + column]);
			if (tile2->state == Tile::ship) return false;
			if ((tile2->state == Tile::shot) && (row + 2 != 9))
			{
				Tile* tile3 = &(target.tiles[10 * (row + 3) + column]);
				if (tile3->state == Tile::ship) return false;
				if (tile3->state == Tile::shot) return true;
			}
		}
	}
	if (column != 9)
	{
		Tile* tile = &(target.tiles[10 * row + column + 1]);
		if (tile->state == Tile::ship) return false;
		if ((tile->state == Tile::shot) && (column + 1 != 9))
		{
			Tile* tile2 = &(target.tiles[10 * row + column + 2]);
			if (tile2->state == Tile::ship) return false;
			if ((tile2->state == Tile::shot) && (column + 2 != 9))
			{
				Tile* tile3 = &(target.tiles[10 * row + column + 3]);
				if (tile3->state == Tile::ship) return false;
				if (tile3->state == Tile::shot) return true;
			}
		}
	}
	return true;
}

void mark_killed(Grid &locator, Grid &field)
{
	for(int i = 0; i <= 99; i++)
		if(is_killed(field,(char)('a' + i/10),i%10 + 1))
			locator.Shoot_around((char)('a' + i/10),i%10 + 1);
}


int ai_random(Grid &target)
{
	srand(time(NULL));
	for(int i = 0;; i++)
	{
		if((target.tiles[i].state == Tile::unknown) && (rand() % 50 == 0)) return i;
		if(i == 99) i = 0;
	}
}
int ai_if_hit(Grid &target, int last_hit)
{
	srand(time(NULL));

	while(true)
	{
	    int unable_counter = 0;
		int able_max = 0;
		
		if(last_hit % 10)
		{
			able_max++;
			if(target.tiles[last_hit-1].state == Tile::unknown)
			{
				//if(rand() % 10== 0)
					return last_hit - 1;
			}
			else unable_counter++;
		}
		if(last_hit % 10 != 9)
		{
			able_max++;
			if(target.tiles[last_hit+1].state == Tile::unknown)
			{
				//if(rand() % 10== 0)
					return last_hit + 1;
			}
			else unable_counter++;
		}
		if(last_hit / 10)
		{
			able_max++;
			if(target.tiles[last_hit-10].state == Tile::unknown)
			{
				//if(rand() % 10== 0)
					return last_hit - 10;
			}
			else unable_counter++;
		}
		if(last_hit / 10 != 9)
		{
			able_max++;
			if(target.tiles[last_hit+10].state == Tile::unknown)
			{
				//if(rand() % 10 == 0)
					return last_hit + 10;
			}
			else unable_counter++;
		}
		if(unable_counter >= able_max) return 222;
	}
}

#endif // !GAME_CPP