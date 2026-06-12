#include "InGameScene.h"

void LoadMap(GameState& state, const string gameMap[MAP_H])
{
	for (int y = 0; y < MAP_H; ++y)
	{ 
		for (int x = 0; x < MAP_W; ++x)
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
		HandleBlockInteraction(state, nextBlock);
		return false;
	}

	return true;
}

void HandleBlockInteraction(GameState& state, BlockType block)
{
	switch (block)
	{
	case BlockType::BRICK:
	{
		break;
	}
	case BlockType::LASERCORE_RED:
	case BlockType::LASERCORE_BLUE:
	{
		break;
	}
	case BlockType::LASERBEAM_HORIZONTAL:
	case BlockType::LASERBEAM_VERTICAL:
	{
		break;
	}
	}
}