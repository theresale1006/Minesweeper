#pragma once
#include "Counter.h"
class Tile
{
	bool reveal;
	bool flagged;
	short adBombs;
	Tile* n[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	sf::Sprite icon;
	sf::Sprite flag;
	sf::Sprite digits;
	sf::Sprite bomb;
public:
	bool bombExist;
	Tile();
	bool IsRevealed();
	void SetNext(Tile**& tiles, int i, int j, int iMax, int jMax);
	void SetPos(float x, float y);
	void Draw(sf::RenderWindow& window, bool showMines);
	void Flagged(Counter& mineCounter);
	bool Revealed();
	void MineReveal();
};