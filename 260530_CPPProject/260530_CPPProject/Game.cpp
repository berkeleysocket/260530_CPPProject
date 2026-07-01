#include "Game.h"

void Init()
{
	SetConsoleWindowStyle(true);
	SetConsoleMouseInputDisabled();
	SetCursorVisible(false);

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
	MapData mapData =
	{
		1,
		"Tutorial 1",
	{
	"000000000000000",//0
	"0.............0",//1
	"0......S......0",//2
	"0.............0",//3
	"0.............0",//4
	"0.............0",//5
	"0.............0",//6
	"0.............0",//7
	"0.............0",//8
	"0.............0",//9
	"0.............0",//10
	"0.............0",//11
	"0......E......0",//12
	"0.............0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::TUTORIAL_1, std::make_unique<MapData>(mapData));

	mapData =
	{
		2,
		"Tutorial 2",
	{
	"000000000000000",//0
	"0.............0",//1
	"0.S.........B.0",//2
	"0.............0",//3
	"00000000000WWW0",//4
	"0.............0",//5
	"0.b...........0",//6
	"0.............0",//7
	"0QQQ00000000000",//8
	"0.............0",//9
	"0...........B.0",//10
	"0.............0",//11
	"00000000000www0",//12
	"00000000000.E.0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::TUTORIAL_2, std::make_unique<MapData>(mapData));

	mapData =
	{
		3,
		"Tutorial 3",
	{
	"000000000000000",//0
	"0.............0",//1
	"0......S......0",//2
	"0.B...........0",//3
	"0.............0",//4
	"0r............0",//5
	"0.............0",//6
	"0.B...........0",//7
	"0.............0",//8
	"0............T0",//9
	"0000000.0000000",//10
	"0.............0",//11
	"0......E......0",//12
	"0.............0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::TUTORIAL_3, std::make_unique<MapData>(mapData));

	mapData =
	{
		4,
		"Tutorial 4",
	{
	"000000000000000",//0
	"0o......C..b..0",//1
	"0.....S.C.....0",//2
	"0N......C..B..0",//3
	"0QQQQQQQ0000000",//4
	"0.......0000000",//5
	"0.......0000000",//6
	"0.......0000000",//7
	"0.......0000000",//8
	"0.......0000000",//9
	"0WWWWWWW0000000",//10
	"0.......0000000",//11
	"0...E...0000000",//12
	"0.......0000000",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::TUTORIAL_4, std::make_unique<MapData>(mapData));

	mapData =
	{
		5,
		"Tutorial 5",
	{
	"000000000000000",//0
	"0...ddddddd...0",//1
	"0.S.........p.0",//2
	"0.............0",//3
	"0.............0",//4
	"0.p.........P.0",//5
	"0.............0",//6
	"000000000000000",//7
	"0.............0",//8
	"0......P......0",//9
	"0.............0",//10
	"0.............0",//11
	"0......E......0",//12
	"0.............0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::TUTORIAL_5, std::make_unique<MapData>(mapData));
	
	mapData =
	{
		6,
		"Stage 1",
	{ 
	"000000000000000",//0
	"0.............0",//1
	"0.S........p..0",//2
	"0.............0",//3
	"000000000.....0",//4
	"0...p...0WWWWW0",//5
	"0.......0.....0",//6
	"0.......0.....0",//7
	"0.......0.....0",//8
	"0..b.B..0QQQQQ0",//9
	"00000000Y.... 0",//10
	"0.............0",//11
	"0.E...........0",//12
	"0..........B..0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE_1, std::make_unique<MapData>(mapData));

	mapData =
	{
		7,
		"Stage 2",
	{ 
	"000000000000000",//0
	"0......q......0",//1
	"0.B....q....b.0",//2
	"0......q......0",//3
	"0......q......0",//4
	"0......q......0",//5
	"0......q......0",//6
	"0qqqqqqUQQQQQQ0",//7
	"0......Q......0",//8
	"0......Q......0",//9
	"0......Q..... 0",//10
	"0......Q......0",//11
	"0.S....Q....E.0",//12
	"0......Q......0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE_2, std::make_unique<MapData>(mapData));

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
		8,
		"Stage 3",
	{ 
	"000000000000000",//0
	"0..S.w.......No",//1
	"0....w........o",//2
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
	StageManager::GetInst()->RegisterStage(Stage::STAGE_3, std::make_unique<MapData>(mapData));

	mapData =
	{
		9,
		"Stage 4",
	{
	"000000000000000",//0
	"0..S...d...E..0",//1
	"0.............0",//2
	"0.............0",//3
	"0.............0",//4
	"0.............0",//5
	"0.......0000000",//6
	"0.............0",//7
	"0....p...p..b.0",//8
	"0.............0",//9
	"0QQQQQQQQQQQQQ0",//10
	"0CCCCCC.......0",//11
	"0..B.......N..0",//12
	"0.............0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::STAGE_4, std::make_unique<MapData>(mapData));

	mapData =
	{
		10,
		"Tutorial 6",
	{
	"000000000000000",//0
	"000000000000000",//1
	"000000000000000",//2
	"000000000000000",//3
	"000000000000000",//4
	"0ooooooooooooo0",//5
	"0.......gQ....0",//6
	"0.S.....gQ..G.0",//7
	"0.......gQ....0",//8
	"0ooooooooooooo0",//9
	"000000000000000",//10
	"000000000000000",//11
	"000000000000000",//12
	"000000000000000",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::TUTORIAL_6, std::make_unique<MapData>(mapData));

	mapData =
	{
		11,
		"End Stage",
	{
	"000000000000000",//0
	"0o.........Q..0",//1
	"0o.b....S..Q.B0",//2
	"0o.........Q..0",//3
	"0l............0",//4
	"0.............0",//5
	"0.............0",//6
	"0.............0",//7
	"0.............0",//8
	"0ggggggggggggg0",//9
	"0QQQQQQQQQQQQQ0",//10
	"0.............0",//11
	"0......G......0",//12
	"0.............0",//13
	"000000000000000" //14
	}
	};
	StageManager::GetInst()->RegisterStage(Stage::ENDSTAGE, std::make_unique<MapData>(mapData));

	StageManager::GetInst()->ChangeStage(Stage::TUTORIAL_1);
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
	case Scene::END:
		if(sceneChanged)
			InitEnd(state);
		UpdateEnd(state);
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