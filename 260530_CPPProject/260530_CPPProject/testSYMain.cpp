#pragma once

#include "Game.h"

int main()
{
	MapBox map;
	GameState state;

	Init(state);
	InitInGame(state);
	LoadMap(state, map.m_gameMap);

	while (true)
	{
		Update(state);
		Render(state);
	}

	return 0;
}