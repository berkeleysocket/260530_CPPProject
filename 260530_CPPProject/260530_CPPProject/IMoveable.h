#pragma once
#include"Dir.h"

class IMoveable
{
private :
	int moveCooltime;
public:
	virtual ~IMoveable() = default;
	virtual void Move(Dir dir);
	int nextMoveTime;
};