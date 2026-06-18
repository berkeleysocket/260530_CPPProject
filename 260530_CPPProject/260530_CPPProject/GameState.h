#pragma once
#include <Windows.h>
#include <vector>
#include "Player.h"
#include "Blocks.h"
#include "Enums.h"
#include "MoveDataRecord.h"
#include "Clone.h"
#include<vector>

using std::vector;


//Map
constexpr int MAP_W = 21; //맵 다합치면 지우기
constexpr int MAP_H = 20; //맵 다 합치면 지우기
constexpr int WIDTH = 160; 
constexpr int HEIGHT = 45; 

struct MapBox
{
    Position m_startPosition = {0,0};
    string m_gameMap[MAP_W] = {
    "....................",//1
    "......P.p.....w.....",//2
    "...bB....S....W.....",//3
    "....................",//4
    "....................",//5
    "....W.........L.....",//6
    "....................",//7
    "...EEE..............",//8
    "...eee..............",//9
    "....................",//10
    "..............0.....",//11
    "....................",//12
    "....................",//13
    "......P.p...........",//14
    "....................",//15
    "....................",//16
    "....................",//17
    "....................",//18
    "....................",//19
    "....................",//20
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
	BlockType map[MAP_H][MAP_W] = {};//나중에 지워야함
	Block* blocks[MAP_H][MAP_W] = {}; //얘두 맵 다 합치면 지워야함
    std::vector<vector<BlockType>> vMap;
    std::vector<vector<Block*>> vBlocks;
	Player	  player;
    Clone     clone;
    MoveDataRecord moveDataRecord;
	ULONGLONG curTime;
    MapBox mapBox;
};
    
bool IsEdge(int x, int y);