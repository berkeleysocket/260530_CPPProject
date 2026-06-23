#include "Game.h"

void Init()
{
	SetConsoleSize(WIDTH, HEIGHT);
	SetConsoleWindowStyle(true);
	SetConsoleMouseInputDisabled();
	SetCursorVisible(false);
	SetConsoleSize(MAP_W * 3, MAP_H * 1.5);

	SoundManager::GetInst()->Init();
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
	SoundManager::GetInst()->Load("Selecte", "Resources/Sounds/Selecte.wav");
	SoundManager::GetInst()->Load("Lock", "Resources/Sounds/Lock.wav");
	SoundManager::GetInst()->Load("RealSelecte", "Resources/Sounds/RealSelecte.wav");
	SoundManager::GetInst()->Load("Exit", "Resources/Sounds/Exit.wav");
	SoundManager::GetInst()->Load("Restart", "Resources/Sounds/Restart.wav");
	LoadMaps();
}

void LoadMaps()		
{
	StageManager::GetInst()->LoadStage();

	MapData mapData
	{
		"Easy Map"
		,
	{ 
	"000000000000000",//0
	"0...S........p0",//1
	"0.............0",//2
	"000000000.....0",//3
	"0...p...0.....0",//4
	"0.......0WWWWW0",//5
	"0.......0.....0",//6
	"0.......0.....0",//7
	"0.......0QQQQQ0",//8
	"0..b.B..0.....0",//9
	"00000000Y.... 0",//10
	"0.............0",//11
	"0E............0",//12
	"0..........B..0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE1, std::make_unique<MapData>(mapData));

	mapData =
	{
		"Clone Map"
		,
	{ 
	"000000000000000",//0
	"0.S..........p0",//1
	"0u............0",//2
	"000000000.....0",//3
	"0d..p...0CCCCC0",//4
	"0.......0.....0",//5
	"0.......0.....0",//6
	"0QQQQQQQ0..b..0",//7
	"0.......0000000",//8
	"0...P..u0..P..0",//9
	"000000000.... 0",//10
	"0.............0",//11
	"0E............0",//12
	"0.............0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE2, std::make_unique<MapData>(mapData));

	//"000000000000000",//0
	//	"0.............0",//1
	//	"0.............0",//2
	//	"0.............0",//3
	//	"0.............0",//4
	//	"0.............0",//5
	//	"0.............0",//6
	//	"0.............0",//7
	//	"0.............0",//8
	//	"0.............0",//9
	//	"0............ 0",//10
	//	"0.............0",//11
	//	"0.............0",//12
	//	"0.............0",//13
	//	"000000000000000" //14
	mapData =
	{
		"Clone Map"
		,
	{
	"000000000000000",//0
	"0.............0",//1
	"0.............0",//2
	"0.............0",//3
	"0.............0",//4
	"0.............0",//5
	"0.............0",//6
	"0.............0",//7
	"0.............0",//8
	"0.............0",//9
	"0............ 0",//10
	"0.............0",//11
	"0.............0",//12
	"0.............0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE2, std::make_unique<MapData>(mapData));

	mapData =
	{
		"Normal Map"
		,
	{ 
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
	StageManager::GetInst()->RegisterStage(Stage::STAGE3, std::make_unique<MapData>(mapData));

	mapData =
	{
		"Hard Map"
		,
	{
	"000000000000000",//0
	"0..S.......0.p0",//1
	"0..........0..0",//2
	"0CCCBN.....0..0",//3
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
	"000000000000000" //14S
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::ENDSTAGE, std::make_unique<MapData>(mapData));

	StageManager::GetInst()->ChangeStage(Stage::STAGE1);
	StageSaveData& sd = StageManager::GetInst()->GetCurStageSaveData();
	sd.m_isLock = false;

	StageManager::GetInst()->SaveStage();
}

void Update(GameState& state)
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
			InitInStage(state);
		UpdateInGame(state);
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

void Render(GameState& state)
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
		RenderInGame(state);
		break;
	case Scene::STAGE:
		RenderStage(state);
		break;
	case Scene::TITLE:
		RenderTitle(state);
		break;
	}
}