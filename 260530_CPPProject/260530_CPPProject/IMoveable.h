#pragma once
#include"Dir.h"
class IMoveable
{
public:
	virtual ~IMoveable() = default;
	virtual void Move(Dir dir) abstract;
};