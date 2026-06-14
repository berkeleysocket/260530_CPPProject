#pragma once
#include "Color.h"
#include"Actor.h"
#include "Clone.h"

class Player:public Actor
{
public:
	Player() = default;

private:
	Position m_spawnPos;//Ä¿¼­¿ë
	Position m_spawnMapPos;//¸Ê¿ë
	bool m_isActive = true;
	Color m_bodyClr = Color::WHITE;
public:
	void SetSpawnPos(Position spawnPos, Position spawnMapPos);
	void Spawn();
	void Dead();
	const bool GetIsActive()const
	{
		return m_isActive;
	}
	void Render() const	 override;
	void Move(Dir dir)  override;
	void Tick(float deltaTime) override;
};