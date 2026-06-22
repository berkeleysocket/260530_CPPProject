#pragma once

#include "Game.h"

int main()
{
	MapBox map;
	GameState state;

	Init(state);
	InitInGame(state);
	ULONGLONG prevTick = 0;

	while (true)
	{
		SoundManager::GetInst()->Update();
		ULONGLONG curTick = GetTickCount64();
		state.delta = (curTick - prevTick);
		Update(state);
		Render(state);
		prevTick = curTick;
	}
	SoundManager::GetInst()->Release();

	return 0;
}