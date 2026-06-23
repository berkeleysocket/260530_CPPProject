#pragma once
#include"Console.h"
#include"GameState.h"
#include"TitleScene.h"
#include"StageScene.h"
#include"InGameScene.h"
#include"StageManager.h"
#include"SoundManager.h"

void Init();
void LoadMaps();
void Update(GameState& state);
void Render(GameState& state);