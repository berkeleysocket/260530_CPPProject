#include "Clone.h"
#include "Console.h"

void Clone::Render() const
{
	SetDefaultMode();
	SetColor();
	GotoXY(m_prevPos.x, m_prevPos.y);
	cout << "  ";

	SetColor(m_bodyClr);
	GotoXY(m_cursorPos.x, m_cursorPos.y);
	cout << "§";
}
void Clone::Move(Dir dir)
{


	m_prevPos = m_cursorPos;

	switch (dir)
	{
	case Dir::UP:
		m_cursorPos.y-=1;
		break;
	case Dir::DOWN:
		m_cursorPos.y+=1;
		break;
	case Dir::LEFT:
		m_cursorPos.x-=2;
		break;
	case Dir::RIGHT:
		m_cursorPos.x+=2;
		break;
	}
}

void Clone::Tick(float deltaTime)
{
	nextMoveTime -= deltaTime;
	if (nextMoveTime <= 0)
	{
		if (!m_moveRecord.empty())
		{
			Move(m_moveRecord.front().dir);
			m_moveRecord.pop();
			nextMoveTime = moveCooltime;
		}
		else
		{
			m_isActive = false;
				}
	}
}
