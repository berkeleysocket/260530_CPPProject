#include "Game.h"

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

	state.clone.Tick(state, state.delta);
}

void Render(GameState& state)
{
	GotoXY(0, 0);
    DrawMap(state);
	GotoXY(0, 18);
	DrawUI(state);
}