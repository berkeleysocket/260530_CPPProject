#include "Blocks.h"

Block* GenerateBlock(BlockType type)
{
	Block* block = nullptr;

	switch (type)
	{
	case BlockType::EMPTY:
	{
		block = new Empty();
		break;
	}
	case BlockType::BRICK:
	{
		block = new Brick();
		break;
	}
	case BlockType::LASERCORE:
	{
		block = new LaserCore(Dir::DOWN);
		break;
	}
	case BlockType::LASER_VERTICAL:
	{
		block = new VerticalLaser();
		break;
	}
	case BlockType::LASER_HORIZONTAL:
	{
		block = new HorizontalLaser();
		break;
	}
	default:
		block = new Empty();
		break;
	}

	return block;
}