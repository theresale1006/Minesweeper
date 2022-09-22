#pragma once
#include "Texture.h"
class Counter
{
	string counter;
	sf::Sprite icons[3] = { sf::Sprite(Textures::Get("digits")), sf::Sprite(Textures::Get("digits")), sf::Sprite(Textures::Get("digits")) };
	const sf::Vector2i digits[11] = { sf::Vector2i(0, 0), sf::Vector2i(21, 0), sf::Vector2i(42, 0), sf::Vector2i(63, 0), sf::Vector2i(84, 0), sf::Vector2i(105, 0), sf::Vector2i(126, 0), sf::Vector2i(147, 0),
		sf::Vector2i(168, 0), sf::Vector2i(189, 0), sf::Vector2i(210, 0) };
	const sf::Vector2i size;
	sf::Sprite hy;
public:
	bool neg;
	Counter(int rows, int bombs);
	void CounterDisplay(string rhs);
	void UpdateText();
	void SetRec(char& countDigit, sf::Sprite& sprite);
	void Draw(sf::RenderWindow& window);
	void Add();
	void Minus();
};
