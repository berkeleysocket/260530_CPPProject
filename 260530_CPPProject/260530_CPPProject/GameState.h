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

struct MapBox
{
    Position m_startPosition = {0,0};
    string m_gameMap[MAP_W] = {
    "00000000000000000000",//1
    "0..................0",//2
    "0...B....S....W....0",//3
    "0..................0",//4
    "0..................0",//5
    "0...W.........L....0",//6
    "0..................0",//7
    "0..................0",//8
    "0..................0",//9
    "0..................0",//10
    "0.............0....0",//11
    "0..................0",//12
    "0..................0",//13
    "0..................0",//14
    "0..................0",//15
    "0..................0",//16
    "0..................0",//17
    "0..................0",//18
    "0..................0",//19
    "00000000000000000000",//20
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