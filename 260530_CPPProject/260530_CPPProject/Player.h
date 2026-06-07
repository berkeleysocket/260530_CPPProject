#pragma once
#include"Position.h"
#include "Color.h"
#include"IMoveable.h"

class Player:public IMoveable
{
private:
	Position pos = { 0,0 };
	Position prevPos = { 0,0 };

	bool isActive;

	Color bodyClr;

public:
	const Position GetPos() const
	{
		return pos;
	}
	void Render();
	void Move(Dir dir) override;
};