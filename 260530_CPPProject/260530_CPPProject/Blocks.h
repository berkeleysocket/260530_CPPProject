#pragma once
#include <string>
#include "Position.h"
#include "Color.h"

using std::string;

enum class BlockType
{
	EMPTY = 0,
	START = 1,
	BRICK = 2,
	LASERCORE = 3,
	LASER_VERTICAL = 4,
	LASER_HORIZONTAL = 5
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
		image = "бс";
		color = Color::GRAY;
	}
};

class LaserCore : public Block
{
private:
	Position dir;

public:
	const Position GetDir() const
	{
		return dir;
	}
};

Block GenerateBlock(BlockType type);

