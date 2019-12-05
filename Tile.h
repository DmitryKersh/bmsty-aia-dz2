#pragma once
class Tile
{
public:
	Tile();
	Tile(char c);
	~Tile();
	enum states{ unknown, free, ship, shot };
	states state; // '`' unknown; '-' free; 'O' ship; 'X' shot; 
	void Display();
};

