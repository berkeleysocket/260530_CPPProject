#pragma once
#include"Position.h"
#include"IMoveable.h"
#include <Windows.h>

class Actor:public IMoveable
{
public:
	Actor(Position cursorPos = { 0,0 }, Position mapPos = { 0,0 });
	virtual ~Actor() = default;

	virtual void Tick(ULONGLONG curTick) abstract;
	virtual void Render() const abstract;
public:
	virtual void Move(Dir _dir) abstract;
public:
	const Position& GetCursorPos() const
	{
		return m_cursorPos;
	}
	const Position& GetMapPos() const
	{
		return m_cursorPos;
	}

protected:
	Position m_cursorPos;
	Position m_prevPos;
	Position m_mapPos;
};

