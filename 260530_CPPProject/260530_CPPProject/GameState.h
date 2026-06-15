#pragma once
#include <Windows.h>
#include <vector>
#include "Player.h"
#include "Blocks.h"
#include "Enums.h"
#include "MoveDataRecord.h"
#include "Clone.h"

using std::vector;

//Map
constexpr int MAP_W = 21;
constexpr int MAP_H = 20;
constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

struct GameState
{
	Scene	  prevScene = Scene::NONE;
	Scene	  curScene = Scene::TITLE;
	Menu      curMenu = Menu::START;
	Stage     curStage = Stage::STAGE1;
	Stage     prevStage = Stage::STAGE1;
	bool	  isRunning = true;
    float     delta = 0;    
	BlockType map[MAP_H][MAP_W] = {};
	Block* blocks[MAP_H][MAP_W] = {};
	Player	  player;
    Clone     clone;
    MoveDataRecord moveDataRecord;
	ULONGLONG curTime;
};
    
struct MapBox
{
    Position m_startPosition = {0,0};
	const string m_gameMap[MAP_W] = {
    "06000000000000000007",
    "00008009999900000000",
    "00000000000000000000",
    "00200000030000009000",
    "00000000000000000000",
    "00000000000000000000",
    "00000000000000000000",
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

bool IsEdge(int x, int y);