#include "Texture.h"

unordered_map<string, sf::Texture> Textures::textures;

void Textures::LoadTexture(string i) {
	string path = "images/" + i + ".png";
	textures[i].loadFromFile(path);
}

sf::Texture& Textures::Get(string i) {
	if (textures.find(i) == textures.end())
		LoadTexture(i);
	return textures[i];
}

void Textures::Clear() {
	textures.clear();
}