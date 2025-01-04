#pragma once

#include "Skyrmion/input/MovementEnums.h"

enum CollisionLayer {
	MAP,
	PLAYER,
	TREES,
	INPUT,
};

static const std::map<int, int> displayIndex = {
	{' ', 0},
	{'~', 0},
	{',', 1},
	{'.', 2},
	{'t', 2}
};

static const std::map<int, int> collisionIndex = {
	{' ', FULL},
	{'~', FULL},
	{',', EMPTY},
	{'.', EMPTY},
	{'t', FULL}
};

static const std::map<int, int> treetopIndex = {
	{' ', -1},
	{'t', 0}
};