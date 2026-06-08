#pragma once
class Block
{
private:
	Position position;
	string image;
public:
	const Position GetPos() const
	{
		return position;
	}
	const string GetImage() const
	{
		return image;
	}
};

class Empty : Block
{

};

class Brick : Block
{

};

class Laser : Block
{
private:
	Position dir;

	const Position GetDirection() const
	{
		return dir;
	}
};

