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
	Dir dir;
	UpdateInput();
	if (GetKeyDown('W'))
	{
		dir = Dir::UP;
		if (TryPlayerMove(state, dir))
		{
			state.player.Move(dir);
		}
	}
	if (GetKeyDown('S'))
	{
		dir = Dir::DOWN;
		if (TryPlayerMove(state, dir))
		{
			state.player.Move(dir);
		}
	}
	if (GetKeyDown('A'))
	{
		dir = Dir::LEFT;
		if (TryPlayerMove(state, dir))
		{
			state.player.Move(dir);
		}
	}
	if (GetKeyDown('D'))
	{
		dir = Dir::RIGHT;
		if (TryPlayerMove(state, dir))
		{
			state.player.Move(dir);
		}
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