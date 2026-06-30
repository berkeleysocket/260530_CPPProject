#include "Blocks.h"
#include "GameState.h"

	#pragma region Block
	Block::Block(BlockAffiliation affiliation)
	{
		m_affiliation = affiliation;
	}
	#pragma endregion

	#pragma region Empty Block
	EmptyBlock::EmptyBlock(BlockAffiliation affiliation) : Block(affiliation)
	{
		m_image = "  ";
		m_color = Color::WHITE;
		m_type = BlockType::EMPTY;
	}

	bool EmptyBlock::IsPassable(Actor& actor)
	{
		return true;
	}
	#pragma endregion

	#pragma region Brick
	Brick::Brick(BlockAffiliation affiliation) : Block(affiliation)
	{
		m_image = "¡á";
		m_color = Color::GRAY;
		m_type = BlockType::BRICK;
	}

	bool Brick::IsPassable(Actor& actor)
	{
		return false;
	}

	KillBrick::KillBrick(BlockAffiliation affiliation) : Block(affiliation)
	{
		m_image = "¢Ã";
		m_color = Color::LIGHT_VIOLET;
		m_type = BlockType::BRICK_KILL;
	}

	bool KillBrick::IsPassable(Actor& actor)
	{
		return false;
	}
	#pragma endregion

	#pragma region LaserCore
	LaserCore::LaserCore(BlockAffiliation affiliation, bool autoRotation, 
		bool isActive, Dir castingDir) : Block(affiliation)
	{
		m_image = "¡Ø";
		m_color = isActive ? Color::RED : Color::LIGHT_GRAY;
		m_type = BlockType::LASERCORE;
		m_isActive = isActive;
		m_autoRotation = autoRotation;
		m_dir = castingDir;
		m_beamPosQueue = queue<Position>();
	}

	void LaserCore::TryDrawCast(GameState& state)
	{
		if (!m_isActive) return;

		Position dir = DirToScreenPosition(m_dir);
		Position createLaserPos = m_position + dir;
		BlockType nextBlockType = BlockType::EMPTY;
		GenerateBlockType laserBeamType = GenerateBlockType::EMPTY;
		if (m_dir == Dir::UP)
			laserBeamType = GenerateBlockType::LASERBEAM_UP;
		else if (m_dir == Dir::DOWN)
			laserBeamType = GenerateBlockType::LASERBEAM_DOWN;
		else if (m_dir == Dir::RIGHT)
			laserBeamType = GenerateBlockType::LASERBEAM_RIGHT;
		else if (m_dir == Dir::LEFT)
			laserBeamType = GenerateBlockType::LASERBEAM_LEFT;

		while (!IsEdge(createLaserPos.x, createLaserPos.y))
		{
			nextBlockType = state.map[createLaserPos.y][createLaserPos.x]->GetType();

			if (nextBlockType == BlockType::SWITCHABLEBRICK)
			{
				SwitchableBrick* swBrick = (SwitchableBrick*)(state.map[createLaserPos.y][createLaserPos.x]);
				if (swBrick->GetIsActive())
					return;
				else
				{
					createLaserPos += dir;
					continue;
				}
			}
			else if (nextBlockType != BlockType::EMPTY && nextBlockType != BlockType::LASERBEAM)
				return;

			state.map[createLaserPos.y][createLaserPos.x] = GenerateBlock(laserBeamType);
			m_beamPosQueue.push({ createLaserPos.x, createLaserPos.y });

			createLaserPos += dir;
		};
	}

	void LaserCore::ChangeDirection(GameState& state)
	{
		if (!m_isActive) return;
		SoundManager::GetInst()->Play("Laser");

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
		Block* blockPtr = nullptr;

		while (!m_beamPosQueue.empty())
		{
			pos = m_beamPosQueue.front();

			blockPtr = state.map[pos.y][pos.x];
			blockPtr->SetType(BlockType::EMPTY);
			*blockPtr = *GenerateBlock(GenerateBlockType::EMPTY);
			m_beamPosQueue.pop();
		}
	}

	void LaserCore::Toggle(GameState& state)
	{
		m_isActive = !m_isActive;
		m_color = m_isActive ? Color::RED : Color::LIGHT_GRAY;

		Clear(state);

		if (m_isActive)
		{
			SoundManager::GetInst()->Play("Laser");
			TryDrawCast(state);
		}
	}

	void LaserCore::Interaction(GameState& state)
	{
		if (m_autoRotation)
			ChangeDirection(state);
		else
			Toggle(state);
	}

	bool LaserCore::IsPassable(Actor& actor)
	{
		return false;
	}
	#pragma endregion

	#pragma region LaserBeam
	LaserBeam::LaserBeam(BlockAffiliation affiliation, Dir beamDirection) : Block(affiliation)
	{
		switch (beamDirection)
		{
		case Dir::UP:
		{
			m_image = "¡è";
			break;
		}
		case Dir::DOWN:
		{
			m_image = "¡é";
			break;
		}
		case Dir::LEFT:
		{
			m_image = "¡ç";
			break;
		}
		case Dir::RIGHT:
		{
			m_image = "¡æ";
			break;
		}
		default:
		{
			m_image = "£¦";
			break;
		}
		}
		m_color = Color::RED;
		m_type = BlockType::LASERBEAM;
	}

	bool LaserBeam::IsPassable(Actor& actor)
	{
		return false;
	}
	#pragma endregion

	#pragma region Button
	Button::Button(BlockAffiliation affiliation) : Block(affiliation)
	{
		m_image = "¢Á";
		if (affiliation == BlockAffiliation::RED)
			m_color = Color::RED;
		else if (affiliation == BlockAffiliation::BLUE)
			m_color = Color::BLUE;
		else if (affiliation == BlockAffiliation::CLONE)
			m_color = Color::LIGHT_GREEN;
		m_type = BlockType::BUTTON;
	}

	void Button::Press(GameState& state)
	{
		SoundManager::GetInst()->Play("ButtonClick");
		Block* blockPtr = nullptr;
		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				blockPtr = state.map[y][x];
				IButtonInteractable* buttonInteractable = dynamic_cast<IButtonInteractable*>(blockPtr);

				if (buttonInteractable != nullptr 
					&& m_affiliation == blockPtr->GetAffiliation())
					buttonInteractable->Interaction(state);
			}
		}
	}

	bool Button::IsPassable(Actor& actor)
	{
		return false;
	}
	#pragma endregion

	#pragma region Portal
	Portal::Portal(BlockAffiliation affiliation) : Block(affiliation)
	{
		m_image = "£À";
		if (affiliation == BlockAffiliation::RED)
			m_color = Color::RED;
		else if (affiliation == BlockAffiliation::BLUE)
			m_color = Color::BLUE;
		else if (affiliation == BlockAffiliation::CLONE)
			m_color = Color::LIGHT_GREEN;
		m_type = BlockType::PORTAL;
	}

	void Portal::Warp(GameState& state, Actor& actor)
	{
		Block* blockPtr = nullptr;

		for (int _y = 0; _y < MAP_H; _y++)
		{
			for (int _x = 0; _x < MAP_W; _x++)
			{
				blockPtr = state.map[_y][_x];
				if (blockPtr->GetType() == m_type
					&& Position{ _x, _y } != m_position
					&& m_affiliation == blockPtr->GetAffiliation())
				{
					Position cursorPos = { 0,0 };
					cursorPos.x += _x * 2;
					cursorPos.y += _y;

					actor.SetPos(cursorPos, { _x, _y });
					SoundManager::GetInst()->Play("Teleport");
				}
			}
		}
	}

	bool Portal::IsPassable(Actor& actor)
	{
		return false;
	}
	#pragma endregion

	#pragma region SwitchableBrick
	SwitchableBrick::SwitchableBrick(BlockAffiliation affiliation,
		bool isActive) : Block(affiliation)
	{
		m_image = isActive ? "¡á" : "¡à";
		switch (affiliation)
		{
		case BlockAffiliation::RED:
		{
			m_color = Color::LIGHT_RED;
			break;
		}
		case BlockAffiliation::BLUE:
		{
			m_color = Color::LIGHT_BLUE;
			break;
		}
		case BlockAffiliation::CLONE:
		{
			m_color = Color::LIGHT_GREEN;
		}
		}
		m_isActive = isActive;
		m_type = BlockType::SWITCHABLEBRICK;
	}

	void SwitchableBrick::OnLaserBrickMode(GameState& state)
	{
		if (!m_isActive)
		{
			m_image = "¢Ì";
			//state.map[m_position.y][m_position.y] = BlockType::Sw
		}
	}

	void SwitchableBrick::OffLaserBrickMode(GameState& state)
	{
		m_image = m_isActive ? "¡á" : "¡à";
	}

	void SwitchableBrick::Toggle(GameState& state)
	{
		m_isActive = !m_isActive;

		if (m_isActive)
		{
			m_image = "¡á";
			SoundManager::GetInst()->Play("SwitchableBrick_ON");
		}
		else
		{
			m_image = "¡à";
			SoundManager::GetInst()->Play("SwitchableBrick_OFF");
		}

		BlockType blockType;
		Block* blockPtr = nullptr;

		for (int y = 0; y < MAP_H; ++y)
		{
			for (int x = 0; x < MAP_W; ++x)
			{
				blockPtr = state.map[y][x];
				blockType = blockPtr->GetType();
				if (blockType == BlockType::LASERCORE)
				{
					LaserCore* laserCore = ((LaserCore*)(blockPtr));
					laserCore->Clear(state);
					laserCore->TryDrawCast(state);
				}
			}
		}
	}

	void SwitchableBrick::Interaction(GameState& state)
	{
		Toggle(state);
	}

	bool SwitchableBrick::IsPassable(Actor& actor)
	{
		Player* player = dynamic_cast<Player*>(&actor);
		
		if (player != nullptr 
			&& m_affiliation == BlockAffiliation::CLONE)
			return false;

		return !m_isActive;
	}
	#pragma endregion

	#pragma region EndBlock
	EndBlock::EndBlock(BlockAffiliation affiliation) : Block(affiliation)
	{
		m_image = "¢Â";
		m_color = Color::YELLOW;
		m_type = BlockType::END;
	}

	bool EndBlock::IsPassable(Actor& actor)
	{
		return false;
	}
	#pragma endregion

	Block* GenerateBlock(GenerateBlockType type)
	{
		Block* block = nullptr;

		switch (type)
		{
		case GenerateBlockType::EMPTY:
		{
			block = new EmptyBlock(BlockAffiliation::NONE);
			break;
		}
		case GenerateBlockType::BRICK:
		{
			block = new Brick(BlockAffiliation::NONE);
			break;
		}
		case GenerateBlockType::START:
		{
			block = new EmptyBlock(BlockAffiliation::NONE);
			break;
		}
		case GenerateBlockType::END:
		{
			block = new EndBlock(BlockAffiliation::NONE);
			break;
		}
		case GenerateBlockType::LASERCORE_UP_AUTO:
		{
			block = new LaserCore(BlockAffiliation::RED, true, true, Dir::UP);
			break;
		}
		case GenerateBlockType::LASERCORE_UP_STATIC_ON:
		{
			block = new LaserCore(BlockAffiliation::RED, false, true, Dir::UP);
			break;
		}
		case GenerateBlockType::LASERCORE_UP_STATIC_OFF:
		{
			block = new LaserCore(BlockAffiliation::RED, false, false, Dir::UP);
			break;
		}
		case GenerateBlockType::LASERCORE_DOWN_AUTO:
		{
			block = new LaserCore(BlockAffiliation::RED, true, true, Dir::DOWN);
			break;
		}
		case GenerateBlockType::LASERCORE_DOWN_STATIC_ON:
		{
			block = new LaserCore(BlockAffiliation::RED, false, true, Dir::DOWN);
			break;
		}
		case GenerateBlockType::LASERCORE_DOWN_STATIC_OFF:
		{
			block = new LaserCore(BlockAffiliation::RED, false, false, Dir::DOWN);
			break;
		}
		case GenerateBlockType::LASERCORE_LEFT_AUTO:
		{
			block = new LaserCore(BlockAffiliation::RED, true, true, Dir::LEFT);
			break;
		}
		case GenerateBlockType::LASERCORE_LEFT_STATIC_ON:
		{
			block = new LaserCore(BlockAffiliation::RED, false, true, Dir::LEFT);
			break;
		}
		case GenerateBlockType::LASERCORE_LEFT_STATIC_OFF:
		{
			block = new LaserCore(BlockAffiliation::RED, false, false, Dir::LEFT);
			break;
		}
		case GenerateBlockType::LASERCORE_RIGHT_AUTO:
		{
			block = new LaserCore(BlockAffiliation::RED, true, true, Dir::RIGHT);
			break;
		}
		case GenerateBlockType::LASERCORE_RIGHT_STATIC_ON:
		{
			block = new LaserCore(BlockAffiliation::RED, false, true, Dir::RIGHT);
			break;
		}
		case GenerateBlockType::LASERCORE_RIGHT_STATIC_OFF:
		{
			block = new LaserCore(BlockAffiliation::RED, false, false, Dir::RIGHT);
			break;
		}
		case GenerateBlockType::LASERBEAM_UP:
		{
			block = new LaserBeam(BlockAffiliation::NONE, Dir::UP);
			break;
		}
		case GenerateBlockType::LASERBEAM_DOWN:
		{
			block = new LaserBeam(BlockAffiliation::NONE, Dir::DOWN);
			break;
		}
		case GenerateBlockType::LASERBEAM_RIGHT:
		{
			block = new LaserBeam(BlockAffiliation::NONE, Dir::RIGHT);
			break;
		}
		case GenerateBlockType::LASERBEAM_LEFT:
		{
			block = new LaserBeam(BlockAffiliation::NONE, Dir::LEFT);
			break;
		}
		case GenerateBlockType::PORTAL_RED:
		{
			block = new Portal(BlockAffiliation::RED);
			break;
		}
		case GenerateBlockType::PORTAL_BLUE:
		{
			block = new Portal(BlockAffiliation::BLUE);
			break;
		}
		case GenerateBlockType::BUTTON_RED:
		{
			block = new Button(BlockAffiliation::RED);
			break;
		}
		case GenerateBlockType::BUTTON_BLUE:
		{
			block = new Button(BlockAffiliation::BLUE);
			break;
		}
		case GenerateBlockType::BUTTON_CLONE:
		{
			block = new Button(BlockAffiliation::CLONE);
			break;
		}
		case GenerateBlockType::SWITCHABLEBRICK_RED_ON:
		{
			block = new SwitchableBrick(BlockAffiliation::RED, true);
			break;
		}
		case GenerateBlockType::SWITCHABLEBRICK_RED_OFF:
		{
			block = new SwitchableBrick(BlockAffiliation::RED, false);
			break;
		}
		case GenerateBlockType::SWITCHABLEBRICK_BLUE_ON:
		{
			block = new SwitchableBrick(BlockAffiliation::BLUE, true);
			break;
		}
		case GenerateBlockType::SWITCHABLEBRICK_BLUE_OFF:
		{
			block = new SwitchableBrick(BlockAffiliation::BLUE, false);
			break;
		}
		case GenerateBlockType::SWITCHABLEBRICK_CLONE_ON:
		{
			block = new SwitchableBrick(BlockAffiliation::CLONE, true);
			break;
		}
		case GenerateBlockType::SWITCHABLEBRICK_CLONE_OFF:
		{
			block = new SwitchableBrick(BlockAffiliation::CLONE, false);
			break;
		}
		case GenerateBlockType::BRICK_KILL:
		{
			block = new KillBrick(BlockAffiliation::NONE);
			break;
		}
		default:
			block = new EmptyBlock(BlockAffiliation::NONE);
			break;
		}
		return block;
	}