#pragma once
#include"GameState.h"
#include<map>

void InitStage();
void UpdateStage(GameState& state);
void RenderStage(GameState& state);
void SelecteStageAni(const StageSaveData& stageData, const MapData& mapData);
