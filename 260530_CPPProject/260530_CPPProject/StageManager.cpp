#include "StageManager.h"
#include<fstream>
#include<iostream>

StageManager* StageManager::m_inst = nullptr;


void StageManager::SaveStage()
{
	std::ofstream stageFile("saveData\\stages_data.txt", std::ios_base::out);
	if(stageFile.is_open())
	{
		for (const auto& [stage, stageData] : m_mapStageSaveData)
		{
			stageFile <<(int)stage<<","<< stageData->m_isLock << ","
				<< stageData->m_isCleared << "," << stageData->m_bestTime << "\n";
		}
		stageFile.close();
	}
}

void StageManager::LoadStage()
{
	std::ifstream stageFile("saveData\\stages_data.txt");
	string getline;
	string str;
	while (std::getline(stageFile, str))
	{
		Stage stage = (Stage)std::stoi(str.substr(0, str.find(",")));
		bool isLock = str[2] == '1';
		bool isClear = str[4] == '1';
		float bestTime = std::stof(str.substr(6));

		StageSaveData stageData;
		stageData.m_isLock = isLock;
		stageData.m_isCleared = isClear;
		stageData.m_bestTime = bestTime;
		stageData.m_prevClear = !isClear;
		stageData.m_prevLock = !isLock;

		m_mapStageSaveData[stage] = std::make_unique<StageSaveData>(stageData);
	}
}

void StageManager::ChangeStage(Stage stage)
{
	auto iter_stage = m_mapStageSaveData.find(stage);
	auto iter_map = m_mapMapData.find(stage);

	if (iter_map == m_mapMapData.end() && iter_stage == m_mapStageSaveData.end())
		return;
	
	m_curMapData = iter_map->second.get();
	m_curStageData = iter_stage->second.get();
}

void StageManager::RegisterStage(Stage stage, std::unique_ptr<MapData> mapData)
{
	m_mapMapData[stage] = std::move(mapData);
	if(m_mapStageSaveData.size() < m_mapMapData.size())
	{
		m_mapStageSaveData[stage] = std::make_unique<StageSaveData>();
	}
}

