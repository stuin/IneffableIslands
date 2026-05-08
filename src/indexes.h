#pragma once

#include "Skyrmion/input/MovementEnums.h"
#include "Skyrmion/tiling/GridMaker.h"

#define LAYER_FOREACH(E) \
    E(MAP) \
    E(FLOWERS) \
    E(WATER) \
    E(OTHERPLAYERS) \
    E(PLAYER) \
	E(TREES) \
	E(GRIDEDITOR) \
	E(TOUCHSCREENINPUT) \
	E(PLAYERBUFFER) \
	E(TESTTEXT) \

NAMED_ENUM(LAYER);

enum TEXTURES {
	TEXTURE_INVALID,
	TEXTURE_PLAYER,
	TEXTURE_BEACH_TILES,
	TEXTURE_WATER_TILES,
	TEXTURE_TREE_TILES,
	TEXTURE_FLOWER_TILES,
	TEXTURE_JOYSTICK,
	TEXTURE_FONT,
	BUFFER_BEACH_TILES,
	BUFFER_PLAYER,
	SHADER_GRAYSCALE,
	SHADER_PALETTE
};
static std::vector<std::string> TEXTURE_FILES = {
	"#INVALID",
	"res/characters.png",
	"res/beachtiles.png",
	"res/water.png",
	"res/trees.png",
	"res/flowers.png",
	"res/debug/touchscreen_joystick.png",
	"res/DejaVuSansMono.png",
	"#BUFFER_BEACH",
	"#BUFFER_PLAYER",
	"res/shaders/glsl%i/grayscale.fs",
	"res/shaders/glsl%i/palette_switch.fs"
};

static const std::map<int, std::string> tileNames = {
	{'~', "shallow water with sand"},
	{'w', "shallow water with rock"},
	{'W', "deep water with rock"},
	{',', "sand"},
	{'.', "light grass"},
	{'_', "dark grass"},
	{'-', "rock"},
	{'d', "dock/path"},
	{'f', "flower with light grass"},
	{'F', "flower with dark grass"},
	{'t', "palm tree with light grass"},
	{'T', "full tree with dark grass"},
	{'p', "pillar with rock"}
};

static const std::map<int, int> displayIndex = {
	{' ', -1},
	{'~', 0},
	{'w', 3},
	{'W', 3},
	{',', 0},
	{'.', 1},
	{'_', 2},
	{'-', 3},
	{'d', 4},
	{'f', 1},
	{'F', 2},
	{'t', 1},
	{'T', 2},
	{'p', 3}
};

static const std::map<int, int> waterIndex = {
	{' ', -1},
	{'~', 0},
	{'w', 0},
	{'W', 1}
};

static const std::map<int, int> treetopIndex = {
	{' ', -1},
	{'t', 1},
	{'T', 0},
	{'p', 2}
};

static const std::map<int, int> flowerIndex = {
	{' ', -1},
	{'f', 0},
	{'F', 0}
};

static const std::map<int, int> flowerRandomIndex = {
	{0, 3},
	{0, 3}
};

static const std::map<int, int> rotationRandomIndex = {
	{0, 4},
	{1, 4},
	{2, 4},
	{3, 4}
};

static const std::map<int, int> collisionIndex = {
	{' ', FULL},
	{'~', FULL},
	{'w', FULL},
	{'W', FULL},
	{',', EMPTY},
	{'.', EMPTY},
	{'_', EMPTY},
	{'-', EMPTY},
	{'d', EMPTY},
	{'t', FULL},
	{'T', FULL},
	{'p', FULL}
};

static const std::map<int, int> genRemapIndex = {
	{'f', '.'},
	{'F', '_'},
	{'t', '.'},
	{'T', '_'},
	{'p', '-'}
};

static const std::vector<int> STARTING_PALETTES[1] = {
    {   // Original blue
        0, 0, 0,
        116, 223, 245,
        54, 116, 224,
        72, 98, 229,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
    }
};

void initializePlayer(Indexer *collisionMap);