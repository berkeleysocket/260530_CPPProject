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
	LASERCORE_RED = 3,
	LASERCORE_BLUE = 4,
	LASERBEAM_VERTICAL = 5,
	LASERBEAM_HORIZONTAL = 6,
	PORTAL_RED = 7,
	PORTAL_BLUE = 8
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

Block* GenerateBlock(BlockType type);

