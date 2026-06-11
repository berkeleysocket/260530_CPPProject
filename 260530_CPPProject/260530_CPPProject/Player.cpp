#include "Player.h"
#include "Console.h"


void Player::Render() const
{
		SetDefaultMode();
		SetColor();
		GotoXY(m_prevPos.x, m_prevPos.y);
		cout << " ";

		SetUniCodeMode();
		SetColor(bodyClr);
		GotoXY(m_pos.x, m_pos.y);
		wcout << L"⁜";

		clone.Render();
}


void Player::Move(Dir dir)
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

	clone.PushMoveData(dir);
}

void Player::Tick(ULONGLONG curTick)
{
	clone.Tick(curTick);
}
