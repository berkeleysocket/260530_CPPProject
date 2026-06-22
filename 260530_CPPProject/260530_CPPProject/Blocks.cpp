#include "Blocks.h"
#include "GameState.h"

	#pragma region Block
	const string Block::GetImage() const
	{
		return m_image;
	}
	const Color Block::GetColor() const
	{
		return m_color;
	}
	#pragma endregion

	#pragma region Empty Block
	EmptyBlock::EmptyBlock()
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
	LaserCore::LaserCore(bool autoRotation, Dir castingDir)
	{
		m_image = "¡Ø";
		m_color = Color::RED;
		m_isActive = true;	
		m_autoRotation = autoRotation;
		m_dir = castingDir;
		m_beamPosQueue = queue<Position>();
	}

	void LaserCore::TryDrawCast(GameState& state)
	{
		if (!m_isActive) return;

		Position dir = DirToMapPosition(m_dir);
		Position createLaserPos = m_position + dir;
		BlockType laserBeamType = BlockType::EMPTY;
		if (m_dir == Dir::UP)
			laserBeamType = BlockType::LASERBEAM_UP;
		else if (m_dir == Dir::DOWN)
			laserBeamType = BlockType::LASERBEAM_DOWN;
		else if (m_dir == Dir::RIGHT)
			laserBeamType = BlockType::LASERBEAM_RIGHT;
		else if (m_dir == Dir::LEFT)
			laserBeamType = BlockType::LASERBEAM_LEFT;

		while (!IsEdge(createLaserPos.x, createLaserPos.y))
		{
			BlockType nextBlockType = state.map[createLaserPos.y][createLaserPos.x];

			if (nextBlockType == BlockType::SWITCHABLEBRICK_RED_ON
				|| nextBlockType == BlockType::SWITCHABLEBRICK_BLUE_ON)
				return;
			else if (nextBlockType == BlockType::SWITCHABLEBRICK_RED_OFF
				|| nextBlockType == BlockType::SWITCHABLEBRICK_BLUE_OFF)
			{
				createLaserPos += dir;	
				continue;
			}

			if (nextBlockType != BlockType::EMPTY 
				&& nextBlockType != BlockType::LASERBEAM_UP
				&& nextBlockType != BlockType::LASERBEAM_DOWN
				&& nextBlockType != BlockType::LASERBEAM_RIGHT
				&& nextBlockType != BlockType::LASERBEAM_LEFT)
				return;

			state.map[createLaserPos.y][createLaserPos.x] = laserBeamType;
			state.blocks[createLaserPos.y][createLaserPos.x] = GenerateBlock(laserBeamType);
			m_beamPosQueue.push({ createLaserPos.x, createLaserPos.y });

			createLaserPos += dir;
		}
	}

	void LaserCore::ChangeDirection(GameState& state)
	{
		if (!m_isActive) return;

		if (m_autoRotation)
		{
			switch (m_dir)
			{
			case Dir::UP:
			{
				m_dir = Dir::RIGHT;
				break;
			}
			case Dir::DOWN:
			{
				m_dir = Dir::LEFT;
				break;
			}
			case Dir::LEFT:
			{
				m_dir = Dir::UP;
				break;
			}
			case Dir::RIGHT:
			{
				m_dir = Dir::DOWN;
				break;
			}
			}
		}

		Clear(state);
		TryDrawCast(state);
	}

	void LaserCore::Clear(GameState& state)
	{
		Position pos{ 0,0 };
		BlockType empty = BlockType::EMPTY;

		while (!m_beamPosQueue.empty())
		{
			pos = m_beamPosQueue.front();
			m_beamPosQueue.pop();

			state.map[pos.y][pos.x] = empty;
			state.blocks[pos.y][pos.x] = GenerateBlock(empty);
		}
	}

	void LaserCore::Toggle(GameState& state)
	{
		m_isActive = !m_isActive;
		m_color = m_isActive ? Color::RED : Color::LIGHT_GRAY;

		Clear(state);

		if(m_isActive)
			TryDrawCast(state);
	}

	const Dir LaserCore::GetBeamDirection() const
	{
		return m_dir;
	}
	#pragma endregion

	#pragma region LaserBeam
	LaserBeamUp::LaserBeamUp()
	{
		m_image = "¡è";
		m_color = Color::RED;
	}

	LaserBeamDown::LaserBeamDown()
	{
		m_image = "¡é";
		m_color = Color::RED;
	}

	LaserBeamRight::LaserBeamRight()
	{
		m_image = "¡æ";
		m_color = Color::RED;
	}

	LaserBeamLeft::LaserBeamLeft()
	{
		m_image = "¡ç";
		m_color = Color::RED;
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
		BlockType blockType;
		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				blockType = state.map[y][x];
				if (blockType == BlockType::SWITCHABLEBRICK_RED_ON
					|| blockType == BlockType::SWITCHABLEBRICK_RED_OFF)
				{
					((RedSwitchableBrick*)(state.blocks[y][x]))->Toggle(state);
				}
				else if (blockType == BlockType::LASERCORE_UP_AUTO
					|| blockType == BlockType::LASERCORE_DOWN_AUTO
					|| blockType == BlockType::LASERCORE_LEFT_AUTO
					|| blockType == BlockType::LASERCORE_RIGHT_AUTO)
				{
					((LaserCore*)(state.blocks[y][x]))->ChangeDirection(state);
				}
				else if (blockType == BlockType::LASERCORE_UP_STATIC
					|| blockType == BlockType::LASERCORE_DOWN_STATIC
					|| blockType == BlockType::LASERCORE_LEFT_STATIC
					|| blockType == BlockType::LASERCORE_RIGHT_STATIC)
				{
					((LaserCore*)(state.blocks[y][x]))->Toggle(state);
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
		BlockType blockType;
		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				blockType = state.map[y][x];
				if (blockType == BlockType::SWITCHABLEBRICK_BLUE_ON
					|| blockType == BlockType::SWITCHABLEBRICK_BLUE_OFF)
				{
					((BlueSwitchableBrick*)(state.blocks[y][x]))->Toggle(state);
				}
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

		BlockType blockType;
		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				blockType = state.map[y][x];
				if (blockType == BlockType::LASERCORE_UP_AUTO
					|| blockType == BlockType::LASERCORE_DOWN_AUTO
					|| blockType == BlockType::LASERCORE_LEFT_AUTO
					|| blockType == BlockType::LASERCORE_RIGHT_AUTO)
				{
					LaserCore* laserCore = ((LaserCore*)(state.blocks[y][x]));
					((LaserCore*)(state.blocks[y][x]))->Clear(state);
					((LaserCore*)(state.blocks[y][x]))->TryDrawCast(state);
				}
				else if (blockType == BlockType::LASERCORE_UP_STATIC
					|| blockType == BlockType::LASERCORE_DOWN_STATIC
					|| blockType == BlockType::LASERCORE_LEFT_STATIC
					|| blockType == BlockType::LASERCORE_RIGHT_STATIC)
				{
					LaserCore* laserCore = ((LaserCore*)(state.blocks[y][x]));
					((LaserCore*)(state.blocks[y][x]))->Clear(state);
					((LaserCore*)(state.blocks[y][x]))->TryDrawCast(state);
				}
			}
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

		BlockType blockType;
		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				blockType = state.map[y][x];
				if (blockType == BlockType::LASERCORE_UP_AUTO
					|| blockType == BlockType::LASERCORE_DOWN_AUTO
					|| blockType == BlockType::LASERCORE_LEFT_AUTO
					|| blockType == BlockType::LASERCORE_RIGHT_AUTO)
				{
					LaserCore* laserCore = (LaserCore*)(state.blocks[y][x]);
					laserCore->Clear(state);
					laserCore->TryDrawCast(state);
				}
				else if (blockType == BlockType::LASERCORE_UP_STATIC
					|| blockType == BlockType::LASERCORE_DOWN_STATIC
					|| blockType == BlockType::LASERCORE_LEFT_STATIC
					|| blockType == BlockType::LASERCORE_RIGHT_STATIC)
				{
					LaserCore* laserCore = (LaserCore*)(state.blocks[y][x]);
					laserCore->Clear(state);
					laserCore->TryDrawCast(state);
				}
			}
		}
	}
	#pragma endregion

	#pragma region EndBlock
	EndBlock::EndBlock()
	{
		m_image = "¢Â";
		m_color = Color::YELLOW;
	}
	#pragma endregion

	Block* GenerateBlock(BlockType type)
	{
		Block* block = nullptr;

		switch (type)
		{
		case BlockType::EMPTY:
		{
			block = new EmptyBlock();
			break;
		}
		case BlockType::BRICK:
		{
			block = new Brick();
			break;
		}
		case BlockType::START:
		{
			block = new EmptyBlock();
			break;
		}
		case BlockType::END:
		{
			block = new EndBlock();
			break;
		}
		case BlockType::LASERCORE_UP_AUTO:
		{
			block = new LaserCore(true, Dir::UP);
			break;
		}
		case BlockType::LASERCORE_UP_STATIC:
		{
			block = new LaserCore(false, Dir::UP);
			break;
		}
		case BlockType::LASERCORE_DOWN_AUTO:
		{
			block = new LaserCore(true, Dir::DOWN);
			break;
		}
		case BlockType::LASERCORE_DOWN_STATIC:
		{
			block = new LaserCore(false, Dir::DOWN);
			break;
		}
		case BlockType::LASERCORE_LEFT_AUTO:
		{
			block = new LaserCore(true, Dir::LEFT);
			break;
		}
		case BlockType::LASERCORE_LEFT_STATIC:
		{
			block = new LaserCore(false, Dir::LEFT);
			break;
		}
		case BlockType::LASERCORE_RIGHT_AUTO:
		{
			block = new LaserCore(true, Dir::RIGHT);
			break;
		}
		case BlockType::LASERCORE_RIGHT_STATIC:
		{
			block = new LaserCore(false, Dir::RIGHT);
			break;
		}
		case BlockType::LASERBEAM_UP:
		{
			block = new LaserBeamUp();
			break;
		}
		case BlockType::LASERBEAM_DOWN:
		{
			block = new LaserBeamDown();
			break;
		}
		case BlockType::LASERBEAM_RIGHT:
		{
			block = new LaserBeamRight();
			break;
		}
		case BlockType::LASERBEAM_LEFT:
		{
			block = new LaserBeamLeft();
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
		case BlockType::BUTTON_RED:
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
			block = new EmptyBlock();
			break;
		}

		return block;
	}
	bool IsPassable(Block* block, BlockType blockType)
	{
		switch (blockType)
		{
		case BlockType::EMPTY:
		case BlockType::SWITCHABLEBRICK_RED_OFF:
		case BlockType::SWITCHABLEBRICK_BLUE_OFF:
		{
			return true;
			break;
		}
		default:
		{
			return false;
			break;
		}
		}
	}