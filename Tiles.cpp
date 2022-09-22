#include <iostream>
#include "Tiles.h"
Tile::Tile() {
	bombExist = false;
	reveal = false;
	flagged = false;
	adBombs = 0;
	icon.setTexture(Textures::Get("tile_hidden"));
	flag.setTexture(Textures::Get("flag"));
	bomb.setTexture(Textures::Get("mine"));
}
bool Tile::IsRevealed() {
	return reveal;
}
void Tile::SetNext(Tile**& tiles, int i, int j, int max, int max2) {
	if (i > 0) {
		n[1] = &tiles[i - 1][j];
		if (j > 0)
			n[0] = &tiles[i - 1][j - 1];
		if (j < max2)
			n[2] = &tiles[i - 1][j + 1];
	}
	if (j > 0)
		n[3] = &tiles[i][j - 1];
	if (j < max2)
		n[4] = &tiles[i][j + 1];
	if (i < max) {
		n[6] = &tiles[i + 1][j];
		if (j > 0)
			n[5] = &tiles[i + 1][j - 1];
		if (j < max2)
			n[7] = &tiles[i + 1][j + 1];
	}
	for (Tile* tile : n)
		if (tile != nullptr)
			if (tile->bombExist)
				adBombs++;
	switch (adBombs) {
	case 1: {
		digits.setTexture(Textures::Get("number_1"));
		break;
	}
	case 2: {
		digits.setTexture(Textures::Get("number_2"));
		break;
	}
	case 3: {
		digits.setTexture(Textures::Get("number_3"));
		break;
	}
	case 4: {
		digits.setTexture(Textures::Get("number_4"));
		break;
	}
	case 5: {
		digits.setTexture(Textures::Get("number_5"));
		break;
	}
	case 6: {
		digits.setTexture(Textures::Get("number_6"));
		break;
	}
	case 7: {
		digits.setTexture(Textures::Get("number_7"));
		break;
	}
	case 8: {
		digits.setTexture(Textures::Get("number_8"));
		break;
	}
	}
}
void Tile::SetPos(float x, float y) {
	icon.setPosition(x, y);
	flag.setPosition(x, y);
	digits.setPosition(x, y);
	bomb.setPosition(x, y);
}
void Tile::Draw(sf::RenderWindow& window, bool showMines) {
	window.draw(icon);
	if (flagged)
		window.draw(flag);
	if (bombExist && showMines)
		window.draw(bomb);
	else
		if (reveal && adBombs > 0)
			window.draw(digits);
}
void Tile::Flagged(Counter& count) {
	if (!reveal) {
		if (flagged) {
			flagged = false;
			count.Add();
		}
		else {
			flagged = true;
			count.Minus();
		}
	}
}
bool Tile::Revealed() {

	if (flagged)
		return false;
	reveal = true;
	icon.setTexture(Textures::Get("tile_revealed"));
	if (bombExist)
		return true;
	if (adBombs == 0)
		for (int k = 0; k < 8; k++)
			if (n[k] != nullptr)
				if (!n[k]->reveal && !n[k]->bombExist && !n[k]->flagged)
					n[k]->Revealed();

	return false;
}
void Tile::MineReveal() {
	icon.setTexture(Textures::Get("tile_revealed"));
}