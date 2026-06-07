#pragma once
#include<Windows.h>
#include "Player.h"

//Map
constexpr int MAP_W = 31;
constexpr int MAP_H = 30;
enum class Block 
{
	EMPTY = 0, 
	START = 1, 
	BRICK = 2, 
	LASER = 3
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
	Block	  map[MAP_H][MAP_W] = {};
	Player	  player;
	ULONGLONG curTime;
};