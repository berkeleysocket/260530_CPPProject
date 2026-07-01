#define NOMINMAX
#include "StageManager.h"
#include<fstream>
#include<iostream>

StageManager* StageManager::m_inst = nullptr;


void StageManager::SaveStage()
{
	std::ofstream stageFile("saveData\\stages_data.txt", std::ios_base::out);
	if(stageFile.is_open())
	{
		for (const auto& [id, stageData] : m_mapStageSaveData)
		{
			stageFile << id <<","<<stageData->m_stageNum<<"," << stageData->m_isLock << ","
				<< stageData->m_isCleared << "," << stageData->m_bestTime <<","<<stageData->m_deadCnt << "\n";
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
		if (str.empty())
			continue;

		size_t pos1 = str.find(',');
		size_t pos2 = str.find(',', pos1 + 1);
		size_t pos3 = str.find(',', pos2 + 1);
		size_t pos4 = str.find(',', pos3 + 1);
		size_t pos5 = str.find(',', pos4 + 1);

		int id = std::stoi(str.substr(0, pos1));
		int stageNum = std::stoi(str.substr(pos1 + 1, pos2 - pos1 - 1));
		bool isLock = std::stoi(str.substr(pos2 + 1, pos3 - pos2 - 1));
		bool isClear = std::stoi(str.substr(pos3 + 1, pos4 - pos3 - 1));
		float bestTime = std::stof(str.substr(pos4 + 1, pos5 - pos4 - 1));
		int deadCnt = std::stoi(str.substr(pos5 + 1));

		StageSaveData stageData;
		stageData.m_id = id;
		stageData.m_stageNum = stageNum;
		stageData.m_isLock = isLock;
		stageData.m_isCleared = isClear;
		stageData.m_bestTime = bestTime;
		stageData.m_prevClear = !isClear;
		stageData.m_prevLock = !isLock;
		stageData.m_deadCnt = deadCnt;

		m_mapStageSaveData[id] = std::make_unique<StageSaveData>(stageData);
	}
}

void StageManager::ChangeStage(Stage stage)
{
	auto iter_map = m_mapMapData.find(stage);
	auto iter_stage = m_mapStageSaveData.find((*iter_map->second.get()).m_id);

	if (iter_map == m_mapMapData.end() && iter_stage == m_mapStageSaveData.end())
		return;
	
	m_curMapData = iter_map->second.get();
	m_curStageData = iter_stage->second.get();
}

void StageManager::RegisterStage(Stage stage, std::unique_ptr<MapData> mapData)
{
	if (m_mapStageSaveData.find(mapData->m_id) == m_mapStageSaveData.end())
	{
		StageSaveData stageData;
		stageData.m_stageNum = (int)stage;
		int id = mapData->m_id;
		m_mapStageSaveData[id] = std::make_unique<StageSaveData>(stageData);

	}
	else
		m_mapStageSaveData[mapData->m_id]->m_stageNum = (int)stage;

	m_mapMapData[stage] = std::move(mapData);
}

void StageManager::Clear(Stage curStage)
{
	m_curStageData->m_isCleared = true;
	Stage nextStage = (Stage)std::min((int)curStage + 1, (int)Stage::ENDSTAGE);

	auto iter_map = m_mapMapData.find(nextStage);
	auto iter_stage = m_mapStageSaveData.find((*iter_map->second.get()).m_id);
	(*iter_stage->second.get()).m_isLock = false;

	SaveStage();
}

const FinalData& StageManager::GetFinalData(float totalPlayTime)
{

	FinalData finalData;

	for (const auto& [id, stageData] : m_mapStageSaveData)
	{
		finalData.totalDeadCount += stageData->m_deadCnt;
		finalData.totalPlayTime = totalPlayTime;
		if(finalData.maxDeadCount < stageData->m_deadCnt)
		{
			finalData.maxDeadCount = stageData->m_deadCnt;
			finalData.maxDeadStage = stageData->m_stageNum;
		}
		if (finalData.minPlayTime > stageData->m_bestTime)
		{
			finalData.minPlayTime = stageData->m_bestTime;
			finalData.minTimeStage = stageData->m_stageNum;
		}
	}

	return finalData;
}

