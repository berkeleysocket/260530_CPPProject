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
	case BlockType::LASERCORE:
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
	case BlockType::PORTAL_RED_ENTER:
	{
		block = new PortalEnter();
		break;
	}
	case BlockType::PORTAL_RED_EXIT:
	{
		block = new PortalExit();
		break;
	}
	{
		block = new PortalEnter();
		break;
	}
	case BlockType::BUTTON_RASERCORE:
	{
		block = new PortalButton();
		break;
	}
	case BlockType::BRICK_SWITCHABLE:
	{
		block = new SwitchableBrick();
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
	m_beamPosQueue = queue<Position>();
	m_image = "¡Ø";
	m_color = Color::LIGHT_GRAY;
}

void LaserCore::Cast(GameState& state, int x, int y)
{
	Position dir = DirToCursorPosition(m_dir);
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
	//m_dir = dir;
	if (m_dir == Dir::UP)
		m_dir = Dir::RIGHT;
	else if (m_dir == Dir::RIGHT)
		m_dir = Dir::DOWN;
	else if (m_dir == Dir::DOWN)
		m_dir = Dir::LEFT;
	else if (m_dir == Dir::LEFT)
		m_dir = Dir::UP;

	Position pos { 0,0 };
	int x(0);
	int y(0);
	BlockType empty = BlockType::EMPTY;

	while (!m_beamPosQueue.empty())
	{
		pos = m_beamPosQueue.front();

		m_beamPosQueue.pop();

		x = pos.x;
		y = pos.y;

		state.map[y][x] = empty;
		state.blocks[y][x] = GenerateBlock(empty);
	}
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

#pragma region Button
PortalButton::PortalButton() 
{
	m_image = "¡Ü";
	m_color = Color::RED;
}
#pragma endregion

#pragma region Portal
PortalEnter::PortalEnter() 
{
	m_image = "£À";
	m_color = Color::LIGHT_VIOLET;
}

PortalExit::PortalExit()
{
	m_image = "£À";
	m_color = Color::LIGHT_VIOLET;
}
#pragma endregion

#pragma region SwitchableBrick
SwitchableBrick::SwitchableBrick()
{
	m_image = "¡á";
	m_color = Color::LIGHT_RED;
}
#pragma endregion


