#pragma once

#include "Skyrmion/input/MovementEnums.h"

enum CollisionLayer {
	MAP,
	WATER,
	PLAYER,
	TREES,
	INPUT,
};

static const std::map<int, int> displayIndex = {
	{' ', 0},
	{'~', 0},
	{'w', 3},
	{'W', 3},
	{',', 0},
	{'.', 1},
	{'_', 2},
	{'-', 3},
	{'t', 1},
	{'T', 2}
};

static const std::map<int, int> rotationIndex = {
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
	{'t', FULL},
	{'T', FULL}
};

static const std::map<int, int> treetopIndex = {
	{' ', -1},
	{'t', 1},
	{'T', 0}
};

static const std::map<int, int> waterIndex = {
	{' ', -1},
	{'~', 0},
	{'w', 0},
	{'W', 1}
};