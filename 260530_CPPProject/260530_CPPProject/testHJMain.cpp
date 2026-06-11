#include"Player.h"
#include"Console.h"
#include"GameState.h"

void Init();
void Update(GameState& state);
void Render(GameState& state);


int main()
{
	GameState state;

	Init();
	while (true)
	{
		Update(state);
		Render(state);
	}
}

void Init()
{
	SetCursorVisible(false);
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
	state.player.Render();
}
