#include"GameState.h"
#include"TitleScene.h"
#include"StageScene.h"
#include"StageManager.h"
#include"SoundManager.h"
#include"Game.h"

void Initt();
void LoadMaps();
void Updatee(GameState& state);
void Renderr(GameState& state);

int main()
{
	GameState state;
	Initt();
	state.curScene = Scene::TITLE;
	while (state.isRunning)
	{
		Updatee(state);
		Renderr(state);
		FrameSync(60);
	}
	SoundManager::GetInst()->Release();
	StageManager::DestroyInst();
}


void Initt()
{
	SoundManager::GetInst()->Init();
	LoadMaps();

	SoundManager::GetInst()->Load("test", "test/Collecte.mp3");
}

void LoadMaps()
{
	StageManager::GetInst()->LoadStage();
	MapData mapData
	{
		"Test Map1"
		,
	{ //map
"000000000000000", //0
"0S.........B000", //1
"0..........W000", //2
"0..........W000", //3
"0..........W000", //4
"0000000....W000", //5
"0.....0....W000", //6
"0..N..0....W000", //7
"0.....0....W000", //8
"0.....0....W000", //9
"0.....0....W000", //10
"0.....0....W000", //11
"0.....0....Ur00", //12
"0..E..0....w000",  //13
"000000000000000"
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
			//InitInGame(state);
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
		SoundManager::GetInst()->Play("test");
		StageSaveData& stageData = StageManager::GetInst()->GetCurStageSaveData();
		stageData.m_isLock = !stageData.m_isLock;
		StageManager::GetInst()->SaveStage();
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