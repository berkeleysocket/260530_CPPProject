#pragma once
#include <iostream>
#include <string>
#include <algorithm>

#include "Console.h"
#include "GameState.h"
#include "Position.h"
#include "Dir.h";

using std::string;
using std::cout;
using std::endl;


//Init
void InitInGame(GameState& state);

//player
void HandlePlayerDead(GameState& state);
void HandleCloneDead(GameState& state);
bool TryDrawPlayer(GameState& state, int x, int y);
bool TryDrawClone(GameState& state, int x, int y);
bool TryPlayerMove(GameState& state, Dir dir);
bool TryCloneMove(GameState& state, Dir dir);
bool TryCloneMove(GameState& state, Dir dir);
void HandlePlayerBlockInteraction(GameState& state, BlockType block);
void HandleCloneBlockInteraction(GameState& state, BlockType block);

//map
void LoadMap(GameState& state, const vector<string>& gameMap);
void LoadMap(GameState& state, const string gameMap[MAP_H]);
void DrawMap(GameState& state);
void DrawBlock(GameState& state, int x, int y);
bool IsEdge(int x, int y);
