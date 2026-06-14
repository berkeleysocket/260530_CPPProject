#pragma once
#include <string>
#include<vector>
#include "Position.h"

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
	vector<string> m_map;
};;
