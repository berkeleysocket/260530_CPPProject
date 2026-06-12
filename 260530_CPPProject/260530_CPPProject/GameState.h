#pragma once
#include <Windows.h>
#include <vector>
#include "Player.h"
#include "Blocks.h"

using std::vector;

//Map
constexpr int MAP_W = 21;
constexpr int MAP_H = 20;
constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

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

struct MapBox
{
    const string gameMap1[MAP_W] = {
    "10000002222222222222",
    "22222000000002222222",
    "22000022222222222222",
    "22222022222222222222",
    "22222000000000022222",
    "22222022222222022222",
    "22222022222222022222",
    "22222022222222022222",
    "22222022222222022222",
    "22222022222222022222",
    "22222022222222000022",
    "22222022222222222222",
    "22222000000000000022",
    "22222022222222220022",
    "22222022222222220220",
    "22222022222222220000",
    "22222022222222222222",
    "22222022222222222022",
    "22222000000000000022",
    "22222222222222222222"
    };
};