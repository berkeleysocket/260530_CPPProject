#pragma once
struct Position
{
	int x;
	int y;

	bool operator==(const Position& other) const 
	{
		return x == other.x && y == other.y;
	}
	bool operator!=(const Position& other) const
	{
		return x != other.x && y != other.y;
	}
	void operator+=(const Position& other)
	{
		x += other.x;  
		y += other.y;
	}
};