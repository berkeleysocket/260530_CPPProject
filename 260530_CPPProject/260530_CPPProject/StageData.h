#pragma once
#include <string>
#include<vector>
#include "Position.h"
#include<Windows.h>

constexpr int MAP_W = 16; 
constexpr int MAP_H = 15; 
constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

using std::string;
using std::vector;

struct StageSaveData
{
	int m_id;
	int m_stageNum = 0;
	bool  m_isLock = true;
	bool  m_prevLock = false;
	bool  m_isCleared = false;
	bool  m_prevClear = true;
	float m_bestTime = -1;
	int m_deadCnt = 0;
}; 

struct MapData
{
	int m_id;
	string m_name = "";
	string m_map[MAP_H];
};

struct FinalData
{
	int totalDeadCount = 0;
	ULONGLONG totalPlayTime = 0;
	int maxDeadStage = 0;
	int maxDeadCount = 0;
	int minTimeStage = 0;
	ULONGLONG minPlayTime = 0;
};
