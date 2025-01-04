//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Skyrmion/tiling/TileMap.hpp"
#include "indexes.h"
#include "Player.hpp"

int main() {
	//Load settings file
	Settings::loadSettings("res/settings.json");

	//Load tilemap textures
	sf::Texture beachTexture;
	sf::Texture treemidTexture;
	sf::Texture treetopTexture;
	UpdateList::loadTexture(&beachTexture, "res/beachtiles.png");
	UpdateList::loadTexture(&treemidTexture, "res/treemid.png");
	UpdateList::loadTexture(&treetopTexture, "res/treetop.png");

	//Load base tile maps
	GridMaker grid("res/test_island.txt");
	TileMap beach(&beachTexture, 16, 16, new MapIndexer(&grid, displayIndex, 0), MAP);
	MapIndexer collisionMap(&grid, collisionIndex, 0, 16, 16);
	MapIndexer treetopMap(&grid, treetopIndex, -1);
	UpdateList::addNode(&beach);

	//Add overlapping tree middles
	TileMap treemid(&treemidTexture, 16, 16, &treetopMap, TREES);
	treemid.setPosition(0, -4);
	UpdateList::addNode(&treemid);

	//Add overlapping tree tops
	TileMap treetop(&treetopTexture, 16, 16, &treetopMap, TREES);
	treetop.setPosition(0, -20);
	UpdateList::addNode(&treetop);

	//Load node textures
	sf::Texture playerTexture;
	sf::Texture treasureTexture;
	UpdateList::loadTexture(&playerTexture, "res/player.png");

	//Upper area player
	Player player(&collisionMap);
	player.setPosition(sf::Vector2f(7*16, 6*16));
	player.setTexture(playerTexture);
	UpdateList::addNode(&player);

	//Finish engine setup
	UpdateList::staticLayer(MAP);
	UpdateList::staticLayer(TREES);
	UpdateList::staticLayer(INPUT);
	UpdateList::setCamera(&player, sf::Vector2f(450, 250));

	UpdateList::startEngine("IneffableIslands");
	return 0;
}