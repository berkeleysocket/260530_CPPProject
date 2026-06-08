//#include "InGameScene.h"
//
//void LoadMap(GameState& state, const string gameMap[MAP_H])
//{
//	for (int y = 0; y < MAP_H; ++y)
//	{ 
//		for (int x = 0; x < MAP_W; ++x)
//		{
//			int data = gameMap[y][x] - '0';
//			state.map[y][x] = (BlockType)data;
//			state.blocks[y][x] = 
//			if (state.map[y][x] == BlockType::START)
//			{
//				//state.player.pos = { x,y };
//				state.map[y][x] = BlockType::EMPTY;
//			}
//		}
//	}
//}
//
//void DrawMap(const GameState& state)
//{
//	for (int y = 0; y < MAP_H; ++y)
//	{
//		for (int x = 0; x < MAP_W; ++x)
//		{
//			if (TryDrawPlayer(state, x, y))
//				continue;
//			DrawBlock(state, x, y);
//		}
//		cout << endl;
//	}
//	SetColor();
//}
//
//void DrawBlock(GameState& state, int x, int y)
//{
//	switch (state.map[y][x])
//	{
//	case BlockType::EMPTY:
//	{
//		SetColor();
//		cout << "  ";
//		break;
//	}
//	case BlockType::BRICK:
//	{
//		SetColor(Color::GRAY);
//		//string player = state.player.image;
//		//cout << player;
//		cout << "бс";
//		break;
//	}
//	case BlockType::LASER_L:
//	{
//		int nx = x - 1;
//		int ny = y;
//
//		while (!IsEdge(nx, ny) && state.map[nx][ny] == BlockType::EMPTY)
//		{
//			state.map[nx][ny] = BlockType::LASER_L;
//		}
//		break;
//	}
//	case BlockType::LASER_R:
//	{
//		break;
//	}
//	case BlockType::LASER_U:
//	{
//		break;
//	}
//	case BlockType::LASER_D:
//	{
//		break;
//	}
//	}
//}
//
//bool IsEdge(int x, int y)
//{
//	return x < 0 || y < 0 ||
//		x >= MAP_W || y >= MAP_H;
//}
//
//bool TryDrawPlayer(const GameState& state, int x, int y)
//{
//	if (state.player.GetPos() == Position{x,y})
//	{
//		SetColor(Color::LIGHT_YELLOW);
//		cout << "б╫";
//		return true;
//	}
//	return false;
//}
//
//bool TryPlayerMove(GameState& state, Position dir)
//{
//    if (dir == Position{ 0,0 })
//        return;
//	
//	Player& player = state.player;
//
//    Position next =
//    {
//       std::clamp(player.GetPos().x + dir.x, 0, MAP_W - 1),
//       std::clamp(player.GetPos().y + dir.y, 0, MAP_H - 1)
//    };
//	BlockType nextBlock = state.map[next.x][next.y];
//	if (nextBlock != BlockType::EMPTY)
//	{
//		HandleBlockInteraction(state, nextBlock);
//		return false;
//	}
//
//	return true;
//}
//
//void HandleBlockInteraction(GameState& state, BlockType block)
//{
//	switch (block)
//	{
//	case BlockType::BRICK:
//	{
//		break;
//	}
//	case BlockType::LASER_L:
//	case BlockType::LASER_R:
//	case BlockType::LASER_U:
//	case BlockType::LASER_D:
//	{
//		break;
//	}
//	}
//}