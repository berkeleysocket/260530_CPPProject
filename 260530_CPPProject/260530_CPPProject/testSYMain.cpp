#pragma once

#include "Game.h"

int main()
{
	MapBox maps;
	GameState state;

	Init(state);
	InitInGame(state);
	LoadMap(state, maps.gameMap1);

	while (true)
	{
		Update(state);
		Render(state);
	}

	return 0;
}