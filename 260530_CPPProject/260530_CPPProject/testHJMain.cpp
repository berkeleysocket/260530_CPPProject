//#include"Player.h"
//#include"Console.h"
//
//
//struct GameState
//{
//	Player player;
//};
//
//void Init();
//void Update(GameState& state, ULONGLONG curTick);
//void Render(GameState& state);
//
//
//int main()
//{
//	GameState state;
//
//	Init();
//	while (true)
//	{
//		ULONGLONG curTick = GetTickCount64();
//		Update(state,curTick);
//		Render(state);
//	}
//}
//
//void Init()
//{
//	SetCursorVisible(false);
//}
//
//void Update(GameState& state, ULONGLONG curTick)
//{
//	UpdateInput();
//	if (GetKeyDown('W'))
//	{
//		state.player.Move(Dir::UP);
//	}
//	if (GetKeyDown('S'))
//	{
//		state.player.Move(Dir::DOWN);
//	}
//	if (GetKeyDown('A'))
//	{
//		state.player.Move(Dir::LEFT);
//	}
//	if (GetKeyDown('D'))
//	{
//		state.player.Move(Dir::RIGHT);
//	}
//	if (GetKeyDown('X'))
//	{
//		state.player.TestGenerateClone();
//	}
//
//	state.player.Tick(curTick);
//}
//
//void Render(GameState& state)
//{
//	state.player.Render();
//}
