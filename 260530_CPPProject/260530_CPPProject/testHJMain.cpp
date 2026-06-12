#include"Player.h"
#include"Console.h"
#include"GameState.h"
#include "MoveDataRecord.h"

struct HJTestState
{
	Player player;
	Clone* clone = nullptr;
	MoveDataRecord record;
	float delta;
};

void Init(HJTestState& state);
void Update(HJTestState& state);
void Render(HJTestState& state);



int main()
{
	HJTestState state;

	Init(state);
	ULONGLONG prevTick = 0;
	while (true)
	{
		ULONGLONG curTick = GetTickCount64();
		state.delta = (curTick - prevTick);
		Update(state);
		Render(state);
		prevTick = curTick;
		FrameSync(60);
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
		state.record.Record(MoveData{Dir::UP});
	}
	if (GetKeyDown('S'))
	{
		state.player.Move(Dir::DOWN);
		state.record.Record(MoveData{ Dir::DOWN });

	}
	if (GetKeyDown('A'))
	{
		state.player.Move(Dir::LEFT);
		state.record.Record(MoveData{ Dir::LEFT });

	}
	if (GetKeyDown('D'))
	{
		state.player.Move(Dir::RIGHT);
		state.record.Record(MoveData{ Dir::RIGHT });

	}
	if(GetKeyDown('R'))
	{
		state.clone = new Clone(state.record.GetRecord());

	}

	state.player.Tick(state.delta);
	if (state.clone != nullptr)
	{

		state.clone->Tick(state.delta);
	}
}

void Render(HJTestState& state)
{
	state.player.Render();
	if (state.clone)
		state.clone->Render();
}
