#pragma once
#include"Position.h"
#include "Color.h"
#include"IMoveable.h"

class Player:public IMoveable
{
public:
	Player(Color bodyClr, Position pos)
	{
		this->m_pos = pos;
		this->bodyClr = bodyClr;
	}
	Player() = default;
private:
	Position m_pos = { 0,0 };
	Position m_prevPos = { 0,0 };

	bool isActive = true;

	Color bodyClr = Color::WHITE;

public:
	const Position GetPos() const
	{
		return m_pos;
	}
	void Render();
	void Move(Dir dir) override;
};