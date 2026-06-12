#include "Blocks.h"

Block GenerateBlock(BlockType type)
{
	Block block;

	switch (type)
	{
	case BlockType::EMPTY:
	{
		block = Empty();
		break;
	}
	case BlockType::BRICK:
	{
		block = Brick();
		break;
	}
	case BlockType::LASERCORE:
	{
		block = LaserCore(Position{0,-1});
		break;
	}
	case BlockType::LASER_VERTICAL:
	{
		block = VerticalLaser();
		break;
	}
	case BlockType::LASER_HORIZONTAL:
	{
		block = HorizontalLaser();
		break;
	}
	}

	return block;
}