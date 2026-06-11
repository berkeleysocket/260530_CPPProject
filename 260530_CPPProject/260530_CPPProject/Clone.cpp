#include "Clone.h"
#include "Console.h"

void Clone::Render() const
{
	if (!isActive) return;
	SetDefaultMode();
	SetColor();
	GotoXY(m_prevPos.x, m_prevPos.y);
	cout << " ";

	SetUniCodeMode();
	SetColor(bodyClr);
	GotoXY(m_pos.x, m_pos.y);
	wcout << L"😊";
}

void Clone::PushMoveData(Dir dir)
{
	moveQ.push(dir);
}

void Clone::Move(Dir dir)
{


	m_prevPos = m_pos;

	switch (dir)
	{
	case Dir::UP:
		m_pos.y--;
		break;
	case Dir::DOWN:
		m_pos.y++;
		break;
	case Dir::LEFT:
		m_pos.x--;
		break;
	case Dir::RIGHT:
		m_pos.x++;
		break;
	}
}

void Clone::Tick(ULONGLONG curTick)
{
	if (isActive = true);
	if (nextMoveTime > curTick)
		return;

	if (moveQ.size() == 0)return;

	Dir dir = moveQ.front();
	moveQ.pop();
	Move(dir);
	nextMoveTime = moveCooltime + curTick;
}
