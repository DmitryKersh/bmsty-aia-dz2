#include "Tile.h"
#include <iostream>


Tile::Tile()
{
	this->state = Tile::unknown;
}

Tile::Tile(Tile::states c)
{
	this->state = c;
}


Tile::~Tile()
{
}

void Tile::Display()
{
	char c;
	switch (this->state)
	{
	case Tile::unknown: c = '?';
		break;
	case Tile::free: c = '-';
		break;
	case Tile::ship: c = 'O';
		break;
	case Tile::shot: c = '#'; 
		break;
	default:
		break;
	}
	std::cout << c << ' ';
}