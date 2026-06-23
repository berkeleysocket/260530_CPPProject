#include "Clone.h"
#include "Console.h"
#include "Player.h"
#include "InGameScene.h"
#include "SoundManager.h"

void Clone::Render() const
{
	if (!m_isActive)
		return;

	SetColor(m_bodyClr);
	GotoXY(m_cursorPos.x, m_cursorPos.y);
	cout << m_bodyImg;
}

void Clone::Move(Dir dir)
{
	SoundManager::GetInst()->Play("CloneMovement");
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

void Clone::Spawn(std::queue<MoveData> record)
{
	m_isActive = true;
	m_moveRecord = record;
	m_bodyClr = Color::YELLOW;
	m_bodyImg = "§";
}

void Clone::Init()
{
	nextMoveTime = moveCooltime;

	Render();
	m_isActive = false;
}

void Clone::Dead()
{
	nextMoveTime = moveCooltime;

	m_bodyClr = Color::RED;
	m_bodyImg = "＃";
	Render();
	m_isActive = false;
	SoundManager::GetInst()->Play("CloneDeath");

	//밑에거 다른곳에서 할거면 지워도 상관 ㄴ
	//SetColor();
	//GotoXY(m_cursorPos.x, m_cursorPos.y);
	//cout << " ";
}

void Clone::Tick(GameState& state, float deltaTime)
{
	if (!m_isActive)
		return;
	nextMoveTime -= deltaTime;
	if (nextMoveTime <= 0)
	{
		if (!m_moveRecord.empty())
		{
			Dir dir = m_moveRecord.front().dir;
			if(TryCloneMove(state, dir))
				Move(dir);
			m_moveRecord.pop();
			nextMoveTime = moveCooltime;
		}
		else
		{
			m_isActive = false;
		}
	}
}

bool Clone:: IsActive()
{
	return m_isActive;
}