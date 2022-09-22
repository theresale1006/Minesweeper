#include <cstdlib>
#include <iostream>
#include "Gameboard.h"

int Board::Bombs() {
	int bombs = 0;
	for (int h = 0; h < rows; h++)
		for (int k = 0; k < col; k++)
			if (tiles[h][k].bombExist)
				bombs++;
	return bombs;
}
Board::Board(int rows, int col, int bombs) : bombCount(rows, bombs) {
	this->col = col;
	this->rows = rows;
	this->bombs = bombs;
	CreateTiles("");
}
void Board::CreateTiles(string board) {
	tiles = new Tile * [rows];
	for (int h = 0; h < rows; h++)
		tiles[h] = new Tile[col];
	if (board == "") {
		srand((int)time(0));
		while (bombs > Bombs()) {
			int randk = rand() % rows;
			int randh = rand() % col;
			tiles[randk][randh].bombExist = true;
		}
	}
	else {
		ifstream boardFile("boards/" + board + ".brd");
		string row;
		for (int h = 0; getline(boardFile, row); h++)
			for (unsigned int k = 0; k < row.length(); k++)
				if (row[k] == '1')
					tiles[h][k].bombExist = true;
	}
	for (int h = 0; h < rows; h++)
		for (int k = 0; k < col; k++) {
			tiles[h][k].SetNext(tiles, h, k, rows - 1, col - 1);
			tiles[h][k].SetPos(k * 32.0f, h * 32.0f);
		}
	bombCount.CounterDisplay(to_string(Bombs()));
	bombCount.neg = false;
	bombCount.UpdateText();
}
void Board::Clear() {
	for (int h = 0; h < rows; h++)
		delete[] tiles[h];
	delete[] tiles;
}
void Board::Draw(sf::RenderWindow& w, bool revealBombs) {
	for (int h = 0; h < rows; h++)
		for (int k = 0; k < col; k++)
			tiles[h][k].Draw(w, revealBombs);
	bombCount.Draw(w);
}
bool Board::Reveal(int h, int k) {
	return tiles[h][k].Revealed();
}
void Board::RevealBomb() {
	for (int h = 0; h < rows; h++)
		for (int k = 0; k < col; k++)
			if (tiles[h][k].bombExist)
				tiles[h][k].MineReveal();
}
void Board::Flag(int h, int k) {
	tiles[h][k].Flagged(bombCount);
}
bool Board::Win() {
	bool won = true;
	for (int h = 0; h < rows; h++)
		for (int k = 0; k < col; k++)
			if (!tiles[h][k].bombExist && !tiles[h][k].IsRevealed())
				return false;
	for (int h = 0; h < rows; h++)
		for (int k = 0; k < col; k++)
			if (tiles[h][k].bombExist)
				tiles[h][k].Flagged(bombCount);
	return true;
}
Board::~Board() {
	Clear();
}