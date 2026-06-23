#include"GameState.h"
#include"TitleScene.h"
#include"StageScene.h"
#include"StageManager.h"
#include"SoundManager.h"
#include"Game.h"

void Initt();
void SoundInit();
void LoadMaps();
void Updatee(GameState& state);
void Renderr(GameState& state);

int main()
{
	GameState state;
	Initt();
	ULONGLONG prevTick = 0;
	state.curScene = Scene::TITLE;

	while (state.isRunning)
	{
		ULONGLONG curTick = GetTickCount64();
		state.delta = (curTick - prevTick);

		Updatee(state);
		Renderr(state);
		FrameSync(60);
		prevTick = curTick;
	}
	SoundManager::GetInst()->Release();
	StageManager::DestroyInst();
}


void Initt()
{
	SoundManager::GetInst()->Init();
	SoundInit();
	LoadMaps();
}

void SoundInit()
{
	SoundManager::GetInst()->Init();
	SoundManager::GetInst()->Load("Laser", "Resources/Sounds/Laser.mp3");
	SoundManager::GetInst()->Load("PlayerMovement", "Resources/Sounds/PlayerMovement.mp3");
	SoundManager::GetInst()->Load("ButtonClick", "Resources/Sounds/ButtonClick.mp3");
	SoundManager::GetInst()->Load("SwitchableBrick_OFF", "Resources/Sounds/SwitchableBrick_OFF.mp3");
	SoundManager::GetInst()->Load("SwitchableBrick_ON", "Resources/Sounds/SwitchableBrick_ON.mp3");
	SoundManager::GetInst()->Load("Teleport", "Resources/Sounds/Teleport.mp3");
	SoundManager::GetInst()->Load("CloneMovement", "Resources/Sounds/CloneMovement.mp3");
	SoundManager::GetInst()->Load("PlayerDeath", "Resources/Sounds/PlayerDeath.mp3");
	SoundManager::GetInst()->Load("CloneDeath", "Resources/Sounds/CloneDeath.mp3");
	SoundManager::GetInst()->Load("StageClear", "Resources/Sounds/StageClear.mp3");
}


void Updatee(GameState& state)
{
	SoundManager::GetInst()->Update();

	if (state.curScene == Scene::RESTART)
	{
		state.curScene = state.prevScene;
		state.prevScene = Scene::RESTART;
	}

	bool sceneChanged = state.prevScene != state.curScene;
	state.prevScene = state.curScene;

	switch (state.curScene)
	{
	case Scene::INGAME:
		if (sceneChanged)
			//InitInGame(state);
		Update(state);
			break;
	case Scene::STAGE:
		if (sceneChanged)
			InitStage();
		UpdateStage(state);
		break;
	case Scene::TITLE:
		if (sceneChanged)
			InitTitle();
		UpdateTitle(state);
		break;
	}
 }

void Renderr( GameState& state)
{
	if (state.prevScene != state.curScene)
	{
		system("cls");
		return;
	}
	GotoXY(0, 0);

	switch (state.curScene)
	{
	case Scene::INGAME:
		Render(state);
		break;
	case Scene::STAGE:
		RenderStage(state);
		break;
	case Scene::TITLE:
		RenderTitle(state);
		break;
	}
}