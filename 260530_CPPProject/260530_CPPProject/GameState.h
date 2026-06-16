#pragma once
#include <Windows.h>
#include <vector>

#include "Player.h"
#include "Clone.h"
#include "MoveDataRecord.h"
#include "Enums.h"
#include "Blocks.h"

using std::vector;

constexpr int MAP_W = 15;
constexpr int MAP_H = 15;
constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

struct MapBox
{
    Position m_startPosition = {0,0};
    string m_gameMap[MAP_W] = {
    "...0...........",//1
    ".S.0.....E.....",//2
    "...0...........",//3
    "...0QQQQQQQQQQQ",//4
    "...0...........",//5
    "...0.....b.....",//6
    "...0...........",//7
    "...0..........l",//8
    "...............",//9
    "...............",//10
    "...............",//11
    "...000000000000",//12
    "...0...........",//13
    ".P.0.P.......B.",//14
    "...0..........." //15
    };
};

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
    MapBox mapBox;
};
    
bool IsEdge(int x, int y);