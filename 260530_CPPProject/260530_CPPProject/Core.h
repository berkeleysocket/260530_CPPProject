#pragma once
#include"GameState.h"

class Core
{
public:
	void CoreInit();
	void Update(GameState& state);
	void Render(const GameState& state);
};

