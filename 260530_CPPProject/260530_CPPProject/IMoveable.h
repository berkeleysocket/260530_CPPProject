#pragma once
#include"Dir.h"

class IMoveable
{
private :
	int moveCooltime = 2;
public:
	virtual ~IMoveable() = default;
	virtual void Move(Dir dir) abstract;
	int nextMoveTime = 0;
};