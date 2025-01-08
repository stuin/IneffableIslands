//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Skyrmion/tiling/TileMap.hpp"
#include "Skyrmion/tiling/TileFilters.hpp"
#include "indexes.h"
#include "Player.hpp"

#include "Skyrmion/debug/DebugLayers.hpp"

int main() {
	//Load settings file
	Settings::loadSettings("res/settings.json");

	//Load tilemap textures
	sf::Texture beachTexture;
	sf::Texture treeTexture;
	sf::Texture waterTexture;
	UpdateList::loadTexture(&beachTexture, "res/beachtiles.png");
	UpdateList::loadTexture(&treeTexture, "res/trees.png");
	UpdateList::loadTexture(&waterTexture, "res/water.png");

	//Load base tile maps
	GridMaker grid("res/test_island.txt");
	Indexer *beachIndexer = new RandomIndexer(new MapIndexer(&grid, displayIndex, 0), rotationIndex, 0, 4);
	TileMap beach(&beachTexture, 16, 16, beachIndexer, MAP);
	MapIndexer collisionMap(&grid, collisionIndex, 0, 16, 16);
	MapIndexer treetopMap(&grid, treetopIndex, -1);
	MapIndexer waterMap(&grid, waterIndex, -1);
	UpdateList::addNode(&beach);

	//printUniqueSquares(&grid);

	//Add overlapping tree middles
	TileMap treemid(&treeTexture, 16, 16, &treetopMap, TREES, 2);
	treemid.setPosition(0, -4);
	UpdateList::addNode(&treemid);

	//Add overlapping tree tops
	TileMap treetop(&treeTexture, 16, 16, &treetopMap, TREES);
	treetop.setPosition(0, -20);
	UpdateList::addNode(&treetop);

	//Add animated water texture
	AnimatedTileMap water(&waterTexture, 16, 16, &waterMap, 4, 0.8, WATER);
	UpdateList::addNode(&water);

	//Load node textures
	sf::Texture playerTexture;
	UpdateList::loadTexture(&playerTexture, "res/player.png");

	//Player
	Player player(&collisionMap);
	player.setPosition(sf::Vector2f(16*16, 16*16));
	player.setTexture(playerTexture);
	UpdateList::addNode(&player);

	//Finish engine setup
	UpdateList::staticLayer(MAP);
	UpdateList::staticLayer(PLAYER);
	UpdateList::staticLayer(TREES);
	UpdateList::staticLayer(INPUT);
	UpdateList::setCamera(&player, sf::Vector2f(450, 250));

	DEBUGLAYERS;

	UpdateList::startEngine("IneffableIslands");
	return 0;
}