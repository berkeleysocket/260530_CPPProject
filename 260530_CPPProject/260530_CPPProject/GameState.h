#pragma once
#include <Windows.h>
#include <vector>

#include "Player.h"
#include "Clone.h"
#include "MoveDataRecord.h"
#include "Enums.h"
#include "Blocks.h"

using std::vector;

struct Block;

constexpr int MAP_W = 15;
constexpr int MAP_H = 15;
constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

struct MapBox
{
    Position m_startPosition = {0,0};
    string m_gameMap[MAP_W] = {
    "........0Q.....",//0
    ".S.B....0Q.....",//1
    "........0Q.....",//2
    "........PQ.....",//3
    "........0Q.....",//4
    "........0Q.....",//5
    "........0QQQQQQ",//6
    "qqqqqqqU.......",//7
    "...............",//8
    "...............",//9
    "...........P...",//10
    "...b...........",//11
    "...............",//12
    "...............",//13
    "..............." //14
    };
};

struct GameState
{ 
	Scene	  prevScene = Scene::NONE;
	Scene	  curScene = Scene::TITLE;
	Menu      curMenu = Menu::START;
	Stage     curStage = Stage::STAGE1;
	Stage     prevStage = Stage::STAGE1;
	BlockType map[MAP_H][MAP_W] = {};
	Block* blocks[MAP_H][MAP_W] = {};
	bool	  isRunning = true;
    float     delta = 0;    
	Player	  player;
    Clone     clone;
    MoveDataRecord moveDataRecord;
	ULONGLONG curTime;
    MapBox mapBox;
    string uiMessage1;
    Color uiColor1;
};
    
bool IsEdge(int x, int y);