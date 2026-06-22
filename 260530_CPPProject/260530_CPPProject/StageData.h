#pragma once
#include <string>
#include<vector>
#include "Position.h"

constexpr int MAP_W = 16; 
constexpr int MAP_H = 15; 
constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

using std::string;
using std::vector;

struct StageSaveData
{
	bool  m_isLock = true;
	bool  m_prevLock = false;
	bool  m_isCleared = false;
	bool  m_prevClear = true;
	float m_bestTime = -1;
}; 

struct MapData
{
	string m_name = "";
	string m_map[MAP_H];
};
