#include "Actor.h"

Actor::Actor(Position cursorPos, Position mapPos)
{
	m_cursorPos = cursorPos;
	m_prevPos = Position{ 0,0 };
	m_mapPos = mapPos;
}
