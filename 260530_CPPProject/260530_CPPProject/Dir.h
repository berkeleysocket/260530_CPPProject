#pragma once
#include "Position.h"

enum class Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

Position DirToPosition(Dir dir);