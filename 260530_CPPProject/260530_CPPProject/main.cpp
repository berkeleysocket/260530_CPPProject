//#include"Game.h"
//
//int main()
//{
//	GameState state;
//	ULONGLONG prevTick = 0;
//	state.curScene = Scene::TITLE;
//	Init();
//
//	while (state.isRunning)
//	{
//		ULONGLONG curTick = GetTickCount64();
//		state.delta = (curTick - prevTick);
//
//		Update(state);
//		Render(state);
//	
//		FrameSync(60);
//		prevTick = curTick;
//	}
//
//	SoundManager::GetInst()->Release();
//	StageManager::DestroyInst();
//}