#include "Clone.h"
#include "Console.h"
#include "Player.h"

void Clone::Render() const
{
	if (!m_isActive)
		return;

	if (m_prevPos != m_cursorPos)
	{
		SetDefaultMode();
		SetColor();
		GotoXY(m_prevPos.x, m_prevPos.y);
		cout << "  ";
	}

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

void Clone::Spawn(std::queue<MoveData> record)
{
	m_isActive = true;
	m_moveRecord = record;
}

void Clone::Dead()
{
	m_isActive = false;

	//밑에거 다른곳에서 할거면 지워도 상관 ㄴ
	SetColor();
	GotoXY(m_cursorPos.x, m_cursorPos.y);
	cout << " ";
}

void Clone::Tick(float deltaTime)
{
	if (!m_isActive)
		return;
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
