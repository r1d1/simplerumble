#ifndef TILE_H
#define TILE_H

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class Tile
{
	private :
		// Coordinates :
		sf::Vector2<float> position;
		// Is tile empty or not
		bool collision;
		// next tile in animation, or -1 if static tile :
		int nextTile;

	public :
		sf::Vector2<float> getPosition();
};

#endif
