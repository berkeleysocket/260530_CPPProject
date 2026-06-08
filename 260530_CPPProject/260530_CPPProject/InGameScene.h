#pragma once
#include <iostream>
#include <string>
#include <algorithm>

#include "Console.h"
#include "GameState.h"
#include "Position.h"

using std::string;
using std::cout;
using std::endl;

//map
void LoadMap(GameState& state, const string gameMap[MAP_H]);
void DrawMap(const GameState& state);
bool IsEdge(int x, int y);

//player
bool TryDrawPlayer(const GameState& state, int x, int y);
bool TryPlayerMove(GameState& state, Position dir);
void HandleBlockInteraction(GameState& state, BlockType block);