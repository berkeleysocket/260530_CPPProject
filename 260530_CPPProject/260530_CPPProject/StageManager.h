#pragma once
#include<map>
#include<memory>
#include"Enums.h"
#include"Defines.h"
#include"StageData.h"

class StageManager
{
private:
	StageManager() = default;
public:
	static StageManager* GetInst()
	{
		if(nullptr== m_inst)	
			m_inst = new StageManager();
		return m_inst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_inst);
	}
public:
	void SaveStage();
	void LoadStage();
	void ChangeStage(Stage stage);
	void RegisterStage(Stage stage, std::unique_ptr<MapData> mapData);
	const MapData& GetCurMapData() const
	{
		return *m_curMapData;
	}
	StageSaveData& GetCurStageSaveData()
	{
		return *m_curStageData;
	}

	void Clear(Stage curStage, ULONGLONG playTime, int deadCount);
	const FinalData& GetFinalData(float totalPlayTime);
private:
	static StageManager* m_inst;
	std::map<int, std::unique_ptr<StageSaveData>> m_mapStageSaveData;
	std::map<Stage, std::unique_ptr< MapData>> m_mapMapData;
	StageSaveData* m_curStageData;
	MapData* m_curMapData;
};

