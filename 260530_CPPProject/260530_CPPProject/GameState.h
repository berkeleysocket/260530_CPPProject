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
	Stage			curStage = Stage::TUTORIAL_1;
	Stage			prevStage = Stage::NONE;
	Block*			map[MAP_H][MAP_W] = {};
	bool			isRunning = true;
    float			delta = 0;    
	Player			player;
    Clone			clone;
    MoveDataRecord  moveDataRecord;
	ULONGLONG		curTime;
    string			actionUIMessage;
    Color			actionUIColor;
	string			descriptionUITitle;
	string			descriptionUIMessage1;
	string			descriptionUIMessage2;
	string			descriptionUIMessage3;
	string			descriptionUIMessage4;
	string			descriptionUIMessage5;
	Color			descriptionUITitleColor;
	Color			descriptionUIMessageColor;
};
    
bool IsEdge(int x, int y);