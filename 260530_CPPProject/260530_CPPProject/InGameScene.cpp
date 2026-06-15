#include "InGameScene.h"
#include "StageManager.h"

void LoadMap(GameState& state, const vector<string>& gameMap)
{
	int w = gameMap[0].size(); // 이렇게 할려면 무조권 맵이 사각형이여야함 (공백으로 체워도 상과 x)
	int h = gameMap.size();
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int data = gameMap[y][x] - '0';
			state.map[y][x] = (BlockType)data;
			state.blocks[y][x] = GenerateBlock((BlockType)data);
			if (state.map[y][x] == BlockType::START)
			{
				//state.player.pos = { x,y };
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
			int data = gameMap[y][x] - '0';
			BlockType blockType = (BlockType)data;
			state.map[y][x] = blockType;
			state.blocks[y][x] = GenerateBlock(blockType);
			if (state.map[y][x] == BlockType::START)
			{
				state.player.SetSpawnPos({ x,y},{x,y});
				state.map[y][x] = BlockType::EMPTY;
			}
		}
	}
}

void InitInGame(GameState& state)
{
	SetConsoleSize(MAP_W * 3, MAP_H * 2);
}

void DrawMap(GameState& state)
{
	StageManager::GetInst()->GetCurMapData().m_map;
	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			if (TryDrawClone(state, x, y))
				continue;
			if (TryDrawPlayer(state, x, y))
				continue;

			DrawBlock(state, x, y);
		}
		cout << endl;
	}
	SetColor();
}

void DrawBlock(GameState& state, int x, int y)
{
	SetDefaultMode();
	SetColor();
	Block* block = state.blocks[y][x];

	if (block == nullptr) return;
	  
	switch (state.map[y][x])
	{
	case BlockType::EMPTY:
	case BlockType::BRICK:
	case BlockType::LASERBEAM_HORIZONTAL:
	case BlockType::LASERBEAM_VERTICAL:
	{
		break;
	}
	case BlockType::LASERCORE:
	{
		LaserCore* laserCore = (LaserCore*)block;
		laserCore-> Cast(state, x, y);
		break;
	}
	case BlockType::PORTAL_RED_ENTER:
	{
		break;
	}
	}

	SetColor(block->GetColor());
	cout << (block->GetImage());
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
	int dirX(0);
	int dirY(0);

	switch (dir)
	{
	case Dir::UP:
		dirY--;
		break;
	case Dir::DOWN:
		dirY++;
		break;
	case Dir::LEFT:
		dirX--;
		break;
	case Dir::RIGHT:
		dirX++;
		break;
	}

	Position playerPos = state.player.GetMapPos();

	Position next =
	{
		playerPos.x + dirX,
		playerPos.y + dirY
    };

	if (IsEdge(next.x, next.y))
		return false;

	BlockType nextBlock = state.map[next.y][next.x];
	if (nextBlock != BlockType::EMPTY)
	{
		HandlePlayerBlockInteraction(state, nextBlock);
		return false;
	}

	return true;
}

bool TryCloneMove(GameState& state, Dir dir)
{
	int dirX(0);
	int dirY(0);

	switch (dir)
	{
	case Dir::UP:
		dirY--;
		break;
	case Dir::DOWN:
		dirY++;
		break;
	case Dir::LEFT:
		dirX--;
		break;
	case Dir::RIGHT:
		dirX++;
		break;
	}

	Position clonePos = state.clone.GetMapPos();

	Position next =
	{
		clonePos.x + dirX,
		clonePos.y + dirY
	};

	if (IsEdge(next.x, next.y))
		return false;

	BlockType nextBlock = state.map[next.y][next.x];
	cout << next.x << "," << next.y << "is not Empty?";
	if (nextBlock != BlockType::EMPTY)
	{
		HandleCloneBlockInteraction(state, nextBlock);
		return false;
	}

	return true;
}

