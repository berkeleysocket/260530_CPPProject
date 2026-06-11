#pragma once
#include <Windows.h>
#include <vector>
#include "Player.h"
#include "Blocks.h"

using std::vector;

//Map
constexpr int MAP_W = 31;
constexpr int MAP_H = 30;

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