#pragma once

class Laser
{
private:
	Position position;
	Position dir;
public:
	const Position GetPos() const
	{
		return position;
	}
	const Position GetDirection() const
	{
		return dir;
	}
};

