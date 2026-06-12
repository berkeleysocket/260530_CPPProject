#include "Clone.h"
#include "Console.h"

void Clone::Render() const
{
	SetDefaultMode();
	SetColor();
	GotoXY(m_prevPos.x, m_prevPos.y);
	cout << " ";

	SetUniCodeMode();
	SetColor(m_bodyClr);
	GotoXY(m_cursorPos.x, m_cursorPos.y);
	wcout << L"😊";
}
void Clone::Move(Dir dir)
{
	m_prevPos = m_cursorPos;

	switch (dir)
	{
	case Dir::UP:
		m_cursorPos.y--;
		break;
	case Dir::DOWN:
		m_cursorPos.y++;
		break;
	case Dir::LEFT:
		m_cursorPos.x--;
		break;
	case Dir::RIGHT:
		m_cursorPos.x++;
		break;
	}
}

void Clone::Tick(float deltaTime)
{

}
