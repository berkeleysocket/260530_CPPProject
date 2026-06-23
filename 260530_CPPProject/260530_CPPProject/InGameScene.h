#pragma once
#include <iostream>
#include <string>
#include <algorithm>

#include "Console.h"
#include "GameState.h"
#include "Position.h"
#include "Dir.h";
#include "StageManager.h"

using std::string;
using std::cout;
using std::endl;

//game
void InitInStage(GameState& state);
void UpdateInGame(GameState& state);
void RenderInGame(GameState& state);
void GenerateMap(GameState& state, const string gameMap[MAP_H]);
void ClearStage(GameState& state);

//render
void DrawMap(GameState& state);
void DrawBlock(GameState& state, int x, int y);
void DrawUI(GameState& state);
bool TryDrawPlayer(GameState& state, int x, int y);
bool TryDrawClone(GameState& state, int x, int y);

//player & clone actions
bool TryPlayerMove(GameState& state, Dir dir);
bool TryCloneMove(GameState& state, Dir dir);
void HandlePlayerBlockInteraction(GameState& state, Block* block, BlockType blockType);
void HandleCloneBlockInteraction(GameState& state, Block* block, BlockType blockType);
void HandlePlayerDead(GameState& state);
void HandleCloneDead(GameState& state);