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

//map
void LoadMap(GameState& state, const string gameMap[MAP_H]);
void DrawMap(GameState& state);
void DrawBlock(GameState& state, int x, int y);
bool IsEdge(int x, int y);

//player
bool TryDrawPlayer(GameState& state, int x, int y);
bool TryPlayerMove(GameState& state, Position dir);
void HandleBlockInteraction(GameState& state, BlockType block);