#pragma once
#include <string>
#include <queue>
#include "Position.h"
#include "Dir.h"
#include "Color.h"

using std::string;
using std::queue;

struct GameState;

enum class BlockType
{
	EMPTY = '.',
	START = 'S',
	BRICK = '0',

	LASERCORE_RED = 'L',
	LASERBEAM_VERTICAL = 'V',
	LASERBEAM_HORIZONTAL = 'H',

	PORTAL_RED = 'P',
	PORTAL_BLUE = 'p',
	
	BUTTOON_RED = 'B',
	BUTTON_BLUE = 'b',

	SWITCHABLEBRICK_RED_ON = 'W',
	SWITCHABLEBRICK_RED_OFF = 'w',
	SWITCHABLEBRICK_BLUE_ON = 'E',
	SWITCHABLEBRICK_BLUE_OFF = 'e',
};

class Block
{
protected:
	string m_image;
	Color m_color;
public:
	Position m_position;
	const string GetImage() const;
	const Color GetColor() const;
};

class Empty : public Block
{
public:
	Empty();
};

class Brick : public Block
{
public:
	Brick();
};

#pragma region Laser
class LaserCore : public Block
{
private:
	Dir m_dir;
	queue<Position> m_beamPosQueue;

public:
	LaserCore();
	LaserCore(Dir castingDir);
	void TryDrawCast(GameState& state, int x, int y);
	void ChangeDirection(GameState& state, Dir dir);
	const Dir GetBeamDirection() const;
};

class HorizontalLaser : public Block
{
public:
	HorizontalLaser();
};

class VerticalLaser : public Block
{
public:
	VerticalLaser();
};
#pragma endregion

#pragma region Button
class RedButton : public Block
{
public:
	RedButton();
public:
	void Press(GameState& state);
};

class BlueButton : public Block
{
public:
	BlueButton();
public:
	void Press(GameState& state);
};
#pragma endregion

#pragma region Portal
class RedPortal : public Block
{
public:
	RedPortal();
};
class BluePortal : public Block
{
public:
	BluePortal();
};
#pragma endregion

#pragma region SwitchableBrick
class RedSwitchableBrick : public Block
{
public:
	RedSwitchableBrick(bool isActive);
private:
	bool m_isActive;
public:
	bool GetIsActive();
	void Toggle(GameState& state);
};

class BlueSwitchableBrick : public Block
{
public:
	BlueSwitchableBrick(bool isActive);
private:
	bool m_isActive;
public:
	bool GetIsActive();
	void Toggle(GameState& state);
};
#pragma endregion



Block* GenerateBlock(BlockType type);
bool IsPassable(Block* block, BlockType blockType);

