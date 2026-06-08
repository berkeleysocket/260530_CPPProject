#pragma once
#include<queue>
#include"Color.h"
#include"IMoveable.h"
#include"Position.h"

class Clone:IMoveable
{
public:
	Clone(Position pos)
	{
		this->pos = pos;
	}

private:
	Position pos = { 0,0 };
	Position prevPos = { 0,0 };

	bool isActive;

	Color bodyClr = Color::YELLOW;

	std::queue<Dir> moveQ;

public:
	int nextMoveTime;
	void PushMoveData(Dir dir);
	void Move(Dir dir)override;
};

