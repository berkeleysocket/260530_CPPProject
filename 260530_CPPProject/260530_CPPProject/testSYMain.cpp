#pragma once
#include "GameState.h"
#include "InGameScene.h"

void Init(GameState& state);
void Update(GameState& state);
void Render(GameState& state);

void Init(GameState& state)
{
	SetConsoleSize(WIDTH, HEIGHT);
	SetConsoleWindowStyle(true);
	SetConsoleMouseInputDisabled();
	SetCursorVisible(false);

	state = GameState{};
}

void Update(GameState& state)
{
	UpdateInput();
	if (GetKeyDown('W'))
	{
		state.player.Move(Dir::UP);
	}
	if (GetKeyDown('S'))
	{
		state.player.Move(Dir::DOWN);
	}
	if (GetKeyDown('A'))
	{
		state.player.Move(Dir::LEFT);
	}
	if (GetKeyDown('D'))
	{
		state.player.Move(Dir::RIGHT);
	}
}

void Render(GameState& state)
{
	GotoXY(0, 0);
	DrawMap(state);
}

int main()
{
	MapBox maps;
	GameState state;
	Init(state);
	LoadMap(state, maps.gameMap1);
	SetConsoleSize(MAP_W * 3, MAP_H * 2);

	while (true)
	{
		Update(state);
		Render(state);
	}

	return 0;
}