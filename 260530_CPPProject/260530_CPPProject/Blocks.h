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
	SWITCHABLEBRICK_RED_OFF = 'w'
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

class RedButton : public Block
{
public:
	RedButton();
};

class Portal : public Block
{
public:
	Portal();
};

class SwitchableBrick : public Block
{
public:
	SwitchableBrick();
private:
	bool m_isActive;
public:
	bool GetIsActive();
	void Toggle(GameState& state);
};

Block* GenerateBlock(BlockType type);
bool IsPassable(Block* block, BlockType blockType);

