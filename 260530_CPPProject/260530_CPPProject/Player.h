#pragma once
#include"Actor.h"
#include"Color.h"
#include"SoundManager.h"
#include<string>

class Player:public Actor
{
public:
	Player() = default;

private:
	Position m_spawnPos;//Ä¿¼­¿ë
	Position m_spawnMapPos;//¸Ê¿ë
	bool m_isActive = true;
	Color m_bodyClr = Color::WHITE;
	std::string m_bodyImg = "¡Ú";

public:
	void SetSpawnPos(Position spawnPos, Position spawnMapPos);
	void Spawn();
	void Dead();
	const bool GetIsActive()const
	{
		return m_isActive;
	}
	const Position GetStartPos() const
	{
		return m_spawnMapPos;
	}
	const std::string GetImage() const
	{
		return m_bodyImg;
	}
	const Color GetColor() const
	{
		return m_bodyClr;
	}
	void Render() const	 override;
	void Move(Dir dir)  override;
	void Tick(float deltaTime);
};