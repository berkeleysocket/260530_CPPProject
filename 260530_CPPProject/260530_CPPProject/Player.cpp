#include "Player.h"
#include "Console.h"
#include "InGameScene.h"

void Player::Render()
{
	SetDefaultMode();
	SetColor();
	GotoXY(m_prevPos.x, m_prevPos.y);
	cout << "  ";

	SetColor(bodyClr);
	GotoXY(m_pos.x, m_pos.y);
	cout << "□";
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
