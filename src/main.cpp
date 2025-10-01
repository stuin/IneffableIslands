#include "Skyrmion/core/UpdateList.h"
#include "Skyrmion/tiling/TileMap.hpp"
#include "Skyrmion/tiling/RandomNoise.hpp"
#include "Skyrmion/debug/GridEditor.hpp"
#include "Skyrmion/input/Settings.h"
//#include "Skyrmion/tiling/SquareTiles.h"
#include "indexes.h"

void initialize() {
	//Load settings file
	Settings::loadSettings("res/settings.json");

	//Load base tile maps
	GridMaker grid("res/test_island.txt");
	noise::module::Perlin rotateNoise;
	rotateNoise.SetSeed(1);
	rotateNoise.SetFrequency(2.1);

	NoiseIndexer *beachIndexer = new NoiseIndexer(new MapIndexer(&grid, displayIndex, 0), rotationRandomIndex, &rotateNoise, 6);
	//Indexer *beachIndexer = new ConstIndexer(1, 25, 25);
	TileMap beach(TEXTURE_BEACH_TILES, 16, 16, beachIndexer, MAP);
	MapIndexer collisionMap(&grid, collisionIndex, 0, 16, 16);
	UpdateList::addNode(&beach);

	//Add random flowers
	RandomIndexer *flowerIndexer = new RandomIndexer(new MapIndexer(&grid, flowerIndex, -1), flowerRandomIndex);
	TileMap flowers(TEXTURE_FLOWER_TILES, 16, 16, flowerIndexer, FLOWERS);
	flowers.setPosition(0,4);
	flowers.setColor(COLOR_NONE);
	UpdateList::addNode(&flowers);

	//Add animated water texture
	MapIndexer waterMap(&grid, waterIndex, -1);
	AnimatedTileMap water(TEXTURE_WATER_TILES, 16, 16, &waterMap, 4, 0.8, WATER);
	UpdateList::addNode(&water);

	//Add overlapping tree middles
	MapIndexer treetopMap(&grid, treetopIndex, -1);
	TileMap treemid(TEXTURE_TREE_TILES, 16, 16, &treetopMap, TREES, 4);
	treemid.setPosition(0, -4);
	UpdateList::addNode(&treemid);

	//Add overlapping tree tops
	TileMap treetop(TEXTURE_TREE_TILES, 16, 16, &treetopMap, TREES);
	treetop.setPosition(0, -20);
	UpdateList::addNode(&treetop);

	//WIP random generation
	//MapIndexer genMap(&grid, genRemapIndex, -1, 1, 1, true);
	//printUniqueSquares(&genMap);
	//readSquareFile("res/allsquares.txt");

	//Test text
	std::string textS = "Hello World";
	GridMaker textGrid(textS.length(), 1);
	for(sint i = 0; i < textS.length(); i++)
		textGrid.setTileI(i, 0, textS[i]);
	TileMap textMap(TEXTURE_FONT, 17, 29, new MapIndexer(&textGrid, Settings::FONT_SPRITEMAP, -1), TESTTEXT);
	UpdateList::addNode(&textMap);
	UpdateList::hideLayer(TESTTEXT);

	UpdateList::connectServer(Settings::getString("/server/ip"), Settings::getInt("/server/port"));

	//Finish engine setup
	UpdateList::globalLayer(OTHERPLAYERS);
	UpdateList::globalLayer(PLAYER);
	UpdateList::globalLayer(INPUT);
	UpdateList::hideLayer(INPUT);
	UpdateList::globalLayer(TOUCHSCREENINPUT);

	//UpdateList::getLayerData(MAP).shader = SHADER_GRAYSCALE;

	//addGridEditor("Grid Editor", "res/temp_grid.txt", "res/test_island.txt", &grid, FloatRect(0,0,beachBuffered.getSize().x,beachBuffered.getSize().y),
	//	tileNames, TEXTURE_BEACH_TILES, GRIDEDITOR);

	initializePlayer(&collisionMap);
}

std::string TITLE = "Ineffable Islands";
std::string *windowTitle() {
	return &TITLE;
}

skColor backgroundColor() {
	return skColor(0,150,255);
}

std::vector<std::string> &textureFiles() {
	return TEXTURE_FILES;
}
std::vector<std::string> &layerNames() {
	return LAYER_NAMES;
}

void recieveNetworkString(std::string data, int code) {
	std::cout << "NETWORK: Received string " << data << "\n";
}