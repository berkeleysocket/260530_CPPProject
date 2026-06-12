#include "Player.h"
#include "Console.h"


void Player::Render() const
{
		SetDefaultMode();
		SetColor();
		GotoXY(m_prevPos.x, m_prevPos.y);
		cout << "  ";

		//SetUniCodeMode();
		SetColor(m_bodyClr);
		GotoXY(m_cursorPos.x, m_cursorPos.y);
		//wcout << L"⁜";
		cout << "□";
}


void Player::Move(Dir dir)
{
	m_prevPos = m_cursorPos;

	switch (dir)
	{
	case Dir::UP:
		m_mapPos.y--;
		m_cursorPos.y --;
		break;
	case Dir::DOWN:
		m_mapPos.y++;
		m_cursorPos.y++;
		break;
	case Dir::LEFT:
		m_mapPos.x--;
		m_cursorPos.x -= 2;
		break;
	case Dir::RIGHT:
		m_mapPos.x++;
		m_cursorPos.x += 2;
		break;
	}

}

void Player::Tick(float deltaTime)
{
}
