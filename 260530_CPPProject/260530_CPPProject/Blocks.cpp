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
	case BlockType::START:
	{
		block = new Empty();
		break;
	}
	case BlockType::LASERCORE_RED:
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
	case BlockType::PORTAL_RED:
	{
		block = new RedPortal();
		break;
	}
	case BlockType::PORTAL_BLUE:
	{
		block = new BluePortal();
		break;
	}
	case BlockType::BUTTOON_RED:
	{
		block = new RedButton();
		break;
	}
	case BlockType::BUTTON_BLUE:
	{
		block = new BlueButton();
		break;
	}
	case BlockType::SWITCHABLEBRICK_RED_ON:
	{
		block = new RedSwitchableBrick(true);
		break;
	}
	case BlockType::SWITCHABLEBRICK_RED_OFF:
	{
		block = new RedSwitchableBrick(false);
		break;
	}
	case BlockType::SWITCHABLEBRICK_BLUE_ON:
	{
		block = new BlueSwitchableBrick(true);
		break;
	}
	case BlockType::SWITCHABLEBRICK_BLUE_OFF:
	{
		block = new BlueSwitchableBrick(false);
		break;
	}
	default:
		block = new Empty();
		break;
	}

	return block;
}

bool IsPassable(Block* block, BlockType blockType)
{
	switch (blockType)
	{
	case BlockType::EMPTY:
	{
		return true;
		break;
	}
	case BlockType::SWITCHABLEBRICK_RED_ON:
	{
		return !(((RedSwitchableBrick*)(block))->GetIsActive());
		break;
	}
	default:
	{
		return false;
		break;
	}
	}
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

void LaserCore::TryDrawCast(GameState& state, int x, int y)
{
	Position dir = DirToMapPosition(m_dir);
	Position createLaserPos = { x + dir.x, y + dir.y };
	BlockType renderLaserType = dir.x != 0 ? BlockType::LASERBEAM_HORIZONTAL : BlockType::LASERBEAM_VERTICAL;
	BlockType& nextBlockType = state.map[createLaserPos.y][createLaserPos.x];

	while (!IsEdge(createLaserPos.x, createLaserPos.y))
	{
		BlockType nextBlockType = state.map[createLaserPos.y][createLaserPos.x];

		if (nextBlockType == BlockType::SWITCHABLEBRICK_RED_ON)
			return;
		else if (nextBlockType == BlockType::SWITCHABLEBRICK_RED_OFF)
		{
			createLaserPos += dir;
			continue;
		}

		if (nextBlockType != BlockType::EMPTY) return;

		state.map[createLaserPos.y][createLaserPos.x] = renderLaserType;
		state.blocks[createLaserPos.y][createLaserPos.x] = GenerateBlock(renderLaserType);
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
	BlockType empty = BlockType::EMPTY;
	BlockType switchableBlock = BlockType::SWITCHABLEBRICK_RED_ON;

	while (!m_beamPosQueue.empty())
	{
		pos = m_beamPosQueue.front();

		m_beamPosQueue.pop();

		if (state.map[pos.y][pos.x] == switchableBlock)
			continue;

		state.map[pos.y][pos.x] = empty;
		state.blocks[pos.y][pos.x] = GenerateBlock(empty);
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
RedButton::RedButton() 
{
	m_image = "¢Á";
	m_color = Color::RED;
}

void RedButton::Press(GameState& state)
{
	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			if (state.map[y][x] == BlockType::SWITCHABLEBRICK_RED_ON
				|| state.map[y][x] == BlockType::SWITCHABLEBRICK_RED_OFF)
			{
				RedSwitchableBrick* switchableBrick = (RedSwitchableBrick*)(state.blocks[y][x]);
				switchableBrick->Toggle(state);
			}
			else if (state.map[y][x] == BlockType::LASERCORE_RED)
			{
				LaserCore* laserCore = (LaserCore*)(state.blocks[y][x]);
				laserCore->ChangeDirection(state, Dir::UP);
				laserCore->TryDrawCast(state, x, y);
			}

		}
	}
}

BlueButton::BlueButton()
{
	m_image = "¢Á";
	m_color = Color::BLUE;
}

void BlueButton::Press(GameState& state)
{
	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			if (state.map[y][x] == BlockType::SWITCHABLEBRICK_BLUE_ON
				|| state.map[y][x] == BlockType::SWITCHABLEBRICK_BLUE_OFF)
			{
				BlueSwitchableBrick* switchableBrick = (BlueSwitchableBrick*)(state.blocks[y][x]);
				switchableBrick->Toggle(state);
			}
			//else if (state.map[y][x] == BlockType::LASERCORE_)
			//{
			//	LaserCore* laserCore = (LaserCore*)(state.blocks[y][x]);
			//	laserCore->ChangeDirection(state, Dir::UP);
			//	laserCore->TryDrawCast(state, x, y);
			//}
		}
	}
}
#pragma endregion

#pragma region Portal
RedPortal::RedPortal() 
{
	m_image = "£À";
	m_color = Color::LIGHT_RED;
}

BluePortal::BluePortal()
{
	m_image = "£À";
	m_color = Color::LIGHT_BLUE;
}
#pragma endregion

#pragma region SwitchableBrick
RedSwitchableBrick::RedSwitchableBrick(bool isActive)
{
	m_image = isActive ? "¡á" : "¡à";
	m_color = Color::LIGHT_RED;
	m_isActive = isActive;
}

bool RedSwitchableBrick::GetIsActive()
{
	return m_isActive;
}

void RedSwitchableBrick::Toggle(GameState& state)
{
	m_isActive = !m_isActive;

	if (m_isActive)
	{
		state.map[m_position.y][m_position.x] = BlockType::SWITCHABLEBRICK_RED_ON;

		m_image = "¡á";
	}
	else
	{
		state.map[m_position.y][m_position.x] = BlockType::SWITCHABLEBRICK_RED_OFF;
		m_image = "¡à";
	}
}

BlueSwitchableBrick::BlueSwitchableBrick(bool isActive)
{
	m_image = isActive ? "¡á" : "¡à";
	m_color = Color::LIGHT_BLUE;
	m_isActive = isActive;
}

bool BlueSwitchableBrick::GetIsActive()
{
	return m_isActive;
}

void BlueSwitchableBrick::Toggle(GameState& state)
{
	m_isActive = !m_isActive;

	if (m_isActive)
	{
		state.map[m_position.y][m_position.x] = BlockType::SWITCHABLEBRICK_BLUE_ON;
		m_image = "¡á";
	}
	else
	{
		state.map[m_position.y][m_position.x] = BlockType::SWITCHABLEBRICK_BLUE_OFF;
		m_image = "¡à";
	}
}
#pragma endregion


