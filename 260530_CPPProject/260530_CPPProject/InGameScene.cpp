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

bool TryPlayerMove(GameState& state, Position)
{
	Player& player = state.player;
}


