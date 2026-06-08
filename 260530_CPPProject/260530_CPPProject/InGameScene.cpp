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
	Block& block = state.blocks[y][x];

	switch (state.map[y][x])
	{
	case BlockType::EMPTY:
	case BlockType::BRICK:
	case BlockType::LASER_HORIZONTAL:
	case BlockType::LASER_VERTICAL:
	{
		break;
	}
	case BlockType::LASERCORE:
	{
		Position pos = (((LaserCore&)block).GetDir());
		Position nPos = { pos.x, pos.y };

		BlockType blockT = nPos.x != 0 ? BlockType::LASER_HORIZONTAL : BlockType::LASER_VERTICAL;
		while (!IsEdge(nPos.x, nPos.y) && state.map[nPos.y][nPos.x] == BlockType::EMPTY)
		{
			state.map[nPos.y][nPos.x] = blockT;
			nPos += pos;
		}
		break;
	}
	}

	SetColor(block.GetColor());
	cout << block.GetImage();
}

bool IsEdge(int x, int y)
{
	return x < 0 || y < 0 ||
		x >= MAP_W || y >= MAP_H;
}

bool TryDrawPlayer(const GameState& state, int x, int y)
{
	if (state.player.GetPos() == Position{x,y})
	{
		SetColor(Color::LIGHT_YELLOW);
		cout << "¡×";
		return true;
	}
	return false;
}

bool TryPlayerMove(GameState& state, Position dir)
{
    if (dir == Position{ 0,0 })
        return;
	
	Player& player = state.player;

    Position next =
    {
       std::clamp(player.GetPos().x + dir.x, 0, MAP_W - 1),
       std::clamp(player.GetPos().y + dir.y, 0, MAP_H - 1)
    };
	BlockType nextBlock = state.map[next.x][next.y];
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
	case BlockType::LASERCORE:
	{
		break;
	}
	case BlockType::LASER_HORIZONTAL:
	case BlockType::LASER_VERTICAL:
	{
		break;
	}
	}
}