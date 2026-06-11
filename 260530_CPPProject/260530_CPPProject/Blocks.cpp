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
		block = LaserCore();
		break;
	}
	case BlockType::LASER_VERTICAL:
	{
		break;
	}
	case BlockType::LASER_HORIZONTAL:
	{
		break;
	}
	}

	return block;
}