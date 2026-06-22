#pragma once
#include <Windows.h>
#include <string>
#include <vector>

#include "Player.h"
#include "Clone.h"
#include "MoveDataRecord.h"
#include "Enums.h"
#include "Blocks.h"
#include "StageData.h"

using std::vector;
using std::wstring;

struct Block;

struct MapBox
{
    Position m_startPosition = {0,0};

    string m_gameMap1[MAP_W] = {
    "00000000000000D",//0
    "0..S.w.......N.",//1
    "0....w.........",//2
    "0QQQQ0www000000",//3
    "0....0...C..c..",//4
    "0....0.b.C..c.B",//5
    "0....0...C..c..",//6
    "0qqqq00000WW000",//7
    "0....0...0..0.0",//8
    "0....0.P.0NN0.0",//9
    "0....0...0000 0",//10
    "0QQQQ0...0..P.0",//11
    "0....W...0....0",//12
    "0....W...0..E.0",//13
    "000000000000000" //14
    };

    string m_gameMap2[MAP_W] = {
    "000000000000000",//0
    "0..S.......0.p0",//1
    "0..........0..0",//2
    "0CCCBN.....0..0",//3
    "0..........0u.0",//4
    "0000000....0..0",//5
    "0..P..0....0.u0",//6
    "0WWWWWWU...0QQ0",//7
    "0......w...0..0",//8
    "0......w...0..0",//9
    "0......w...0..0",//10
    "0......w...0..0",//11
    "0000000w.b.0..0",//12
    "0p.q.P0w...0RE0",//13
    "000000000000000" //14
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