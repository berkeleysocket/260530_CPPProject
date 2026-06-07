#include "InGameScene.h"

void LoadMap(GameState& state, const string gameMap[MAP_H])
{
	for (int y = 0; y < MAP_H; ++y)
	{ 
		for (int x = 0; x < MAP_W; ++x)
		{
			int data = gameMap[y][x] - '0';
			state.map[y][x] = (Block)data;
			if (state.map[y][x] == Block::START)
			{
				//state.player.pos = { x,y };
				state.map[y][x] = Block::EMPTY;
			}
		}
	}
}

void DrawMap(const GameState& state)
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

void DrawBlock(const GameState& state, int x, int y)
{
	switch (state.map[y][x])
	{
	case Block::BRICK:
		SetColor(Color::GRAY);
		cout << "■";
		break;
	case Block::EMPTY:
		SetColor();
		cout << "  ";
		break;
	case Block::LASER:
	{
		//ULONGLONG elapsed = 0;
		//for (const Bomb& bom : state.vecBombs)
		//{
		//	if (bom.active && bom.pos == Position{ x,y })
		//	{
		//		elapsed = state.curTime - bom.startTime;
		//		break;
		//	}
		//}
		//SetColor(Color::LIGHT_VIOLET);
		//cout << (elapsed / BOMB_BLINK_INTERVAL_MS % 2 == 0 ? "◐" : "◑"); // 
	}
	break;
	}
}

bool IsEdge(int x, int y)
{
	return x >= 0 && y >= 0 &&
		x >= MAP_W && y >= MAP_H;
}

bool TryDrawPlayer(const GameState& state, int x, int y)
{
	if (state.player.GetPos() == Position{x,y})
	{
		// 플레이어
		SetColor(Color::LIGHT_YELLOW);
		cout << "§";
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
	Block nextBlock = state.map[next.x][next.y];
	if (nextBlock != Block::EMPTY)
	{
		HandleBlockInteraction(state, nextBlock);
		return false;
	}

	return true;
}

void HandleBlockInteraction(GameState& state, Block block)
{
	switch (block)
	{
	case Block::BRICK:
	{

	}
	case Block::LASER:
		{

		}
	}
}