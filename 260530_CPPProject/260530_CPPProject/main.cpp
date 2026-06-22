#include"Player.h"
#include"Console.h"
#include"GameState.h"
#include "MoveDataRecord.h"
#include"TitleScene.h"
#include"StageScene.h"
#include"StageManager.h"
#include"SoundManager.h"
#include"Game.h"

void Initt();
void Updatee(GameState& state);
void Renderr(GameState& state);

int main()
{
	GameState state;
	Initt();
	state.curScene = Scene::STAGE;
	while (state.isRunning)
	{
		SoundManager::GetInst()->Update();
		Updatee(state);
		Renderr(state);
		FrameSync(60);
	}
	StageManager::DestroyInst();
	SoundManager::DestroyInst();
}


void Initt()
{
	InitTitle();
	StageManager::GetInst()->LoadStage();
	MapData mapData
	{
		"Test Map1"
		,
	{ //map
		"........0Q.....",//0
	".S.B....0Q.....",//1
	"........0Q.....",//2
	"........PQ.....",//3
	"........0Q.....",//4
	"........0Q.....",//5
	"........0QQQQQQ",//6
	"..qqq..U.......",//7
	"...............",//8
	"...............",//9
	"...........P...",//10
	"...b...........",//11
	"...............",//12
	"...............",//13
	"..............." //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE1, std::make_unique<MapData>(mapData));

	MapData mapData2
	{
		"Test Map2"
		,
	{
		"........0Q.....",//0
	".S.B....0Q.....",//1
	"........0Q.....",//2
	"........PQ.....",//3
	"........0Q.....",//4
	"........0Q.....",//5
	"........0QQQQQQ",//6
	"..qqq..U.......",//7
	"...............",//8
	"...............",//9
	"...........P...",//10
	"...b...........",//11
	"...............",//12
	"...............",//13
	"..............." //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE2, std::make_unique<MapData>(mapData2));
	StageManager::GetInst()->SaveStage();
	StageManager::GetInst()->ChangeStage(Stage::STAGE1);
}

void Updatee(GameState& state)
{
	bool sceneChanged = state.prevScene != state.curScene;
	state.prevScene = state.curScene;

	switch (state.curScene)
	{
	case Scene::INGAME:
		if (sceneChanged)
		{
			//Init(state);
			SetConsoleSize(WIDTH, HEIGHT);
			SetConsoleWindowStyle(true);
			SetConsoleMouseInputDisabled();
			SetCursorVisible(false);
			InitInGame(state);
			LoadMap(state, StageManager::GetInst()->GetCurMapData().m_map);
		}
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
	if (GetKey('C'))
	{
		StageSaveData& stageData = StageManager::GetInst()->GetCurStageSaveData();
		stageData.m_isLock = !stageData.m_isLock;
		StageManager::GetInst()->SaveStage();
	}
}

void Renderr(GameState& state)
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
