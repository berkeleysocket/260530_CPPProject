#include "Blocks.h"
#include "GameState.h"

#include <iostream>

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
	case BlockType::LASERCORE_RED:
	case BlockType::LASERCORE_BLUE:
	{
		block = new LaserCore(Dir::DOWN);
		break;
	}
	case BlockType::LASERBEAM_VERTICAL:
	{
		block = new VerticalLaser();
		break;
	}
	case BlockType::LASERBEAM_HORIZONTAL:
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

const string Block::GetImage() const
{
	return m_image;
}
const Color Block::GetColor() const
{
	return m_color;
}

#pragma region Empty
Empty::Empty()
{
	m_image = "  ";
	m_color = Color::WHITE;
}
#pragma endregion

#pragma region Brick
Brick::Brick()
{
	m_image = "¡á";
	m_color = Color::GRAY;
}
#pragma endregion

#pragma region LaserCore
LaserCore::LaserCore()
{
	m_dir = Dir::UP;
	m_image = "¡Ø";
	m_color = Color::LIGHT_GRAY;
	m_beamPosQueue = queue<Position>();
}

LaserCore::LaserCore(Dir castingDir)
{
	m_dir = castingDir;
	m_image = "¡Ø";
	m_color = Color::LIGHT_GRAY;
}

void LaserCore::Cast(GameState& state, int x, int y)
{
	Position dir = DirToMapPosition(m_dir);
	Position createLaserPos = { x + dir.x, y + dir.y };
	BlockType castingLaserT = dir.x != 0 ? BlockType::LASERBEAM_HORIZONTAL : BlockType::LASERBEAM_VERTICAL;

	while (!IsEdge(createLaserPos.x, createLaserPos.y)
		&& state.map[createLaserPos.y][createLaserPos.x] == BlockType::EMPTY)
	{
		state.map[createLaserPos.y][createLaserPos.x] = castingLaserT;
		state.blocks[createLaserPos.y][createLaserPos.x] = GenerateBlock(castingLaserT);
		m_beamPosQueue.push({ createLaserPos.x, createLaserPos.y });
		createLaserPos += dir;
	}
}

void LaserCore::ChangeDirection(GameState& state, Dir dir)
{

}

const Dir LaserCore::GetBeamDirection() const
{
	return m_dir;
}
#pragma endregion

#pragma region LaserBeam
HorizontalLaser::HorizontalLaser()
{
	m_image = "¡æ";
	m_color = Color::LIGHT_RED;
}

VerticalLaser::VerticalLaser()
{
	m_image = "¡è";
	m_color = Color::LIGHT_RED;
}
#pragma endregion

