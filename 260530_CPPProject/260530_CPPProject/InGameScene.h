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
void InitInGame(GameState& state);
void ClearStage(GameState& state);
void LoadMap(GameState& state, const vector<string>& gameMap);
void LoadMap(GameState& state, const string gameMap[MAP_H]);

//render
void DrawMap(GameState& state);
void DrawBlock(GameState& state, int x, int y);
bool TryDrawPlayer(GameState& state, int x, int y);
bool TryDrawClone(GameState& state, int x, int y);

//player & clone actions
bool TryPlayerMove(GameState& state, Dir dir);
bool TryCloneMove(GameState& state, Dir dir);
void HandlePlayerBlockInteraction(GameState& state, Block* block, BlockType blockType);
void HandleCloneBlockInteraction(GameState& state, Block* block, BlockType blockType);
void HandlePlayerDead(GameState& state);
void HandleCloneDead(GameState& state);