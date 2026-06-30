#include "InGameScene.h"

void InitInStage(GameState& state)
{
	SetConsoleSize(MAP_W * 4, MAP_H * 1.5);
	SoundManager::GetInst()->PlayBGM("Resources/Sounds/InGameBGM.wav");
	GenerateMap(state, StageManager::GetInst()->GetCurMapData().m_map);
	state.clone.Init();
	state.moveDataRecord.ReSet();
}

void UpdateInGame(GameState& state)
{
	Dir dir;
	UpdateInput();
	if (GetKeyDown('W'))
	{
		dir = Dir::UP;
		if (TryPlayerMove(state, dir))
			state.player.Move(dir);
	}
	if (GetKeyDown('S'))
	{
		dir = Dir::DOWN;
		if (TryPlayerMove(state, dir))
			state.player.Move(dir);
	}
	if (GetKeyDown('A'))
	{
		dir = Dir::LEFT;
		if (TryPlayerMove(state, dir))
			state.player.Move(dir);
	}
	if (GetKeyDown('D'))
	{
		dir = Dir::RIGHT;
		if (TryPlayerMove(state, dir))
			state.player.Move(dir);
	}

	if (GetKeyDown(VK_ESCAPE))
	{
		SoundManager::GetInst()->Play("Exit");
		state.curScene = Scene::STAGE;
		state.prevStage = Stage::NONE;
	}

	if (GetKeyDown('R'))
	{
		SoundManager::GetInst()->Play("Restart");
		state.curScene = Scene::RESTART;
	}

	state.clone.Tick(state, state.delta);
}

void RenderInGame(GameState& state)
{
	GotoXY(0, 0);
	DrawMap(state);
	DrawUI(state);
}

void ClearStage(GameState& state)
{
	//Stage 클리어 처리
	SoundManager::GetInst()->Play("StageClear");

	Sleep(500);
	StageManager::GetInst()->Clear(state.curStage);
	state.curScene = Scene::STAGE;
	state.prevStage = Stage::NONE;
}

void GenerateMap(GameState& state, const string gameMap[MAP_H])
{
	for (int y = 0; y < MAP_H; ++y)
	{ 
		for (int x = 0; x < MAP_W; ++x)
		{
			int data = gameMap[y][x];
			GenerateBlockType generateBlockType = (GenerateBlockType)data;
			BlockType blockType = (BlockType)data;
			Block* block = GenerateBlock((GenerateBlockType)data);

			block->SetPosition({x,y});
			
			state.map[y][x] = block;

			if (blockType == BlockType::START)
			{
				Position cursorPos = { x * 2, y };
				Position mapPos = { x, y };
				state.player.SetSpawnPos(cursorPos, mapPos);
				state.player.SetPos(cursorPos, mapPos);
			}
		}
	}
}

void DrawMap(GameState& state)
{
	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			GotoXY(x * 2, y);

			if (TryDrawPlayer(state, x, y))
				continue;
			if (TryDrawClone(state, x, y))
				continue;

			PreDrawBlock(state, x, y);
			DrawBlock(state, x, y);
		}
		SetDefaultMode();
		cout << endl;
	}

	PostDrawBlock(state);
}

void PreDrawBlock(GameState& state, int x, int y)
{
	Block* blockPtr = state.map[y][x];
	BlockType blockType = blockPtr -> GetType();

	if (blockPtr == nullptr) return;

	switch (blockType)
	{
	case BlockType::LASERCORE:
	{
		((LaserCore*)blockPtr) -> TryDrawCast(state);
		break;
	}
	}
}

void PostDrawBlock(GameState& state)
{
	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			if (Position{ x,y } == state.player.GetMapPos())
			{
				switch (state.map[y][x] -> GetType())
				{
				case BlockType::LASERCORE:
				{
					HandlePlayerDead(state);
					break;
				}
				}
			}
		}
	}
}

void DrawBlock(GameState& state, int x, int y)
{
	Block* block = state.map[y][x];

	if (block == nullptr) return;

	SetColor(block -> GetColor());
	cout << (block -> GetImage());
}

void DrawUI(GameState& state)
{
	GotoXY(0, 15);
	if (state.uiMessage1.empty())
		SetColor();
	else
		SetColor(state.uiColor1);
	cout << state.uiMessage1 << "              ";

	GotoXY(0, 16);
	SetColor(Color::RED);
	cout << "@";
	SetColor(Color::WHITE);
	cout << " : 빨간 포탈";
	SetColor(Color::BLUE);
	cout << " @";
	SetColor(Color::WHITE);
	cout << " : 파란 포탈";

	GotoXY(0, 17);
	SetColor(Color::RED);
	cout << "⊙";
	SetColor(Color::WHITE);
	cout << " : 빨간 버튼";
	SetColor(Color::BLUE);
	cout << " ⊙";
	SetColor(Color::WHITE);
	cout << " : 파란 버튼";

	GotoXY(0, 18);
	SetColor(Color::RED);
	cout << "※";
	SetColor(Color::WHITE);
	cout << " : 레이저 코어";
	SetColor(Color::RED);
	cout << " ↑";
	SetColor(Color::WHITE);
	cout << " : 레이저";

	GotoXY(0, 19);
	SetColor(Color::LIGHT_GREEN);
	cout << "⊙";
	SetColor(Color::WHITE);
	cout << " : 클론 버튼";
	SetColor(Color::LIGHT_GREEN);
	cout << " ■";
	SetColor(Color::WHITE);
	cout << " : 클론 스위치 벽";

	GotoXY(0, 20);
	SetColor(Color::LIGHT_RED);
	cout << "■";
	SetColor(Color::WHITE);
	cout << " : 빨간 스위치 벽";
	SetColor(Color::BLUE);
	cout << " ■";
	SetColor(Color::WHITE);
	cout << " : 파란 스위치 벽";

	GotoXY(32, 0);
	cout << "[ESC] Selecte Stage";
	GotoXY(32, 1);
	cout << "[R] Restart";

}

