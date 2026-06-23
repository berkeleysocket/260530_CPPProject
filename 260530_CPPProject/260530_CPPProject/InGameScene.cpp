#include "InGameScene.h"

void InitInGame(GameState& state)
{
	SetConsoleSize(MAP_W * 3, MAP_H * 1.5);
	LoadMap(state, StageManager::GetInst()->GetCurMapData().m_map);
	state.clone.Dead();
}

void ClearStage(GameState& state)
{
	//사운드

	//Stage 클리어 처리

	Sleep(1000);
	StageManager::GetInst()->Clear(state.curStage);
	state.curScene = Scene::STAGE;
}

void LoadMap(GameState& state, const string gameMap[MAP_H])
{
	for (int y = 0; y < MAP_H; ++y)
	{ 
		for (int x = 0; x < MAP_W; ++x)
		{
			int data = gameMap[y][x];
			BlockType blockType = (BlockType)data;
			Block* block = GenerateBlock((BlockType)data);

			block->m_position = { x, y };
			
			state.blocks[y][x] = block;
			state.map[y][x] = blockType; 

			if (blockType == BlockType::START)
			{
				Position cursorPos = { x * 2, y };
				Position mapPos = { x, y };
				state.player.SetSpawnPos(cursorPos, mapPos);
				state.player.SetPos(cursorPos, mapPos);
				state.map[y][x] = BlockType::EMPTY;
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

			DrawBlock(state, x, y);
		}
		SetDefaultMode();
		cout << endl;
	}

	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			if (Position{ x,y } == state.player.GetMapPos())
			{
				GotoXY(x * 2, y);
				switch (state.map[y][x])
				{
				case BlockType::LASERBEAM_UP:
				case BlockType::LASERBEAM_DOWN:
				case BlockType::LASERBEAM_RIGHT:
				case BlockType::LASERBEAM_LEFT:
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
	BlockType blockType = state.map[y][x];
	Block* block = state.blocks[y][x];

	if (block == nullptr) return;
	  
	switch (blockType)
	{
	case BlockType::LASERCORE_UP_AUTO:
	case BlockType::LASERCORE_UP_STATIC:
	case BlockType::LASERCORE_DOWN_AUTO:
	case BlockType::LASERCORE_DOWN_STATIC:
	case BlockType::LASERCORE_LEFT_AUTO:
	case BlockType::LASERCORE_LEFT_STATIC:
	case BlockType::LASERCORE_RIGHT_AUTO:
	case BlockType::LASERCORE_RIGHT_STATIC:
	{
		((LaserCore*)block)-> TryDrawCast(state);
		break;
	}
	}

	SetColor(block->GetColor());
	cout << (block->GetImage());
}

void DrawUI(GameState& state)
{
	GotoXY(0, 15);
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
	cout << "[ESC] Main Menu";
	GotoXY(32, 1);
	cout << "[R] Restart";
}

bool TryDrawPlayer(GameState& state, int x, int y)
{
	if (state.player.GetMapPos() == Position{ x, y } )
	{
		SetColor();
		cout << "★";
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

	Position dirToPos = DirToMapPosition(dir);
	Position playerPos = state.player.GetMapPos();
	Position nextPos = playerPos + dirToPos;
	BlockType nextBlockType = state.map[nextPos.y][nextPos.x];

	//cout << nextPos.x << "," << nextPos.y << " : " << (char)nextBlockType << "   ";

	if (IsEdge(nextPos.x, nextPos.y))
	{
		return false;
	}

	Block* nextBlock = state.blocks[nextPos.y][nextPos.x];
	if (!IsPassable(nextBlock, nextBlockType))
	{
		HandlePlayerBlockInteraction(state, nextBlock, nextBlockType);
		return false;
	}

	return true;
}

bool TryCloneMove(GameState& state, Dir dir)
{
	Position dirToPos = DirToMapPosition(dir);
	Position clonePos = state.clone.GetMapPos();
	Position nextPos = clonePos + dirToPos;

	if (IsEdge(nextPos.x, nextPos.y))
		return false;

	Block* nextBlock = state.blocks[nextPos.y][nextPos.x];
	BlockType nextBlockType = state.map[nextPos.y][nextPos.x];

	if (nextBlockType == BlockType::SWITCHABLEBRICK_CLONE_ON)
		return true;
	if (!IsPassable(nextBlock, nextBlockType))
	{
		HandleCloneBlockInteraction(state, nextBlock, nextBlockType);
		return false;
	}

	return true;
}

void HandlePlayerBlockInteraction(GameState& state, Block* block , BlockType blockType)
{
	Position blockPos = block-> m_position;

	switch (blockType)
	{
	case BlockType::LASERBEAM_UP:
	case BlockType::LASERBEAM_DOWN:
	case BlockType::LASERBEAM_RIGHT:
	case BlockType::LASERBEAM_LEFT:
	{
		state.uiColor1 = Color::RED;
		state.uiMessage1 = "플레이어가 죽었습니다.";
		HandlePlayerDead(state);
		break;
	}
	case BlockType::PORTAL_RED:
	{
		ShakeConsoleWindow(15, 40, 25);

		for (int _y = 0; _y < MAP_H; _y++)
		{
			for (int _x = 0; _x < MAP_W; _x++)
			{
				if (state.map[_y][_x] == BlockType::PORTAL_RED
					&& Position {_x, _y} != blockPos)
				{
					Position cursorPos = { 0,0 };
					cursorPos.x += _x * 2;
					cursorPos.y += _y * 2;
					
					state.player.SetPos(cursorPos, {_x, _y});

					state.uiColor1 = Color::YELLOW;
					state.uiMessage1 = "플레이어가 워프했습니다.";
				}
			}
			cout << endl;
		}
		break;
	}
	case BlockType::PORTAL_BLUE:
	{
		ShakeConsoleWindow(15, 40, 25);

		for (int _y = 0; _y < MAP_H; _y++)
		{
			for (int _x = 0; _x < MAP_W; _x++)
			{
				if (state.map[_y][_x] == BlockType::PORTAL_BLUE
					&& Position{ _x, _y } != blockPos)
				{
					Position cursorPos = { 0,0 };
					cursorPos.x += _x * 2;
					cursorPos.y += _y * 2;

					state.player.SetPos(cursorPos, { _x, _y });

					state.uiColor1 = Color::YELLOW;
					state.uiMessage1 = "플레이어가 워프했습니다. ";
				}
			}
			cout << endl;
		}
		break;
	}
	case BlockType::BUTTON_RED:
	{
		ShakeConsoleWindow(15, 40, 25);

		RedButton* redButton = (RedButton*)block;
		redButton->Press(state);

		state.uiColor1 = Color::YELLOW;
		state.uiMessage1 = "플레이어가 빨간 버튼을 눌렀습니다.";
		break;
	}
	case BlockType::BUTTON_BLUE:
	{
		ShakeConsoleWindow(15, 40, 25);

		BlueButton* blueButton = (BlueButton*)block;
		blueButton->Press(state);

		state.uiColor1 = Color::YELLOW;
		state.uiMessage1 = "플레이어가 파란 버튼을 눌렀습니다.";
		break;
	}
	case BlockType::BUTTON_CLONE:
	{
		ShakeConsoleWindow(15, 40, 25);

		CloneButton* cloneButton = (CloneButton*)block;
		cloneButton->Press(state);

		state.uiColor1 = Color::YELLOW;
		state.uiMessage1 = "플레이어가 클론 버튼을 눌렀습니다.";
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
	}
}

void HandleCloneBlockInteraction(GameState& state, Block* block, BlockType blockType)
{
	Position blockPos = block->m_position;

	switch (blockType)
	{
	case BlockType::LASERBEAM_UP:
	case BlockType::LASERBEAM_DOWN:
	case BlockType::LASERBEAM_LEFT:
	case BlockType::LASERBEAM_RIGHT:
		{
			HandleCloneDead(state);
			break;
		}
	case BlockType::PORTAL_RED:
		{
			ShakeConsoleWindow(15, 40, 25);

			for (int _y = 0; _y < MAP_H; _y++)
			{
				for (int _x = 0; _x < MAP_W; _x++)
				{
					if (state.map[_y][_x] == BlockType::PORTAL_RED
						&& Position{ _x, _y } != blockPos)
					{
						Position cursorPos = { 0,0 };
						cursorPos.x += _x * 2;
						cursorPos.y += _y * 2;

						state.clone.SetPos(cursorPos, { _x, _y });
					}
				}
				cout << endl;
			}
			break;
		}
	case BlockType::PORTAL_BLUE:
		{
			ShakeConsoleWindow(15, 40, 25);

			for (int _y = 0; _y < MAP_H; _y++)
			{
				for (int _x = 0; _x < MAP_W; _x++)
				{
					if (state.map[_y][_x] == BlockType::PORTAL_BLUE
						&& Position{ _x, _y } != blockPos)
					{
						Position cursorPos = { 0,0 };
						cursorPos.x += _x * 2;
						cursorPos.y += _y * 2;

						state.clone.SetPos(cursorPos, { _x, _y });
					}
				}
				cout << endl;
			}
			break;
		}
	case BlockType::BUTTON_RED:
		{
			ShakeConsoleWindow(15, 40, 25);

			RedButton* redButton = (RedButton*)block;
			redButton->Press(state);
			break;
		}
	case BlockType::BUTTON_BLUE:
		{
			ShakeConsoleWindow(15, 40, 25);

			BlueButton* blueButton = (BlueButton*)block;
			blueButton->Press(state);
			break;
		}
	case BlockType::BUTTON_CLONE:
	{
		ShakeConsoleWindow(15, 40, 25);

		CloneButton* cloneButton = (CloneButton*)block;
		cloneButton->Press(state);
		break;
	}
	case BlockType::END:
	{
		ShakeConsoleWindow(15, 40, 25);

		ClearStage(state);
		break;
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