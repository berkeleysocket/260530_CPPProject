#pragma once
#include "Position.h"

enum class Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

Position DirToCursorPosition(Dir dir);
Position DirToMapPosition(Dir dir);