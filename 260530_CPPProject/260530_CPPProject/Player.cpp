#include "Player.h"
#include "Console.h"

void Player::Render() const
{
	SetColor(m_bodyClr);
	GotoXY(m_cursorPos.x, m_cursorPos.y);
	cout << m_bodyImg;
}

void Player::SetSpawnPos(Position spawnPos, Position spawnMapPos)
{
	m_spawnMapPos = spawnMapPos;
	m_spawnPos = spawnPos;
}

void Player::Spawn()
{
	m_bodyClr = Color::WHITE;
	m_bodyImg = "★";
	m_isActive = true;
}

void Player::Dead()
{
	m_prevPos = m_cursorPos;
	m_isActive = false;
	m_bodyClr = Color::RED;
	m_bodyImg = "☆";
	SoundManager::GetInst()->Play("PlayerDeath");
	Render();
}

void Player::Move(Dir dir)
{
	SoundManager::GetInst()->Play("PlayerMovement");
	m_prevPos = m_cursorPos;

	switch (dir)
	{
	case Dir::UP:
		m_mapPos.y--;
		m_cursorPos.y--;
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
