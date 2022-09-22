#pragma once
#include <fstream>
#include "Tiles.h"
class Board
{
	int rows;
	int col;
	int bombs;
	Tile** tiles;
	int Bombs();
	Counter bombCount;
public:
	Board(int rows, int columns, int mines);
	void CreateTiles(string board);
	void Clear();
	void Draw(sf::RenderWindow& window, bool showMines);
	bool Reveal(int i, int j);
	void RevealBomb();
	void Flag(int i, int j);
	bool Win();
	~Board();
};
