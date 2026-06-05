#pragma once
#include <string>
#include "GameState.h"
#include "Position.h";

using std::string;

void LoadMap(GameState& state, const string gameMap[MAP_H]);
bool TryPlayerMove(GameState& state);