#pragma once
#include<queue>
#include"Color.h"
#include"IMoveable.h"
#include"Position.h"

const int CLONE_MOVE_COOLDOWN;
class Clone:IMoveable
{
private:
	std::queue<Dir> moveQ;

public:
	int nextMoveTime;
	void PushMoveData(Dir dir);
	void Move(Dir dir)override;
};

