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
			
			MoveData moveData;
			moveData.dir = dir;
			state.moveDataRecord.Record(moveData);
		}
	}
	if (GetKeyDown('S'))
	{
		dir = Dir::DOWN;
		if (TryPlayerMove(state, dir))
		{
			state.player.Move(dir);

			MoveData moveData;
			moveData.dir = dir;
			state.moveDataRecord.Record(moveData);
		}
	}
	if (GetKeyDown('A'))
	{
		dir = Dir::LEFT;
		if (TryPlayerMove(state, dir))
		{
			state.player.Move(dir);

			MoveData moveData;
			moveData.dir = dir;
			state.moveDataRecord.Record(moveData);
		}
	}
	if (GetKeyDown('D'))
	{
		dir = Dir::RIGHT;
		if (TryPlayerMove(state, dir))
		{
			state.player.Move(dir);

			MoveData moveData;
			moveData.dir = dir;
			state.moveDataRecord.Record(moveData);
		}
	}

	state.clone.Tick(state.delta);
}

void Render(GameState& state)
{
	GotoXY(0, 0);
    DrawMap(state);
}