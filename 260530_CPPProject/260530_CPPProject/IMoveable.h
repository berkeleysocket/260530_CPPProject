#pragma once
#include"Dir.h"

class IMoveable
{ 
protected:
	int moveCooltime = 500;
	int nextMoveTime = 0;
public:
	virtual ~IMoveable() = default;
	virtual void Move(Dir dir) abstract;
};