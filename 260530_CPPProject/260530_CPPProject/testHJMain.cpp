#include"Player.h"
#include"Console.h"
#include"GameState.h"
#include "MoveDataRecord.h"

void Init(HJTestState& state);
void Update(HJTestState& state);
void Render(HJTestState& state);

struct HJTestState
{
	Player player;
	Clone* clone;
	MoveDataRecord record;
};


int main()
{
	HJTestState state;

	Init(state);
	while (true)
	{
		Update(state);
		Render(state);
	}
}

void Init(HJTestState& state)
{
	SetCursorVisible(false);
}

void Update(HJTestState& state)
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
	if(GetKeyDown('R'))
	{
		state.clone = new Clone(state.record.GetRecord());
	}
}

void Render(HJTestState& state)
{
	state.player.Render();
}
