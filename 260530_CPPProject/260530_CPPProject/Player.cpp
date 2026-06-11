#include "Player.h"
#include "Console.h"


void Player::Render() const
{
		SetDefaultMode();
		SetColor();
		GotoXY(m_prevPos.x, m_prevPos.y);
		cout << " ";

		SetUniCodeMode();
		SetColor(m_bodyClr);
		GotoXY(m_pos.x, m_pos.y);
		wcout << L"□";
}


void Player::Move(Dir dir)
{
	m_prevPos = m_pos;

	switch (dir)
	{
	case Dir::UP:
		m_pos.y -= 2;
		break;
	case Dir::DOWN:
		m_pos.y += 2;
		break;
	case Dir::LEFT:
		m_pos.x -= 2;
		break;
	case Dir::RIGHT:
		m_pos.x += 2;
		break;
	}
}

void Player::Tick(float deltaTime)
{
}
