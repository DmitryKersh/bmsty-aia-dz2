#include "Grid.h"
#include <iostream>
#include <string>


Grid::Grid(string owner/*, bool is_opened_to_owner*/)
{
	this->owner = owner;
	Tile* empty_tile = new Tile(Tile::unknown);
	//if (is_opened_to_owner) empty_tile->state = Tile::free;
		
	for (int i = 99; i >= 0; i--)
	{
		this->tiles[i] = *empty_tile;
	}
	delete empty_tile;
}

Grid::Grid(string owner, string layout)
{
	Tile* empty_tile = new Tile(Tile::free);
	this->owner = owner;
	for (int i = 0; i <= 99; i++)
	{
		this->tiles[i] = *empty_tile;
		if (layout[i] == 'O') this->tiles[i].state = Tile::ship;
	}
}

Grid::~Grid()
{
}

void Grid::Display()
{
	std::cout << this->owner << "'s grid:" << std::endl;
	std::cout << "   A B C D E F G H I J " << std::endl;
	for (std::pair<int, Tile> pair : this->tiles)
	{
		if (pair.first % 10 == 0)
		{
			std::cout.width(2);
			std::cout << pair.first/10 + 1;
			std::cout << '|' ;
		}
		pair.second.Display();
		if (pair.first % 10 == 9) std::cout << '|' << std::endl;		
	}
}

int Grid::Place_ship(int size, char orientation, int row, char column_c)
{
	int column = (int)column_c - (int)'a';
	row--; //column--;
	if((orientation == 'h') && (column - 1 + size >= 10) || (orientation == 'v') && (row - 1 + size >= 10))
	{
		std::cout << "CANNOT PLACE THIS SHIP HERE" << std::endl;
		return 1;
	}
	int tile_number = 10 * row + column;

	if (orientation == 'h')
	{
		for (int i = 0; i < size; i++)
		{
			if (this->tiles[tile_number + i].state != Tile::unknown)
			{
				std::cout << "CANNOT PLACE THIS SHIP HERE" << std::endl;
				return 1;
			}
		}
		if (column != 0)
		{
			this->tiles[tile_number - 1].state = Tile::free;
			if (row != 0) this->tiles[tile_number - 11].state = Tile::free;
			if (row != 9) this->tiles[tile_number + 9].state = Tile::free;
		}
		if (column != 9)
		{
			this->tiles[tile_number + (size - 1) + 1].state = Tile::free;
			if (row != 9) this->tiles[tile_number + (size - 1) + 11].state = Tile::free;
			if (row != 0) this->tiles[tile_number + (size - 1) - 9].state = Tile::free;
		}
		for (int i = 0; i < size; i++)
		{
			this->tiles[tile_number + i].state = Tile::ship;
			if (row != 0)this->tiles[tile_number + i - 10].state = Tile::free;
			if (row != 9) this->tiles[tile_number + i + 10].state = Tile::free;
		}
	}
	if (orientation == 'v')
	{
		for (int i = 0; i < size; i++)
		{
			if (this->tiles[tile_number + 10 * i].state != Tile::unknown)
			{
				std::cout << "CANNOT PLACE THIS SHIP HERE" << std::endl;
				return 1;
			}
		}
		if (row != 0)
		{
			this->tiles[tile_number - 10].state = Tile::free;
			if (column != 0) this->tiles[tile_number - 11].state = Tile::free;
			if (column != 9) this->tiles[tile_number - 9].state = Tile::free;
		}
		if (row != 9)
		{
			this->tiles[tile_number + (size - 1)*10 + 10].state = Tile::free;
			if (column != 9) this->tiles[tile_number + (size - 1)*10 + 11].state = Tile::free;
			if (column != 0) this->tiles[tile_number + (size - 1)*10 + 9].state = Tile::free;
		}
		for (int i = 0; i < size; i++)
		{
			this->tiles[tile_number + 10*i].state = Tile::ship;
			if (column != 0)this->tiles[tile_number + 10*i - 1].state = Tile::free;
			if (column != 9) this->tiles[tile_number + 10*i + 1].state = Tile::free;
		}
	}
	return 0;
}

int Grid::Shoot(Grid &target, char column_c, int row)
{
	row--;
	int column = (int)column_c - (int)'a';
	if (column >= 10) return 1;
	if (row >= 10) return 1;
	int tile_number = 10 * row + column;
	//if (this->tiles[tile_number].state != Tile::unknown) return 2;
	
	if (target.tiles[tile_number].state == Tile::free)
	{
		this->tiles[tile_number].state = Tile::free;
		return 3;
	}
	if (target.tiles[tile_number].state == Tile::ship)
	{
		this->tiles[tile_number].state = Tile::shot;
		target.tiles[tile_number].state = Tile::shot;
		return 4;
	}
	return 0;
}

int Grid::Count_ships()
{
	int res = 0;
	for (std::pair<int, Tile> pair : this->tiles)
	{
		if (pair.second.state == Tile::ship) res++;
	}
	return res;
}