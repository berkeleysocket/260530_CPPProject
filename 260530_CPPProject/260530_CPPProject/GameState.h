#pragma once
#include <Windows.h>
#include <string>
#include <vector>

#include "Player.h"
#include "Clone.h"
#include "MoveDataRecord.h"
#include "Enums.h"
#include "StageData.h"

using std::vector;
using std::wstring;

class Block;
enum class BlockType;

struct GameState
{ 
	Scene			prevScene = Scene::NONE;
	Scene			curScene = Scene::TITLE;
	Menu			curMenu = Menu::START;
	Stage			curStage = Stage::STAGE1;
	Stage			prevStage = Stage::NONE;
	Block*			map[MAP_H][MAP_W] = {};
	bool			isRunning = true;
    float			delta = 0;    
	Player			player;
    Clone			clone;
    MoveDataRecord  moveDataRecord;
	ULONGLONG		curTime;
    string			uiMessage1;
    Color			uiColor1;
};
    
bool IsEdge(int x, int y);