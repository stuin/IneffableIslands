#pragma once

#include "Skyrmion/input/MovementEnums.h"

enum CollisionLayer {
	MAP,
	WATER,
	FLOWERS,
	PLAYER,
	TREES,
	NOISEMAP,
	INPUT,
};

/*
~ = shallow water with sand
w = shallow water with rock
W = deep water with rock
, = sand
. = light grass
_ = dark grass
- = rock
d = dock/path
f = flower with light grass
F = flower with dark grass
t = palm tree with light grass
T = full tree with dark grass
p = pillar with rock
*/

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