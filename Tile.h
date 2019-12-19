#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	enum states { unknown, free, ship, shot };
	Tile();
	Tile(Tile::states c);
	~Tile();
	states state; 
	void Display();
};


#endif // !TILE_H