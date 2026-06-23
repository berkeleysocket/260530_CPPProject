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

void LoadMaps()
{
	StageManager::GetInst()->LoadStage();
	MapData mapData
	{
		"Test Map1"
		,
	{ //map
 "000000000000000",//0
	"0..S.w.......N.",//1
	"0....w.........",//2
	"0QQQQ0www000000",//3
	"0....0...C..c..",//4
	"0....0.b.C..c.B",//5
	"0....0...C..c..",//6
	"0qqqq00000WW000",//7
	"0....0...0..0.0",//8
	"0....0.P.0NN0.0",//9
	"0....0...0000 0",//10
	"0QQQQ0...0..P.0",//11
	"0....W...0....0",//12
	"0....W...0..E.0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE1, std::make_unique<MapData>(mapData));

	MapData mapData2
	{
		"Test Map2"
		,
	{
	"000000000000000",//0
	"0..S.......0.p0",//1
	"0..........0..0",//2
	"0...B......0..0",//3
	"0..........0u.0",//4
	"0000000....0..0",//5
	"0..P..0....0.u0",//6
	"0WWWWWWU...0QQ0",//7
	"0......w...0..0",//8
	"0......w...0..0",//9
	"0......w...0..0",//10
	"0......w...0..0",//11
	"0000000w.b.0..0",//12
	"0p.q.P0w...0RE0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE2, std::make_unique<MapData>(mapData2));

	StageManager::GetInst()->ChangeStage(Stage::STAGE1);
	StageSaveData& sd = StageManager::GetInst()->GetCurStageSaveData();
	sd.m_isLock = false;

	StageManager::GetInst()->SaveStage();


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
			InitInGame(state);
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