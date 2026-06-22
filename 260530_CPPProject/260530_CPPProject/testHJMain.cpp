#include"Player.h"
#include"Console.h"
#include"GameState.h"
#include "MoveDataRecord.h"
#include"TitleScene.h"
#include"StageScene.h"
#include"StageManager.h"
#include"Game.h"

void Initt();
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
	StageManager::DestroyInst();
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

//struct HJTestState
//{
//	Player player;
//	Clone* clone = nullptr;
//	MoveDataRecord record;
//	float delta;
//};
//
//void Init(HJTestState& state);
//void Update(HJTestState& state);
//void Render(HJTestState& state);
//
//
//
//int main()
//{
//	HJTestState state;
//
//	Init(state);
//	ULONGLONG prevTick = 0;
//	while (true)
//	{
//		ULONGLONG curTick = GetTickCount64();
//		state.delta = (curTick - prevTick);
//		Update(state);
//		Render(state);
//		prevTick = curTick;
//		FrameSync(60);
//	}
//}
//
//void Init(HJTestState& state)
//{
//	SetCursorVisible(false);
//}
//
//void Update(HJTestState& state)
//{
//	UpdateInput();
//	if (GetKeyDown('W'))
//	{
//		state.player.Move(Dir::UP);
//		state.record.Record(MoveData{Dir::UP});
//	}
//	if (GetKeyDown('S'))
//	{
//		state.player.Move(Dir::DOWN);
//		state.record.Record(MoveData{ Dir::DOWN });
//
//	}
//	if (GetKeyDown('A'))
//	{
//		state.player.Move(Dir::LEFT);
//		state.record.Record(MoveData{ Dir::LEFT });
//
//	}
//	if (GetKeyDown('D'))
//	{
//		state.player.Move(Dir::RIGHT);
//		state.record.Record(MoveData{ Dir::RIGHT });
//
//	}
//	if(GetKeyDown('R'))
//	{
		//state.clone = new Clone(state.record.GetRecord());
//
//	}
//
//	state.player.Tick(state.delta);
//	if (state.clone != nullptr)
//	{
//
//		state.clone->Tick(state.delta);
//	}
//}
//
//void Render(HJTestState& state)
//{
//	state.player.Render();
//	if (state.clone)
//		state.clone->Render();
//}

