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
	EMPTY = 0,
	START = 1,
	BRICK = 2,

	LASERCORE = 3,
	LASERBEAM_VERTICAL = 4,
	LASERBEAM_HORIZONTAL = 5,

	PORTAL_RED_ENTER = 6,
	PORTAL_RED_EXIT = 7,
	
	BUTTON_RASERCORE = 8,
	//BUTTON_PORTAL = 9,

	BRICK_SWITCHABLE = 9,
};

class Block
{
protected:
	string m_image;
	Color m_color;
public:
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
	void Cast(GameState& state, int x, int y);
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

class PortalButton : public Block
{
public:
	PortalButton();
};

class PortalEnter : public Block
{
public:
	PortalEnter();
};

class PortalExit : public Block
{
public:
	PortalExit();
};

class SwitchableBrick : public Block
{
public:
	SwitchableBrick();
};

Block* GenerateBlock(BlockType type);