bool TryDrawPlayer(GameState& state, int x, int y)
{
	if (state.player.GetMapPos() == Position{ x, y } )
	{
		state.player.Render();
		return true;
	}

	return false;
}

bool TryDrawClone(GameState& state, int x, int y)
{
	if (state.clone.GetMapPos() == Position{ x, y }
		&& state.clone.IsActive())
	{
		state.clone.Render();
		return true;
	}

	return false;
}

bool TryPlayerMove(GameState& state, Dir dir)
{
	MoveData moveData;
	moveData.dir = dir;
	state.moveDataRecord.Record(moveData);

	Position dirToPos = DirToScreenPosition(dir);
	Position playerPos = state.player.GetMapPos();
	Position nextPos = playerPos + dirToPos;

	if (IsEdge(nextPos.x, nextPos.y))
		return false;

	Block* nextBlock = state.map[nextPos.y][nextPos.x];
	if (!IsPlayerPassable(nextBlock))
	{
		HandlePlayerBlockInteraction(state, nextBlock);
		return false;
	}

	return true;
}

bool TryCloneMove(GameState& state, Dir dir)
{
	Position dirToPos = DirToScreenPosition(dir);
	Position clonePos = state.clone.GetMapPos();
	Position nextPos = clonePos + dirToPos;

	if (IsEdge(nextPos.x, nextPos.y))
		return false;

	Block* nextBlock = state.map[nextPos.y][nextPos.x];

	if (state.map[nextPos.y][nextPos.x]->GetType() == BlockType::SWITCHABLEBRICK)
	{

		return true;
	}
	if (!IsClonePassable(nextBlock))
	{
		HandleCloneBlockInteraction(state, nextBlock);
		return false;
	}

	return true;
}

void HandlePlayerBlockInteraction(GameState& state, Block* block)
{
	BlockType blockType = block->GetType();
	Position blockPosition = block->GetPosition();

	switch (blockType)
	{
	case BlockType::LASERBEAM:
	{
		state.uiColor1 = Color::RED;
		state.uiMessage1 = "플레이어가 죽었습니다.";

		HandlePlayerDead(state);
		break;
	}
	case BlockType::PORTAL:
	{
		ShakeConsoleWindow(15, 40, 25);

		((Portal*)block)->Warp(state, state.player);

		state.uiColor1 = Color::YELLOW;
		state.uiMessage1 = "플레이어가 파란 포탈에 들어갔습니다.";
		break;
	}
	case BlockType::BUTTON:
	{
		ShakeConsoleWindow(15, 40, 25);

		((Button*)block)->Press(state);

		state.uiColor1 = Color::YELLOW;
		state.uiMessage1 = "플레이어가 빨간 버튼을 눌렀습니다.";
		break;
	}
	case BlockType::END:
	{
		ShakeConsoleWindow(15, 40, 25);

		ClearStage(state);

		state.uiColor1 = Color::YELLOW;
		state.uiMessage1 = "스테이지 클리어!";
		break;
	}
	case BlockType::BRICK_KILL:
	{
		HandlePlayerDead(state);
	}
	}
}

void HandleCloneBlockInteraction(GameState& state, Block* block)
{
	BlockType blockType = block->GetType();
	Position blockPos = block->GetPosition();

	switch (blockType)
	{
	case BlockType::LASERBEAM:
	{
		HandleCloneDead(state);
		break;
	}
	case BlockType::PORTAL:
	{
		ShakeConsoleWindow(15, 40, 25);

		Portal* portal = (Portal*)block;
		portal->Warp(state, state.clone);
		break;
	}
	case BlockType::BUTTON:
	{
		ShakeConsoleWindow(15, 40, 25);

		Button* button = (Button*)block;
		button->Press(state);
		break;
	}
	case BlockType::END:
	{
		ShakeConsoleWindow(15, 40, 25);

		ClearStage(state);
		break;
	}
	case BlockType::BRICK_KILL:
	{
		HandleCloneDead(state);
	}
	}
}

void HandlePlayerDead(GameState& state)
{
	Position startPos = state.player.GetStartPos();
	Position cursorPos = { startPos.x * 2, startPos.y };
	state.player.Dead();
	ShakeConsoleWindow(20, 30, 30);
	Sleep(500);

	state.clone.SetPos(cursorPos, startPos);
	state.player.SetPos(cursorPos, startPos);
	state.clone.Spawn(state.moveDataRecord.GetRecord());
	state.player.Spawn();
	state.moveDataRecord.ReSet();
}

void HandleCloneDead(GameState& state)
{
	state.clone.Dead();
	ShakeConsoleWindow(20, 30, 30);
	Sleep(500);
}