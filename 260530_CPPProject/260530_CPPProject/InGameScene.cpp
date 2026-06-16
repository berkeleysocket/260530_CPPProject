#include "InGameScene.h"

void InitInGame(GameState& state)
{
	SetConsoleSize(MAP_W * 3, MAP_H * 1.5);
	LoadMap(state, state.mapBox.m_gameMap);
}
void ClearStage(GameState& state)
{
	//Stage 클리어 처리
	SetColor(Color::LIGHT_YELLOW);
	cout << endl;
	cout << "Stage Clear!!";
}
void LoadMap(GameState& state, const vector<string>& gameMap)
{
	int w = gameMap[0].size(); // 이렇게 할려면 무조권 맵이 사각형이여야함 (공백으로 체워도 상과 x)
	int h = gameMap.size();

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
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
		cout << endl;
	}
	SetColor();
}
void DrawBlock(GameState& state, int x, int y)
{
	BlockType blockType = state.map[y][x];
	Block* block = state.blocks[y][x];

	if (block == nullptr) return;
	  
	switch (blockType)
	{
	case BlockType::LASERCORE_RED_UP_AUTO:
	case BlockType::LASERCORE_RED_UP_STATIC:
	case BlockType::LASERCORE_RED_DOWN_AUTO:
	case BlockType::LASERCORE_RED_DOWN_STATIC:
	case BlockType::LASERCORE_RED_LEFT_AUTO:
	case BlockType::LASERCORE_RED_LEFT_STATIC:
	case BlockType::LASERCORE_RED_RIGHT_AUTO:
	case BlockType::LASERCORE_RED_RIGHT_STATIC:
	{
		((LaserCore*)block)-> TryDrawCast(state);
		break;
	}
	}

	SetColor(block->GetColor());
	cout << (block->GetImage());
}
bool TryDrawPlayer(GameState& state, int x, int y)
{
	if (state.player.GetMapPos() == Position{ x, y } )
		//플레이어를 그릴 때도 죽었다면 그리지 말아야 한다.
	{
		SetColor();
		cout << "★";
		//state.player.Render();
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

	cout << nextPos.x << "," << nextPos.y << " : " << (char)nextBlockType << "   ";

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
	case BlockType::LASERBEAM_HORIZONTAL:
	case BlockType::LASERBEAM_VERTICAL:
	{
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
				}
			}
			cout << endl;
		}
		break;
	}
	case BlockType::BUTTOON_RED:
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
	case BlockType::END:
	{
		ShakeConsoleWindow(15, 40, 25);

		ClearStage(state);
		break;
	}
	}
}
void HandleCloneBlockInteraction(GameState& state, Block* block, BlockType blockType)
{
	Position blockPos = block->m_position;

	switch (blockType)
	{
	case BlockType::LASERBEAM_HORIZONTAL:
	case BlockType::LASERBEAM_VERTICAL:
		{
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

						state.player.SetPos(cursorPos, { _x, _y });
					}
				}
				cout << endl;
			}
			break;
		}
	case BlockType::BUTTOON_RED:
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
