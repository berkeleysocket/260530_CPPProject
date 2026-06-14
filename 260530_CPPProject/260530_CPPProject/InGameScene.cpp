#include "InGameScene.h"

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
				//state.player.pos = { x,y };
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
	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
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

	switch (state.map[y][x])
	{
	case BlockType::EMPTY:
	case BlockType::BRICK:
	case BlockType::LASERBEAM_HORIZONTAL:
	case BlockType::LASERBEAM_VERTICAL:
	{
		break;
	}
	case BlockType::LASERCORE_RED:
	case BlockType::LASERCORE_BLUE:
	{
		LaserCore* laserCore = (LaserCore*)block;
		laserCore-> Cast(state, x, y);
		break;
	}
	case BlockType::PORTAL_RED:
	case BlockType::PORTAL_BLUE:
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
		HandleBlockInteraction(state, nextBlock,next.x,next.y);
		return false;
	}

	return true;
}

void HandleBlockInteraction(GameState& state, BlockType block, int x, int y)
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
		ShakeConsoleWindow(25, 100, 25);
		break;
	}
	case BlockType::PORTAL_RED:
	{
		ShakeConsoleWindow(15, 40, 25);
		for (int _y = 0; _y < MAP_H; _y++)
		{
			for (int _x = 0; _x < MAP_W; _x++)
			{
				cout << _x << endl;
				if (state.map[_y][_x] == BlockType::PORTAL_RED
					&& _y != y && _x != x)
				{
					cout << "BlockType::PORTAL_RED:BlockType::PORTAL_RED:BlockType::PORTAL_RED:BlockType::PORTAL_RED:";
					Position cursorPos = { 0,0 };
					for (int i = 0; i < _x; ++i)
					{
						cursorPos.x += 2;
					}
					for (int i = 0; i < _y; ++i)
					{
						cursorPos.y += 2;
					}
					state.player.SetPos(cursorPos, {_x, _y});
				}
			}
		}
		break;
	}
	case BlockType::BUTTON_RED:
	{
		ShakeConsoleWindow(15, 40, 25);
		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				if (state.map[y][x] == BlockType::LASERCORE_RED)
				{
					((LaserCore*)(state.blocks[y][x]))->ChangeDirection(state, Dir::UP);
					((LaserCore*)(state.blocks[y][x]))->Cast(state, x, y);
				}
			}
		}
		break;
	}

	}
	cout << state.player.GetMapPos().x << "," << state.player.GetMapPos().y;
}