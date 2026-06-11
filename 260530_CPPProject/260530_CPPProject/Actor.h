#pragma once
#include"Position.h"
#include"IMoveable.h"
#include "MoveData.h"
#include<vector>
#include <Windows.h>

class Actor:public IMoveable
{
public:
	Actor(Position pos = { 0,0 });
	virtual ~Actor() = default;

	virtual void Tick(float deltaTime) abstract;
	virtual void Render() const abstract;
public:
	virtual void Move(Dir _dir) abstract;
public:
	const Position& GetPos() const
	{
		return m_pos;
	}
protected:
	Position m_pos;
	Position m_prevPos;
};