void HandlePlayerBlockInteraction(GameState& state, BlockType block)
{
	switch (block)
	{
	case BlockType::BRICK:
	{
		break;
	}
	case BlockType::LASERBEAM_HORIZONTAL:
	case BlockType::LASERBEAM_VERTICAL:
	{
		//플레이어 죽는 처리
		HandlePlayerDead(state);
		break;
	}
	case BlockType::PORTAL_RED_ENTER:
	{
		ShakeConsoleWindow(15, 40, 25);
		for (int _y = 0; _y < MAP_H; _y++)
		{
			for (int _x = 0; _x < MAP_W; _x++)
			{
				if (state.map[_y][_x] == BlockType::PORTAL_RED_EXIT)
				{
					Position cursorPos = { 0,0 };
					cursorPos.x += _x * 2;
					cursorPos.y += _y * 2;
					//for (int i = 0; i < _x; ++i)
					//{
					//	cursorPos.x += 2;
					//}
					//for (int i = 0; i < _y; ++i)
					//{
					//	cursorPos.y += 2;
					//}
					state.player.SetPos(cursorPos, {_x, _y});
				}
			}
		}
		break;
	}
	case BlockType::PORTAL_RED_EXIT:
	{
		ShakeConsoleWindow(15, 40, 25);
		for (int _y = 0; _y < MAP_H; _y++)
		{
			for (int _x = 0; _x < MAP_W; _x++)
			{
				if (state.map[_y][_x] == BlockType::PORTAL_RED_ENTER)
				{
					Position cursorPos = { 0,0 };
					for (int i = 0; i < _x; ++i)
					{
						cursorPos.x += 2;
					}
					for (int i = 0; i < _y; ++i)
					{
						cursorPos.y += 2;
					}
					state.player.SetPos(cursorPos, { _x, _y });
				}
			}
		}
		break;
	}
	case BlockType::BUTTON_RASERCORE:
	{
		ShakeConsoleWindow(15, 40, 25);
		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				if (state.map[y][x] == BlockType::LASERCORE)
				{
					((LaserCore*)(state.blocks[y][x]))->ChangeDirection(state, Dir::UP);
					((LaserCore*)(state.blocks[y][x]))->Cast(state, x, y);
				}
			}
		}
		break;
	}

	}
}

void HandleCloneBlockInteraction(GameState& state, BlockType block)
{
	cout << "HandleCloneBlockInteraction";
	switch (block)
	{
	case BlockType::BRICK:
	{
		break;
	}
	case BlockType::LASERBEAM_HORIZONTAL:
	case BlockType::LASERBEAM_VERTICAL:
	{
		HandleCloneDead(state);
		break;
	}
	case BlockType::PORTAL_RED_ENTER:
	{
		ShakeConsoleWindow(15, 40, 25);
		cout << "PORTAL_RED_ENTERPORTAL_RED_ENTER";
		for (int _y = 0; _y < MAP_H; _y++)
		{
			for (int _x = 0; _x < MAP_W; _x++)
			{
				if (state.map[_y][_x] == BlockType::PORTAL_RED_EXIT)
				{
					Position cursorPos = { 0,0 };
					cursorPos.x += _x * 2;
					cursorPos.y += _y * 2;

					state.clone.SetPos(cursorPos, { _x, _y });
				}
			}
		}
		break;
	}
	case BlockType::PORTAL_RED_EXIT:
	{
		cout << "PORTAL_RED_EXITPORTAL_RED_EXIT";

		ShakeConsoleWindow(15, 40, 25);
		for (int _y = 0; _y < MAP_H; _y++)
		{
			for (int _x = 0; _x < MAP_W; _x++)
			{
				if (state.map[_y][_x] == BlockType::PORTAL_RED_ENTER)
				{
					Position cursorPos = { 0,0 };
					cursorPos.x += _x * 2;
					cursorPos.y += _y * 2;

					state.clone.SetPos(cursorPos, { _x, _y });
				}
			}
		}
		break;
	}
	case BlockType::BUTTON_RASERCORE:
	{
		ShakeConsoleWindow(15, 40, 25);
		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				if (state.map[y][x] == BlockType::LASERCORE)
				{
					((LaserCore*)(state.blocks[y][x]))->ChangeDirection(state, Dir::UP);
					((LaserCore*)(state.blocks[y][x]))->Cast(state, x, y);
				}
			}
		}
		break;
	}

	}
}

void HandlePlayerDead(GameState& state)
{
	Position startPos = state.player.GetStartPos();
	Position cursorPos = { startPos.x * 2, startPos.y * 2 };
	state.clone.Spawn(state.moveDataRecord.GetRecord());

	ShakeConsoleWindow(4, 200, 4);
	state.clone.SetPos(cursorPos, startPos);
	state.player.SetPos(cursorPos, startPos);
}

void HandleCloneDead(GameState& state)
{
	ShakeConsoleWindow(4, 200, 4);
	state.clone.Dead();
}