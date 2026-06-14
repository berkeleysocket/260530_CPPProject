#pragma once

#include "Game.h"

int main()
{
	MapBox map;
	GameState state;

	Init(state);
	InitInGame(state);
	LoadMap(state, map.m_gameMap);
	ULONGLONG prevTick = 0;

	while (true)
	{
		ULONGLONG curTick = GetTickCount64();
		state.delta = (curTick - prevTick);
		Update(state);
		Render(state);
		prevTick = curTick;
	}

	return 0;
}