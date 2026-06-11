#pragma once
#include"Position.h"
#include "Color.h"
#include"IMoveable.h"

class Player:public IMoveable
{
public:
	Player(Color bodyClr, Position pos)
	{
		this->pos = pos;
		this->bodyClr = bodyClr;
	}
	Player() = default;
private:
	Position pos = { 0,0 };
	Position prevPos = { 0,0 };

	bool isActive = true;

	Color bodyClr = Color::WHITE;

public:
	const Position GetPos() const
	{
		return pos;
	}
	void Render();
	void Move(Dir dir) override;
};