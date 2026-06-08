#pragma once
#include <Windows.h>
#include <map>
#include "Player.h"
#include "Blocks.h"

using std::map;

//Map
constexpr int MAP_W = 31;
constexpr int MAP_H = 30;

enum class BlockType
{
	EMPTY = 0,
	START = 1,
	BRICK = 2,
	LASERCORE = 3,
	LASER_VERTICAL = 4,
	LASER_HORIZONTAL = 5
};

enum class Scene
{
	NONE,
	TITLE,
	INGAME
};

struct GameState
{
	Scene	  prevScene = Scene::NONE;
	Scene	  curScene = Scene::INGAME;
	bool	  isRunning = true;
	BlockType map[MAP_H][MAP_W] = {};
	Block blocks[MAP_H][MAP_W] = {};
	Player	  player;
	ULONGLONG curTime;
};