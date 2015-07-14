/*
 *  Map.cpp
 *  SimpleRumble
 *
 *  Created by R1M@ster on 15/08/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include "Map.h"

/*
Map::Map()
{
	tileNumber = mapWidth = mapHeight = offsetX = offsetY = 0;
//	bgSprite = NULL;
//	data = NULL;
}
Map::~Map()
{
	// Will that work ???
	//delete tileSet;
//	delete bgSprite;
	delete data;
}

//Tile Map::get Tile(int x, int y, map){}
//Tile Map::getTile(int x, int y)
unsigned int Map::getTile(int x, int y)
{
	return data[x+y*mapWidth];
}

void Map::randomizeMap(int width, int height, const std::string tilesetname)
{
	int i, x, y;
	bgSprite.loadFromFile(tilesetname);
	//tileNumber = bgSprite->getSize().x * bgSprite->getSize().y;
	tileNumber = bgSprite.getSize().x * bgSprite.getSize().y;

	x=y=0;

	for(i=0 ; i < tileNumber ; i++)
	{
		tileSet.at(i).getPosition() = sf::Vector2<float>(x,y);
	}
}
*/
