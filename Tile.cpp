#include "Tile.h"
#include <iostream>


Tile::Tile()
{
	this->state = Tile::unknown;
}

Tile::Tile(char c)
{
	switch (c)
	{
		case 'u': this->state = Tile::unknown;
			break;
		case 'f': this->state = Tile::free;
			break;
		case 's': this->state = Tile::ship;
			break;
		case 'h': this->state = Tile::shot;
			break;
		default:break;
	}
	
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