#pragma once
#include "Color.h"
#include"Actor.h"
#include "Clone.h"

class Player:public Actor
{
public:
	Player() = default;
private:
	bool m_isActive = true;
	Color m_bodyClr = Color::WHITE;
public:

	void Render() const	 override;
	void Move(Dir dir)  override;
	void Tick(float deltaTime) override;
};