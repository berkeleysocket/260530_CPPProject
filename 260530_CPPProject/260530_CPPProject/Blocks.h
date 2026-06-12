#pragma once
#include <string>
#include "Position.h"
#include "Dir.h"
#include "Color.h"

using std::string;

enum class BlockType
{
	EMPTY = 0,
	START = 1,
	BRICK = 2,
	LASERCORE = 3,
	LASER_VERTICAL = 4,
	LASER_HORIZONTAL = 5,
	PORTAL_ONE = 6,
	PORTAL_TWO = 7
};

class Block
{
protected:
	//Position position;
	string image;
	Color color;
public:
	//const Position GetPos() const
	//{
	//	return position;
	//}
	const string GetImage() const
	{
		return image;
	}
	const Color GetColor() const
	{
		return color;
	}
};

class Empty : public Block
{
public:
	Empty()
	{
		image = "  ";
		color = Color::WHITE;
	}
};

class Brick : public Block
{
public:
	Brick()
	{
		image = "¡á";
		color = Color::GRAY;
	}
};

class LaserCore : public Block
{
private:
	Position dir;

public:
	LaserCore()
	{
		dir = {0,0};
		image = "¡Ø";
		color = Color::LIGHT_GRAY;
	}
	LaserCore(Dir dir)
	{
		dir = castingDir;
		image = "¡Ø";
		color = Color::LIGHT_GRAY;
	}
	const Position GetDir() const
	{
		return dir;
	}
};

class HorizontalLaser : public Block
{
public:
	HorizontalLaser()
	{
		image = "¡æ";
		color = Color::LIGHT_RED;
	}
};

class VerticalLaser : public Block
{
public:
	VerticalLaser()
	{
		image = "¡è";
		color = Color::LIGHT_RED;
	}
};

Block* GenerateBlock(BlockType type);

