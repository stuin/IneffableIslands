//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Skyrmion/debug/DebugTools.hpp"

#include "Skyrmion/tiling/TileMap.hpp"
#include "Skyrmion/tiling/RandomNoise.hpp"
#include "Skyrmion/tiling/SquareTiles.h"
#include "indexes.h"
#include "Player.hpp"

int main() {
	//Load settings file
	Settings::loadSettings("res/settings.json");

	//Load tilemap textures
	sf::Texture beachTexture;
	sf::Texture waterTexture;
	sf::Texture treeTexture;
	sf::Texture flowerTexture;
	UpdateList::loadTexture(&beachTexture, "res/beachtiles.png");
	UpdateList::loadTexture(&waterTexture, "res/water.png");
	UpdateList::loadTexture(&treeTexture, "res/trees.png");
	UpdateList::loadTexture(&flowerTexture, "res/flowers.png");

	//Load base tile maps
	GridMaker grid("res/test_island.txt");
	noise::module::Perlin rotateNoise;
	rotateNoise.SetSeed(1);
	rotateNoise.SetFrequency(2.1);
	NoiseIndexer *beachIndexer = new NoiseIndexer(new MapIndexer(&grid, displayIndex, 0), rotationRandomIndex, &rotateNoise, 6);
	TileMap beach(&beachTexture, 16, 16, beachIndexer, MAP);
	MapIndexer collisionMap(&grid, collisionIndex, 0, 16, 16);
	UpdateList::addNode(&beach);

	//Add animated water texture
	MapIndexer waterMap(&grid, waterIndex, -1);
	AnimatedTileMap water(&waterTexture, 16, 16, &waterMap, 4, 0.8, WATER);
	UpdateList::addNode(&water);

	//Add overlapping tree middles
	MapIndexer treetopMap(&grid, treetopIndex, -1);
	TileMap treemid(&treeTexture, 16, 16, &treetopMap, TREES, 4);
	treemid.setPosition(0, -4);
	UpdateList::addNode(&treemid);

	//Add overlapping tree tops
	TileMap treetop(&treeTexture, 16, 16, &treetopMap, TREES);
	treetop.setPosition(0, -20);
	UpdateList::addNode(&treetop);

	//Add random flowers
	RandomIndexer *flowerIndexer = new RandomIndexer(new MapIndexer(&grid, flowerIndex, -1), flowerRandomIndex);
	TileMap flowers(&flowerTexture, 16, 16, flowerIndexer, FLOWERS);
	flowers.setPosition(0,-4);
	UpdateList::addNode(&flowers);

	//WIP random generation
	MapIndexer genMap(&grid, genRemapIndex, -1, 1, 1, true);
	//printUniqueSquares(&genMap);
	//readSquareFile("res/allsquares.txt");

	//libnoise test map
	noise::module::Perlin testNoise;
	testNoise.SetSeed(time(0));
	testNoise.SetFrequency(2.1);
	//testNoise.SetPersistence(1.0);
	//testNoise.SetLacunarity(3.5);
	//testNoise.SetOctaveCount(12);
	//noise::module::Checkerboard checkerNoise;
	//noise::module::Add addNoise;
	//addNoise.SetSourceModule(0, testNoise);
	//addNoise.SetSourceModule(1, checkerNoise);

	int testSize = 20;
	int testDivisions = 4;
	NoiseIndexer *randomIndexer = new NoiseIndexer(new ConstIndexer(0, testSize, testSize),
		new ConstIndexer(testDivisions, testSize, testSize), &testNoise, 100 / testDivisions);
	//RandomIndexer *randomIndexer = new RandomIndexer(new ConstIndexer(0, testSize, testSize),
	//	new ConstIndexer(testDivisions, testSize, testSize), 100 / testDivisions);

	sf::Texture debugMapTexture;
	UpdateList::loadTexture(&debugMapTexture, "src/Skyrmion/res/heatmapG.png");
	TileMap debugNoise(&debugMapTexture, 1, 1, randomIndexer, NOISEMAP);
	debugNoise.setScale(5,5);
	UpdateList::addNode(&debugNoise);
	UpdateList::hideLayer(NOISEMAP);

	int counters[testDivisions] = {0};
	randomIndexer->mapGrid([&counters, testDivisions](int c, sf::Vector2f pos) {
		counters[c/ (100/testDivisions)]++;
	});
	int sum = 0;
	for(int c : counters) {
		std::cout << c << "\n";
		sum += c;
	}
	std::cout << sum << "\n";

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

	DEBUGTOOLS;

	UpdateList::startEngine("IneffableIslands");
	return 0;
}