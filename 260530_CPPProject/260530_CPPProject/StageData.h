#pragma once
#include <string>
#include<vector>
using std::string;
using std::vector;

struct StageSaveData
{
	bool  m_isLock = true;
	bool  m_isCleared = false;
	float m_bestTime = -1;
}; 

struct MapData
{
	string m_name = "";
	vector<string> m_map;
};;
